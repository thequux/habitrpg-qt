#include <QUuid>
#include <QJsonValue>
#include <QJsonObject>
#include <QString>
#include <QDateTime>

#include "HrpgTask.h"


HrpgTask::HrpgTask(TaskType type, QObject *parent) :
    QObject(parent),
    m_taskType(type),
    m_id(QUuid::createUuid().toString().mid(1, 36))
{

}

HrpgTask* HrpgTask::fromJSON(QObject *parent, const QJsonValue &json) {
    TaskType typ;
    QJsonObject obj = json.toObject();
    if (obj.isEmpty()) {
        return nullptr; // TODO: log this
    }

    QString stype = obj["type"].toString();
    if (stype == "habit") {
        typ = Habit;
    } else if (stype == "daily") {
        typ = Daily;
    } else if (stype == "todo") {
        typ = Todo;
    } else if (stype == "reward") {
        typ = Reward;
    } else {
        return nullptr;
        // TODO: log this
    }

    HrpgTask *task = new HrpgTask(typ, parent);

    // I know that nothing can be listening to signals, so I won't send any of them.
    task->m_id = obj["id"].toString();
    task->m_text = obj["text"].toString();
    task->m_dateCreated = QDateTime::fromString(obj["dateCreated"].toString(), Qt::ISODate);

    // TODO: process other fields
    return task;

}
