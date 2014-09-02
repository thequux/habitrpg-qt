#include <QUuid>
#include <QJsonValue>
#include <QString>
#include <QDateTime>

#include "HrpgTask.h"


HrpgTask::HrpgTask(TaskType type, QObject *parent) :
    QObject(parent),
    m_taskType(type),
    m_id(QUuid::createUuid().toString().mid(1, 36))
{

}

HrpgTask* HrpgTask::fromJSON(const QJsonValue &json) {
    return nullptr;
}
