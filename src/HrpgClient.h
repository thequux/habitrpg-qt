#ifndef HRPGCLIENT_H
#define HRPGCLIENT_H

#include <QObject>
#include <QQmlParserStatus>
#include <QNetworkAccessManager>
#include "HrpgAuth.h"


class HrpgClient : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
    Q_PROPERTY(HrpgAuth auth READ auth WRITE setAuth)


public:
    explicit HrpgClient(QObject *parent = 0);

    void classBegin();
    void componentComplete();
    const HrpgAuth &auth() const;

    QNetworkRequest build_request(QString endpoint, HrpgAuth *authinfo);
    QNetworkRequest build_request(QString endpoint);

signals:
    void resynced();
    void login_failed();

public slots:
    void setAuth(HrpgAuth &newValue);
    void resync();

private:
    HrpgAuth *m_auth;
    bool m_fullyInitialized;
    bool m_auth_valid;
    QNetworkAccessManager m_netman;
protected:
};

#endif // HRPGCLIENT_H
