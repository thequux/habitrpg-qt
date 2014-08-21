#ifndef HRPGCLIENT_H
#define HRPGCLIENT_H

#include <QObject>
#include <QQmlParserStatus>
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

signals:
    void userChanged();

public slots:
    void setAuth(HrpgAuth &newValue);

private:
    void try_login(HrpgAuth &auth);

    HrpgAuth *m_auth;
    bool m_fullyInitialized;

};

#endif // HRPGCLIENT_H
