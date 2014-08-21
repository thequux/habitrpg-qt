#ifndef HRPGAUTH_H
#define HRPGAUTH_H

#include <QObject>
#include <QString>

class HrpgAuth : public QObject {
    // I expect that my parent object will be the HrpgClient object
    Q_OBJECT

    Q_PROPERTY(QString uuid READ uuid WRITE setUuid)
    Q_PROPERTY(QString apiKey READ apiKey WRITE setApiKey)

public:
    explicit HrpgAuth(QObject *parent = 0);
    QString &uuid() { return m_uuid; }
    QString &apiKey() { return m_apiKey; }

    bool operator==(HrpgAuth &other) {
        return this->uuid() == other.uuid()
                && this->apiKey() == other.apiKey();
    }
    bool operator!=(HrpgAuth &other) {
        return !(*this == other);
    }

    HrpgAuth& operator=(const HrpgAuth& other) {
        this->m_apiKey = other.m_apiKey;
        this->m_uuid = other.m_uuid;
        return *this;
    }

public slots:
    void setUuid(QString &value);
    void setApiKey(QString &value);

private:
    QString m_uuid;
    QString m_apiKey;


};


#endif // HRPGAUTH_H
