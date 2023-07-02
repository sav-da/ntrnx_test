#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include "conncetionmodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public slots:
    void setConnectionCount(std::string);
public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;
    ConnectionModel* table{nullptr};
};




#endif // CLIENT_H
