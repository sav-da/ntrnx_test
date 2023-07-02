#ifndef CLIENT_H
#define CLIENT_H

#include "conncetionmodel.h"
#include "server.hpp"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Client;
}
QT_END_NAMESPACE

class Client : public QMainWindow {
  Q_OBJECT

public slots:
  void setConnectionCount(std::string);

public:
  explicit Client(QWidget *parent = nullptr);
  ~Client() override;

private:
  Ui::Client *ui;
  ConnectionModel *table{nullptr};
  Server *serv;
};




#endif // CLIENT_H
