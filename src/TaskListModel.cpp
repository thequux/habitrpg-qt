#include "TaskListModel.h"

TaskListModel::TaskListModel(QObject *parent) :
    QAbstractListModel(parent),
    contents()
{

}

void TaskListModel::mergeFrom(QList<QObject *> obj) {

}
