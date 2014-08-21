#include "HrpgAuth.h"


HrpgAuth::HrpgAuth(QObject *parent) :
    QObject(parent),
    m_uuid(),
    m_apiKey()
{
}

void HrpgAuth::setApiKey(QString &apikey) {
    if (apikey != m_apiKey) {
        m_apiKey = apikey;
    }
}

void HrpgAuth::setUuid(QString &value) {
    if (value != m_uuid) {
        m_uuid = value;
    }
}
