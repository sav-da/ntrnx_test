#include "client.h"
#include "./ui_client.h"
#include "conncetionmodel.h"
#include <qtimer.h>

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    QList<int> connNum;
    connNum.append(1);
    connNum.append(2);
    connNum.append(3);

    QList<QString> LastData;
    LastData.append("some");
    LastData.append("2");
    LastData.append("3");

    QList<bool> state;
    state.append(true);
    state.append(false);
    state.append(true);
    table = new ConnectionModel(this);

    table->populateData(connNum, LastData, state);

    ui->tableView->setModel(table);

    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();
    serv = new Server(16384);
}

Client::~Client()
{
    delete serv;
    delete ui;
}



void Client::setConnectionCount(std::string newLable) {
    ui->totalCountLbl->setText("some text");
}
