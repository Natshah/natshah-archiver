#ifndef configurations_H
#define configurations_H

#include <QObject>
#include <QXmlReader>
#include <QDomDocument>
#include <QDir>

class configurations : public QObject
{
    Q_OBJECT
public:
    explicit configurations(QObject *parent = 0);

    void load(QString fileName);

signals:

public slots:

public:

    // for Source Database.
    QString sourceDatabaseType;
    QString sourceHostName;
    QString sourceDatabaseName;
    QString sourceUserName;
    QString sourcePassword;
    QString sourcePort;
    QString sourcePrefix;
    QString sourceURLsTableName;
    QString sourceDomainsTableName;
    QString sourceEmailsTableName;

    // for Target Database.
    QString targetDatabaseType;
    QString targetHostName;
    QString targetDatabaseName;
    QString targetUserName;
    QString targetPassword;
    QString targetPort;
    QString targetPrefix;
    QString targetURLsTableName;
    QString targetDomainsTableName;
    QString targetEmailsTableName;

    // for timeing.
    int WAITE_TIME;
    int PROGRESS_PAR_SHOW_TIME;
};

#endif // configurations_H
