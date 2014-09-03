#ifndef HRPGTASK_H
#define HRPGTASK_H

#include <QObject>
#include <QDateTime>
//#include <QStr
class QUuid;
class QJsonValue;
class QString;
class QDateTime;

class HrpgTask : public QObject
{
    Q_OBJECT
    Q_ENUMS(TaskType)
    Q_PROPERTY(TaskType taskType READ taskType)
    Q_PROPERTY(QString id READ id)
    Q_PROPERTY(QDateTime dateCreated READ dateCreated)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)

public:
    enum TaskType {
        Habit,
        Daily,
        Todo,
        Reward
    };

    explicit HrpgTask(TaskType type, QObject *parent = 0);


    static HrpgTask* fromJSON(QObject *parent, const QJsonValue& json);

    TaskType taskType() const { return m_taskType; }
    QString id() const { return m_id; }
    QString text() const { return m_text; }
    QDateTime dateCreated() const { return m_dateCreated; }
signals:
    void taskTypeChanged(TaskType t);
    void textChanged(QString text);
public slots:
    void setText(QString &new_text) {
        if (m_text != new_text) {
            m_text = new_text;
            emit textChanged(m_text);
        }
    }

private:
    TaskType m_taskType;
    QString m_id;
    QString m_text;
    QDateTime m_dateCreated;
};

#endif // HRPGTASK_H
