/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 18:57:53 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/03/02 18:57:57 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/webserv.hpp"

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello World!";
    struct pollfd fds[MAX_CLIENTS];
    int nfds = 1;

    // Create a socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, (socklen_t)sizeof(opt))) {
//        strerror(errno);
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Set server socket to non-blocking
    int flags = fcntl(server_fd, F_GETFL, 0);
    fcntl(server_fd, F_SETFL, flags | O_NONBLOCK);

    // Initialize pollfd for server socket
    fds[0].fd = server_fd;
    fds[0].events = POLLIN;

    // Accept incoming connections and send response
    while (1) {
        // Wait for events
        int nready = poll(fds, nfds, -1);
        if (nready == -1) {
            perror("poll failed");
            exit(EXIT_FAILURE);
        }

        // Check for new connection
        if (fds[0].revents & POLLIN) {
            if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t *) &addrlen)) < 0) {
                perror("accept failed");
                exit(EXIT_FAILURE);
            }

            // Set client socket to non-blocking
            flags = fcntl(new_socket, F_GETFL, 0);
            fcntl(new_socket, F_SETFL, flags | O_NONBLOCK);

            // Add client socket to pollfd array
            fds[nfds].fd = new_socket;
            fds[nfds].events = POLLIN;
            nfds++;

            printf("New connection from %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        }

        // Check for incoming data
        for (int i = 1; i < nfds; i++) {
            if (fds[i].revents & POLLIN) {
                valread = read(fds[i].fd, buffer, 1024);
                if (valread == 0) {
                    // Client closed connection
                    close(fds[i].fd);
                    fds[i] = fds[nfds - 1];
                    nfds--;
                    i--;
                } else if (valread > 0) {
                    // Send respons
                    send(fds[i].fd, hello, strlen(hello), 0);
                } else {
                    perror("read failed");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return 0;
}

