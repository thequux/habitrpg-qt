#include "HrpgClient.h"


HrpgClient::HrpgClient(QObject *parent) :
    QObject(parent),
    m_auth(nullptr),
    m_fullyInitialized(false)
{
}

void HrpgClient::try_login(HrpgAuth &auth) {
    *m_auth = auth;
    emit userChanged();
}

const HrpgAuth &HrpgClient::auth() const {
    return *m_auth;
}
void HrpgClient::setAuth(HrpgAuth &newValue) {
    if (newValue != *m_auth) {
        try_login(newValue);
    }
}

void HrpgClient::classBegin() {}
void HrpgClient::componentComplete() {
    m_fullyInitialized = true;
    if (m_auth != nullptr) {
        try_login(*m_auth);
    }

}
