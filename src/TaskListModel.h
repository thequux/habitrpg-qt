#ifndef MERGABLELISTMODEL_H
#define TASKLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

///
/// \brief Manages a set of items with QString ids
///
class TaskListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TaskListModel(QObject *parent = 0);

signals:
public slots:
    void mergeFrom(QList<QObject*> obj);

private:
    QList<QObject*> contents;
};

#endif // TASKLISTMODEL_H
