#include "client.h"
#include "./ui_client.h"
#include "conncetionmodel.h"
#include "server.hpp"
#include <QThread>
#include <qtimer.h>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client) {
  ui->setupUi(this);
  connNum.resize(20);
  LastData.resize(20);
  state.resize(20);

  table = new ConnectionModel(this);

  table->populateData(connNum, LastData, state);

  ui->tableView->setModel(table);

  ui->tableView->horizontalHeader()->setVisible(true);
  ui->tableView->verticalHeader()->setVisible(false);
  ui->tableView->show();
}

Client::~Client() { delete ui; }
void Client::decConnectionCount() {
  --connCount;
  ui->totalCountLbl->setNum(connCount);
}

void Client::incConnectionCount() {
  ++connCount;
  ui->totalCountLbl->setNum(connCount);
}
void Client::updateTable(const int &connNumber, const QString &lastD,
                         const bool &actState) {
  qDebug() << "num" << connNumber << " size vector " << connNum.size();

  connNum[connNumber] = connNumber;

  LastData[connNumber] = lastD;

  state[connNumber] = actState;

  table->populateData(connNum, LastData, state);
}
