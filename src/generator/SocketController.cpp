#include "SocketController.hpp"
#include <netinet/in.h>
#include <sys/socket.h>

#include <arpa/inet.h>
#include <csignal>
#include <iostream>
#include <utility>

SocketController::SocketController(int threadCount, std::string servAddr, int port):
                                    port(port),
                                    addr(std::move(servAddr)) {
    for (int i = 0; i < threadCount; ++i) {
    auto sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
      std::cout <<"Can't create some sockets" << std::endl;
      throw ;
    }

    threadPool.emplace_back(new std::thread{&SocketController::threadInit, this, sock});

  }
}
void SocketController::threadInit(int sockFd) {
    sockaddr_in serv{
      .sin_family = AF_INET,
      .sin_port = htons(port)
    };
    inet_pton(AF_INET, addr.c_str(), &serv.sin_addr);
    int opt = 1;
    if (setsockopt(sockFd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
      std::cout <<"Can't set sockets opts sockFd: " << sockFd << std::endl;
      return ;
    }
    while (!started.load(std::memory_order_relaxed) && !terminate.load(std::memory_order_relaxed))
      std::this_thread::sleep_for(std::chrono::microseconds(500));
    auto res = connect(sockFd, (struct sockaddr*)&serv,sizeof(serv));
    if (res < 0)
      return ;
    while (started.load(std::memory_order_relaxed)) {
      auto data = std::to_string(random() % 10000);
      auto sc = send(sockFd, data.data(), data.size() - 1 , MSG_NOSIGNAL);
      if (sc == -1 ) {
        close(sockFd);
        std::cout << "Error on sending message to sockFd: " << sockFd << std::endl;
        return;
      }
    }

    if (!started.load(std::memory_order_relaxed) || terminate.load(std::memory_order_relaxed))
      close(sockFd);
}
void SocketController::start() {
    started = true;
}

void SocketController::stop() {
    started = false;
    terminate = true;
    for (auto t : threadPool) {
      if (t->joinable())
        t->join();
      delete t;
    }
}
