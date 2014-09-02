#ifndef MERGABLELISTMODEL_H
#define TASKLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "HrpgTask.h"

///
/// \brief Manages a set of items with QString ids
///
class TaskListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TaskListModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

signals:
public slots:
    void mergeFrom(QList<QJsonValue*> obj);

private:
    QList<HrpgTask*> contents;
};

#endif // TASKLISTMODEL_H
