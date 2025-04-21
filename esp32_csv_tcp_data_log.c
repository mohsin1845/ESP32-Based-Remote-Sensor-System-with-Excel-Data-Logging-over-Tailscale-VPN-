/*
Name: Mohsin Mohiuddin  
Date: April 21, 2025  
Description:  
This program creates a TCP server that listens on port 5010 for incoming sensor data.  
Each client connection is handled in a separate process using `fork()`.  
Incoming data is timestamped and saved to a CSV file named "sensor_data.csv".  
The server can handle multiple clients simultaneously, and data is logged in the format:  
[Timestamp], [Sensor Data].

Sample input:  
Sensor data sent over a TCP connection (e.g., "Humidity: 60%")  

Sample output (in `sensor_data.csv`):  
2025-04-21 21:02:15,Humidity: 60%  
2025-04-21 21:02:20,Temperature: 25.3°C  

Console output:  
Server listening on port 5010...  
Received: Humidity: 60%  
Received: Temperature: 25.3°C  
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 5010
#define BUFSIZE 1024
#define CSV_FILE "sensor_data.csv"

void save_to_csv(const char *sensor_data) {
    FILE *fp = fopen(CSV_FILE, "a");
    if (!fp) {
        perror("fopen");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", t);

    fprintf(fp, "%s,%s\n", timestamp, sensor_data);
    fclose(fp);
}

void handle_client(int client_sock) {
    char buffer[BUFSIZE];
    int bytes_read;

    while ((bytes_read = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0';
        printf("Received: %s\n", buffer);
        save_to_csv(buffer);
    }

    close(client_sock);
    exit(0);  // Child process ends
}

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    //server_addr.sin_addr.s_addr = inet_addr("192.168.29.102");
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    listen(server_sock, 5);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        if (fork() == 0) {
            close(server_sock); // Child doesn't need the listener
            handle_client(client_sock);
        } else {
            close(client_sock); // Parent doesn't need the client socket
        }
    }

    return 0;
}
