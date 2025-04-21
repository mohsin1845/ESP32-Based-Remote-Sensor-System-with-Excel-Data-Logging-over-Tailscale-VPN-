/*
Name: Mohsin Mohiuddin  
Date: April 21, 2025  
Description:  
This program creates a TCP server that listens for incoming sensor data on port 5010.  
It receives data sent by a client (e.g., an ESP32 or similar device), timestamps it with the current date and time,  
and stores it in an Excel file named "sensor_data.xlsx" using the libxlsxwriter library.  
The program also handles a Ctrl+C (SIGINT) signal to gracefully close and save the Excel file before exiting.

Sample input:  
Sensor data sent over TCP socket connection (e.g., "Temperature: 28.5°C")  

Sample output:  
Excel file "sensor_data.xlsx" with columns: Date | Time | Data  
Console output:
Received: Temperature: 28.5°C  
Data saved to Excel: Date: 2025-04-21, Time: 12:30:45, data: Temperature: 28.5°C  
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <xlsxwriter.h>

#define PORT 5010

lxw_workbook *workbook;
lxw_worksheet *worksheet;
int row = 1;

// Cleanup function to call on Ctrl+C
void handle_sigint(int sig) {
    printf("\nSaving and closing Excel file...\n");
    if (workbook) {
        workbook_close(workbook);
    }
    exit(0);
}

void save_to_excel(const char *sensor_data) {
    if (worksheet == NULL) {
        worksheet = workbook_add_worksheet(workbook, NULL);
	  /* Add a format. */
    lxw_format *format = workbook_add_format(workbook);

    /* Set the bold property for the format */
    format_set_bold(format);
        worksheet_write_string(worksheet, 0, 0, "Date", format);
        worksheet_write_string(worksheet, 0, 1, "Time", format);
        worksheet_write_string(worksheet, 0, 2, "Data", format);
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date[64], time_str[64];

    strftime(date, sizeof(date), "%Y-%m-%d", t);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", t);

    worksheet_write_string(worksheet, row, 0, date, NULL);
    worksheet_write_string(worksheet, row, 1, time_str, NULL);
    worksheet_write_string(worksheet, row, 2, sensor_data, NULL);

    printf("Data saved to Excel: Date: %s, Time: %s, data: %s\n", date, time_str, sensor_data);
    row++;
}

int main() {
    signal(SIGINT, handle_sigint);  // Handle Ctrl+C to close file safely

    workbook = workbook_new("sensor_data.xlsx");
    if (!workbook) {
        fprintf(stderr, "Failed to create workbook\n");
        return 1;
    }

    printf("Excel workbook 'sensor_data.xlsx' created.\n");

    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_fd, 5);

    printf("Server listening on port %d...\n", PORT);

    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int len = read(client_fd, buffer, sizeof(buffer) - 1);
        if (len <= 0) break;

        printf("Received: %s\n", buffer);
        save_to_excel(buffer);
    }

    // Close workbook on normal exit
    workbook_close(workbook);
    close(client_fd);
    close(server_fd);
    return 0;
}
