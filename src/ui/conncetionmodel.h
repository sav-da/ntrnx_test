#ifndef CONNCETIONMODEL_H
#define CONNCETIONMODEL_H


#include "qabstractitemmodel.h"


class ConnectionModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    ConnectionModel(QObject *parent = 0);
    void populateData(const QList<int> &connNumber,const QList<QString> &lastD, const QList<bool> &connected);
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole)
        const Q_DECL_OVERRIDE;
private:
    QList<int> connectNum;
    QList<QString> lastData;
    QList<bool> connected;
};

#endif // CONNCETIONMODEL_H
