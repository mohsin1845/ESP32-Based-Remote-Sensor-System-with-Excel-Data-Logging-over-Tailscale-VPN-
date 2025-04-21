/*
Name: Mohsin Mohiuddin
Date: 21/04/2025
Description: This C program acts as a bridge between an ESP32 device and a remote PC (PC A) using TCP sockets. 
It listens for incoming connections from an ESP32 on a local port and forwards the received data to a remote PC over a Tailscale network.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define LOCAL_PORT 5010                  // Port to receive from ESP32
#define REMOTE_IP "100.119.33.116"       // Tailscale IP of PC A
#define REMOTE_PORT 5010                 // Same port as server

int main() {
    int listen_sock, client_sock, remote_sock;
    struct sockaddr_in local_addr, client_addr, remote_addr;
    socklen_t addr_len = sizeof(struct sockaddr_in);
    char buffer[1024];
    int bytes_read;

    // Create listening socket (for ESP32)
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind to local port (receiving data from ESP32)
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = INADDR_ANY;
    local_addr.sin_port = htons(LOCAL_PORT);
    if (bind(listen_sock, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(listen_sock, 1);
    printf("Waiting for ESP32 on port %d...\n", LOCAL_PORT);

    while (1) {
        // Accept connection from ESP32
        client_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &addr_len);
        if (client_sock < 0) {
            perror("Accept failed");
            continue;
        }

        printf("Connected to ESP32: %s\n", inet_ntoa(client_addr.sin_addr));

        // Create connection to remote server over Tailscale
        remote_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (remote_sock < 0) {
            perror("Remote socket creation failed");
            close(client_sock);
            continue;
        }

        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port = htons(REMOTE_PORT);
        inet_pton(AF_INET, REMOTE_IP, &remote_addr.sin_addr);

        if (connect(remote_sock, (struct sockaddr*)&remote_addr, sizeof(remote_addr)) < 0) {
            perror("Connect to remote failed");
            close(client_sock);
            close(remote_sock);
            continue;
        }

        printf("Forwarding data to PC A (%s:%d)\n", REMOTE_IP, REMOTE_PORT);

        // Forward data
        while ((bytes_read = recv(client_sock, buffer, sizeof(buffer), 0)) > 0) {
            send(remote_sock, buffer, bytes_read, 0);
        }

        printf("Connection closed by ESP32.\n");

        close(client_sock);
        close(remote_sock);
    }

    close(listen_sock);
    return 0;
}

