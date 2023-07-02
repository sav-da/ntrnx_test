#include <iostream>
#include "SocketController.hpp"

void printHelper() {
  std::cout << "Please, use this with parameters ./program server-ip thread-count server-port \n";
}


int main(int argc, char* argv[]) {
  if (argc < 4) {
    printHelper();
    exit(1);
  }

  auto ip = std::string{argv[1]};
  auto threadCount = std::stoi(argv[2]);
  auto port = std::stoi(argv[3]);

  SocketController controller(threadCount, ip, port);
  controller.start();
  std::this_thread::sleep_for(std::chrono::seconds(5));
  controller.stop();


  return 0;
}