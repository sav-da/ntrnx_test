#ifndef NTRNX_TEST_SOCKETCONTROLLER_HPP
#define NTRNX_TEST_SOCKETCONTROLLER_HPP

#include <atomic>
#include <list>
#include <string>
#include <thread>
#include <unordered_map>
class SocketController {
public:
  explicit SocketController(int threadCount, std::string addr, int port);
  void start();
  void stop();

private:
  void threadInit(int sockFd);


  mutable std::atomic<bool> started{false};
  mutable std::atomic<bool> terminate{false};
  std::list<std::thread*> threadPool{};

//  Constants
  const int port;
  const std::string addr;

};

#endif // NTRNX_TEST_SOCKETCONTROLLER_HPP
