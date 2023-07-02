#include "server.hpp"
#include <csignal>
#include <future>
#include <iostream>
#include <netinet/in.h>

Server::Server(int portNum) {
  sockaddr_in address{};
  int opt = 1;
  int addrlen = sizeof(address);

  // Creating socket file descriptor
  if ((listenFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    std::cout << "Cannot create socket" << std::endl;
    return;
  }

  // Forcefully attaching socket to the port 8080
  if (setsockopt(listenFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    std::cout << "Cannot set socket opts" << std::endl;
    close(listenFd);
    return;
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(portNum);

  // Forcefully attaching socket to the port 8080
  if (bind(listenFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    std::cout << "Cannot bind socket" << std::endl;
    close(listenFd);
    return;
  }
  if (listen(listenFd, 20) < 0) {
    std::cout << "Cannot listen socket" << std::endl;
    close(listenFd);
    return;
  }

  auto accepter = std::async(std::launch::async, [&]() {
    while (!terminate.load(std::memory_order_relaxed)) {
      auto size = connectsFds.size();
      auto &back = connectsFds.back();
      back =
          accept(listenFd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
      if (back < 0) {
        std::cout << "Cannot accept connection" << std::endl;
        continue;
      }
      threadPool.emplace_back(
          new std::thread{&Server::processConnection, this, size, back});
    }
  });
  //    valread = read(new_socket, buffer, 1024);
  //    printf("%s\n", buffer);
  //    send(new_socket, hello, strlen(hello), 0);
  //    printf("Hello message sent\n");
  //
  //    // closing the connected socket
  //    close(new_socket);
  //    // closing the listening socket
  //    shutdown(listenFd, SHUT_RDWR);
  //    return 0;
}

void Server::processConnection(int connNum, int sock) {
  while (!terminate.load(std::memory_order_relaxed)) {
    char buf[7]{};
    read(sock, &buf, 6);
    std::cout << buf << std::endl;
    sleep(1);
  }
}