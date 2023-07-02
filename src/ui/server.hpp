#ifndef NTRNX_TEST_SERVER_HPP
#define NTRNX_TEST_SERVER_HPP

#include <atomic>
#include <list>
#include <thread>
class Server {
public:
  explicit Server(int portNum);

private:
  void processConnection(int connNum, int sockFd);

  int listenFd{};
  std::list<int> connectsFds{};
  std::list<std::thread *> threadPool{};
  std::atomic<bool> terminate{false};
};

#endif // NTRNX_TEST_SERVER_HPP
