#include <QUuid>
#include "HrpgTask.h"


HrpgTask::HrpgTask(TaskType type, QObject *parent) :
    QObject(parent),
    m_taskType(type),
    m_id(QUuid::createUuid().toString().mid(1, 36))
{

}
