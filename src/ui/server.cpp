#include "server.hpp"
#include "client.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent), parent(parent) {
  server = new QTcpServer(this);

  // whenever a user connects, it will emit signal
  connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

  if (!server->listen(QHostAddress::Any, 32768)) {
    qDebug() << "Server could not start";
  } else {
    qDebug() << "Server started!";
  }
}

void Server::newConnection() {
  // need to grab the socket
  sockets.append(server->nextPendingConnection());
  if (parent) {
    auto *client = dynamic_cast<Client *>(parent);
    if (client)
      client->incConnectionCount();
  }
  char buf[7];
  auto socksSize = sockets.indexOf(sockets.back());
  qDebug() << "socksize" << socksSize;
  socksSize = socksSize > 20 ? 0 : socksSize;

  sockets.back()->read(buf, 6);
  sockets.back()->write("Hello client\r\n");
  sockets.back()->waitForBytesWritten(300);

  connect(sockets[socksSize],
          SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,
          SLOT(terminateConnection(QAbstractSocket::SocketState)));
  threadPool.append(QThread::create([=]() {
    char buf[7];
    auto socket = sockets.back();
    while (socket->state() == QAbstractSocket::SocketState::ConnectedState) {
      socket->read(buf, 6);
      auto *client = dynamic_cast<Client *>(parent);
      if (client)
        client->updateTable(socksSize, QString(buf), true);
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    auto *client = dynamic_cast<Client *>(parent);
    if (client)
      client->updateTable(socksSize, QString(buf), false);
  }));
  threadPool.back()->start(QThread::TimeCriticalPriority);
}
void Server::terminateConnection(QAbstractSocket::SocketState state) {
  if (parent && state == QAbstractSocket::SocketState::UnconnectedState) {
    auto *client = dynamic_cast<Client *>(parent);
    if (client)
      client->decConnectionCount();
  }
}
