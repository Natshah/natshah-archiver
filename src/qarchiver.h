#ifndef QARCHIVER_H
#define QARCHIVER_H


#include <QObject>
#include <QSemaphore>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QtSql>
#include <QDir>
#include <QtNetwork>
#include <QTextStream>
#include <QStringList>
#include <QTimer>

#include "configurations.h"

class QFile;
class QHttp;
class QHttpResponseHeader;

class QSslError;
class QAuthenticator;
class QNetworkReply;
class QStringList;
class QArchiver : public QObject
{
    Q_OBJECT
public:
    explicit QArchiver(QObject *parent = 0);

    void archiving();
    bool areThereNotArchivedDomains();
    bool areThereNotArchivedURLs();
    bool areThereNotArchivedEmails();

    void setArchivedDomains(QString theDomain,int states);
    void setArchivedURLs(QString theURL,int states);
    void setArchivedEmails(QString theEmail,int states);

    void archiveFirstNotArchivedDomain();
    void archiveFirstNotArchivedURL();
    void archiveFirstNotArchivedEmail();

    bool createSourceConnection();
    bool createTargetConnection();

    bool this_domain_in_the_database(QString theDomain);
    bool this_URL_in_the_database(QString theURL);
    bool this_email_in_the_database(QString theEmail);


    QSqlDatabase sourceDB;
    QSqlDatabase targetDB;

    configurations config;
signals:
public slots:

};

#endif // QARCHIVER_H
