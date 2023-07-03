#ifndef NTRNX_TEST_SERVER_HPP
#define NTRNX_TEST_SERVER_HPP

#include "qthread.h"
#include <QDebug>
#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <atomic>
#include <list>
#include <thread>

class Server : public QObject {
  Q_OBJECT
public:
  explicit Server(QObject *parent = 0);

signals:

public slots:
  void newConnection();
  void terminateConnection(QAbstractSocket::SocketState);

private:
  QTcpServer *server;
  QObject *parent;
  QList<QTcpSocket *> sockets{};
  QList<QThread *> threadPool{};
};

#endif // NTRNX_TEST_SERVER_HPP
