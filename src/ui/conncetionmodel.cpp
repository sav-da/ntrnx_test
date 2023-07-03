#include "conncetionmodel.h"

ConnectionModel::ConnectionModel(QObject *parent)
    : QAbstractTableModel(parent) {}
// Create a method to populate the model with data:
void ConnectionModel::populateData(const QVector<int> &connNumber,
                                   const QVector<QString> &lastD,
                                   const QVector<bool> &state) {
  connectNum.clear();
  connectNum = QList<int>::fromVector(connNumber);
  lastData.clear();
  lastData = QList<QString>::fromVector(lastD);
  connected.clear();
  connected = QList<bool>::fromVector(state);
  resetInternalData();
}

int ConnectionModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return connectNum.length();
}
int ConnectionModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 3;
}
QVariant ConnectionModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    switch (index.column()) {
      case 0:
        return connectNum[index.row()];
      case 1:
        return lastData[index.row()];
      case 2:
        return connected[index.row()];
    }
    return QVariant();
}
QVariant ConnectionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
          return QString("Connect #");
        case 1:
          return QString("Last Data");
        case 2:
          return QString("Connected");
        }
    }
    return QVariant();
}
