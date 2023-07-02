#include "client.h"
#include "./ui_client.h"
#include <qtimer.h>
#include "conncetionmodel.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
//    QTimer::singleShot(2000, this, SLOT(setLable("some")));

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
    ConnectionModel *model = new ConnectionModel(this);

    model->populateData(connNum, LastData, state);

    ui->tableView->setModel(model);

    ui->tableView->horizontalHeader()->setVisible(true);
    ui->tableView->show();


}

Client::~Client()
{
    delete ui;
}



void Client::setLable(std::string newLable) {
    ui->totalCountLbl->setText("some text");
}