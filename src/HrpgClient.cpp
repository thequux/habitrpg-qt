#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include "HrpgClient.h"

#define STRINGIFY(x) #x

static QUrl api_basepath("http://" STRINGIFY(HRPG_SERVER) "/api/v2/");

HrpgClient::HrpgClient(QObject *parent) :
    QObject(parent),
    m_auth(nullptr),
    m_fullyInitialized(false),
    m_auth_valid(false),
    m_netman(this)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,2,2)
    m_netman.connectToHost(api_basepath.host(), api_basepath.port(80));
#endif
}

QNetworkRequest HrpgClient::build_request(QString endpoint, HrpgAuth *authinfo) {
    QNetworkRequest req(api_basepath.resolved(endpoint));
    if (authinfo) {
        req.setRawHeader("X-Api-User", authinfo->uuid().toLatin1());
        req.setRawHeader("X-Api-Key", authinfo->apiKey().toLatin1());
    }

    return req;
}
QNetworkRequest HrpgClient::build_request(QString endpoint) {
    return build_request(endpoint, m_auth);
}

const HrpgAuth &HrpgClient::auth() const {
    return *m_auth;
}
void HrpgClient::setAuth(HrpgAuth &newValue) {
    if (newValue != *m_auth) {
        *m_auth = newValue;
        m_auth_valid = false;
        resync();
    }
}

void HrpgClient::classBegin() {}
void HrpgClient::componentComplete() {
    m_fullyInitialized = true;
    resync();
}

void HrpgClient::resync() {
    QNetworkReply* user_reply = m_netman.get(build_request("user"));
    QNetworkReply* content_reply = m_netman.get(build_request("content"));
    connect(user_reply, &QNetworkReply::finished, [this,user_reply,content_reply](){
        if (user_reply->error() != 0) {
            // Throw an error somehow
            content_reply->abort();
        }
        int status_code = user_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (status_code == 401) {
            // HTTP error: invalid login info
            emit login_failed();
        } else if (status_code == 200) {
            // parse user structure
            QJsonDocument doc = QJsonDocument::fromJson(user_reply->readAll());


        }

    });
}
