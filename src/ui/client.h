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
  void incConnectionCount();
  void decConnectionCount();
  void updateTable(const int &connNumber, const QString &lastD,
                   const bool &actState);

public:
  explicit Client(QWidget *parent = nullptr);
  ~Client() override;

private:
  int connCount{};
  Ui::Client *ui;
  ConnectionModel *table{nullptr};
  Server *serv{new Server(this)};

  QVector<bool> state{};
  QVector<QString> LastData{};
  QVector<int> connNum{};
};




#endif // CLIENT_H
