#include "qarchiver.h"

#include <iostream>
using namespace std;

QArchiver::QArchiver(QObject *parent) :
    QObject(parent)
{
}

/**************************************************
 * Archiving Source Database to the Target database.
 **************************************************/
void QArchiver::archiving()
{

    cout <<"\n+-------------------------------------------------------------+\n"
         <<"|  Start Domains Archiving                                    | \n"
         <<"+-------------------------------------------------------------+\n\n";
                // Archiving Domains.
                while(this->areThereNotArchivedDomains())
                 this->archiveFirstNotArchivedDomain();
    cout <<"\n+-------------------------------------------------------------+\n"
         <<"|  Finish Domains Archiving                                   |\n"
         <<"+-------------------------------------------------------------+\n\n";



    cout <<"\n+-------------------------------------------------------------+\n"
         <<"|  Start URLs Archiving                                       | \n"
         <<"+-------------------------------------------------------------+\n\n";
            // Archiving URLs.
            while(this->areThereNotArchivedURLs())
              this->archiveFirstNotArchivedURL();
    cout <<"\n+-------------------------------------------------------------+\n"
         <<"|  Finish URLs Archiving                                      |\n"
         <<"+-------------------------------------------------------------+\n\n";

    cout <<"\n+-------------------------------------------------------------+\n"
         <<"|  Start Emails Archiving                                     | \n"
         <<"+-------------------------------------------------------------+\n\n";

                // Archiving Emails.
                while(this->areThereNotArchivedEmails())
                    this->archiveFirstNotArchivedEmail();
    cout <<"\n+-------------------------------------------------------------+\n"
         <<"|  Finish Emails Archiving                                    |\n"
         <<"+-------------------------------------------------------------+\n\n";





}

/**************************************************
 *  Are There No Archived Domains.
 *  return : ture if not and false if still there are
 **************************************************/
bool QArchiver::areThereNotArchivedDomains()
{
    QSqlQuery squery(sourceDB);
    squery.prepare("SELECT COUNT(id) FROM "+config.sourcePrefix+config.sourceDomainsTableName+" WHERE archived='0' limit 0,1 ");
    squery.exec();

    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::areThereNotArchivedDomains : " << squery.lastError().text().toStdString() <<"\n";

    squery.next();
    if (squery.value(0).toInt()<1)
        return false;
    else
        return true;

}

/**************************************************
 *  Are There No Archived URLs.
 *  return : ture if not and false if still there are
 **************************************************/
bool QArchiver::areThereNotArchivedURLs()
{
    QSqlQuery squery(sourceDB);
    squery.prepare("SELECT COUNT(id) FROM "+config.sourcePrefix+config.sourceURLsTableName+" WHERE archived='0' limit 0,1 ");
    squery.exec();

    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::areThereNotArchivedURLs : " << squery.lastError().text().toStdString() <<"\n";

    squery.next();
    if (squery.value(0).toInt()<1)
        return false;
    else
        return true;
}

/**************************************************
 *  Are There No Archived Eamils.
 *  return : ture if not and false if still there are
 **************************************************/
bool QArchiver::areThereNotArchivedEmails()
{
    QSqlQuery squery(sourceDB);
    squery.prepare("SELECT COUNT(id) FROM "+config.sourcePrefix+config.sourceEmailsTableName+" WHERE archived='0' limit 0,1 ");
    squery.exec();

    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::areThereNotArchivedEmails : " << squery.lastError().text().toStdString() <<"\n";

    squery.next();
    if (squery.value(0).toInt()<1)
        return false;
    else
        return true;
}




/**************************************************
 *  Are There No Archived Domains.
 **************************************************/
void QArchiver::setArchivedDomains(QString theDomain,int states)
{
    QSqlQuery squery(sourceDB);
    squery.prepare("UPDATE "+config.sourcePrefix+config.sourceDomainsTableName+" SET archived=:states WHERE domain=:thedomain ");
    squery.bindValue(":states",states);
    squery.bindValue(":thedomain",theDomain);
    squery.exec();
    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::setArchivedDomains : " << squery.lastError().text().toStdString() <<"\n";

     cout << "Domain : " << theDomain.toStdString() <<"\n";
}

/**************************************************
 *  Set Archived URLS to 0 or 1 .
 **************************************************/
void QArchiver::setArchivedURLs(QString theURL,int states)
{
    QSqlQuery squery(sourceDB);
    squery.prepare("UPDATE "+config.sourcePrefix+config.sourceURLsTableName+" SET archived=:states WHERE url=:theurl ");
    squery.bindValue(":states",states);
    squery.bindValue(":theurl",theURL);
    squery.exec();
    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::setArchivedURLs : " << squery.lastError().text().toStdString() <<"\n";

     cout << "URL : " << theURL.toStdString() <<"\n";
}

/**************************************************
 *  Set Archived Emails to 0 or 1 .
 **************************************************/
void QArchiver::setArchivedEmails(QString theEmail,int states)
{
    QSqlQuery squery(sourceDB);
    squery.prepare("UPDATE "+config.sourcePrefix+config.sourceEmailsTableName+" SET archived=:states WHERE email=:theemail ");
    squery.bindValue(":states",states);
    squery.bindValue(":theemail",theEmail);
    squery.exec();
    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::setArchivedEmails : " << squery.lastError().text().toStdString() <<"\n";

    cout << "Email : " << theEmail.toStdString() <<"\n";
}


/**************************************************
 *  Set Archived Domains to 0 or 1 .
 **************************************************/
void QArchiver::archiveFirstNotArchivedDomain()
{
    QSqlQuery squery(sourceDB);
    squery.prepare("SELECT domain FROM "+config.sourcePrefix+config.sourceDomainsTableName+" WHERE archived='0' LIMIT 0,1 ");
    squery.exec();

    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::archiveFirstNotArchivedDomains(): Get First Not Archived : " << squery.lastError().text().toStdString() <<"\n";
    squery.next();



    if(this->this_domain_in_the_database(squery.value(0).toString()))
    {
        //  Add the domain
        QSqlQuery tquery(targetDB);
        tquery.prepare("INSERT INTO "+config.targetPrefix+config.targetDomainsTableName+" VALUES (NULL, :domain,1 ,1 ,1 )");
        tquery.bindValue(":domain",squery.value(0).toString());
        tquery.exec();
        if (!tquery.isActive())
            cout << "\n\tDBE - QArchiver::archiveURLs : Save Archived URL : " << tquery.lastError().text().toStdString() <<"\n";

    }



    // Set the domain as Archived in the Soruce Database..
    setArchivedDomains(squery.value(0).toString(),1);


}

/**************************************************
*  Do Archive the first not Archived URL
**************************************************/
void QArchiver::archiveFirstNotArchivedURL()
{

    QSqlQuery squery(sourceDB);
    squery.prepare("SELECT url,data FROM "+config.sourcePrefix+config.sourceURLsTableName+" WHERE archived='0' LIMIT 0,1 ");
    squery.exec();

    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::archiveURLs : Get First Not Archived : " << squery.lastError().text().toStdString() <<"\n";
    squery.next();


    if(this->this_URL_in_the_database(squery.value(0).toString()))
    {
        QSqlQuery tquery(targetDB);
        tquery.prepare("INSERT INTO "+config.targetPrefix+config.targetURLsTableName+" VALUES (NULL, :url, :data,1 ,1 ,1 )");
        tquery.bindValue(":url",squery.value(0).toString());
        tquery.bindValue(":data",squery.value(1).toString());

        tquery.exec();
        if (!tquery.isActive())
            cout << "\n\tDBE - QArchiver::archiveURLs : Save Archived URL : " << tquery.lastError().text().toStdString() <<"\n";

    }



    // Set the URL as Archived in the Soruce Database..
    setArchivedURLs(squery.value(0).toString(),1);

}


/**************************************************
*  Do Archive the first not Archived Email
**************************************************/
void QArchiver::archiveFirstNotArchivedEmail()
{

    QSqlQuery squery(sourceDB);
    squery.prepare("SELECT email FROM "+config.sourcePrefix+config.sourceEmailsTableName+" WHERE archived='0' LIMIT 0,1 ");
    squery.exec();

    if (!squery.isActive())
        cout << "\n\tDBE - QArchiver::archiveFirstNotArchivedEmail : Get First Not Archived : " << squery.lastError().text().toStdString() <<"\n";
    squery.next();


    if(this->this_email_in_the_database(squery.value(0).toString()))
    {
        QSqlQuery tquery(targetDB);
        tquery.prepare("INSERT INTO "+config.targetPrefix+config.targetEmailsTableName+" VALUES (NULL, :theemail,1 ,1 ,1 )");
        tquery.bindValue(":theemail",squery.value(0).toString());

        tquery.exec();
        if (!tquery.isActive())
            cout << "\n\tDBE - QArchiver::archiveFirstNotArchivedEmail : Save Archived URL : " << tquery.lastError().text().toStdString() <<"\n";


    }


    // Set this Email as Archived in the Soruce Database..
    this->setArchivedEmails(squery.value(0).toString(),1);

}


/**************************************************
*  Create Connection to the Source database.
**************************************************/
bool QArchiver::createSourceConnection()
{
        sourceDB = QSqlDatabase::addDatabase(config.sourceDatabaseType,"sourceDB");
        sourceDB.setHostName(config.sourceHostName);
        sourceDB.setDatabaseName(config.sourceDatabaseName);
        sourceDB.setUserName(config.sourceUserName);
        sourceDB.setPassword(config.sourcePassword);
        sourceDB.setPort(config.sourcePort.toInt());

        if( !sourceDB.open() )
        {
            cout << "\n\tSource Database Connection Error :  " << sourceDB.lastError().text().toStdString() <<"\n";
                return false;
        }
        return true;
}

/**************************************************
*  Create Connection to the Source database.
**************************************************/
bool QArchiver::createTargetConnection()
{
        targetDB = QSqlDatabase::addDatabase(config.targetDatabaseType,"targetDB");
        targetDB.setHostName(config.targetHostName);
        targetDB.setDatabaseName(config.targetDatabaseName);
        targetDB.setUserName(config.targetUserName);
        targetDB.setPassword(config.targetPassword);
        targetDB.setPort(config.targetPort.toInt());

        if( !targetDB.open() )
        {
            cout << "\n\tTarget Database Connection Error :  " << targetDB.lastError().text().toStdString() <<"\n";
                return false;
        }
        return true;
}

/*************************************************************************************************
 * Is this URL in the Database.
 * @theURL : the URL link as String.
 * Return True if the URL is in the database and False if not.
 *************************************************************************************************/
bool QArchiver::this_URL_in_the_database(QString theURL)
{
    QSqlQuery tquery(this->targetDB);
    tquery.prepare("SELECT COUNT(id) FROM "+config.targetPrefix+config.targetURLsTableName+" WHERE url= '"+theURL+"' ");
    tquery.exec();

    if (!tquery.isActive())
        cout << "\n\tDBE - QArchiver::this_URL_in_the_database : " << tquery.lastError().text().toStdString() <<"\n";

    tquery.next();
    if (tquery.value(0).toInt()<1)
        return false;
    else
        return true;
}

/*************************************************************************************************
 * Is this Domian in the Database.
 * @theDomain : the Domain name as String.
 * Return True if the URL is in the database and False if not.
 *************************************************************************************************/
bool QArchiver::this_domain_in_the_database(QString theDomain)
{
    QSqlQuery tquery(this->targetDB);
    tquery.prepare("SELECT COUNT(id) FROM "+config.targetPrefix+config.targetDomainsTableName+" WHERE domain= '"+theDomain+"' ");
    tquery.exec();

    if (!tquery.isActive())
        cout << "\n\tDBE - QArchiver::this_domain_in_the_database : " << tquery.lastError().text().toStdString() <<"\n";

    tquery.next();
    if (tquery.value(0).toInt()<1)
        return false;
    else
        return true;
}

/*************************************************************************************************
 * Is this Email in the Database.
 * @theEmail : the Email name as String.
 * Return True if the Email is in the database and False if not.
 *************************************************************************************************/
bool QArchiver::this_email_in_the_database(QString theEmail)
{
    QSqlQuery tquery(this->targetDB);
    tquery.prepare("SELECT COUNT(id) FROM "+config.targetPrefix+config.targetEmailsTableName+" WHERE email= '"+theEmail+"' ");
    tquery.exec();

    if (!tquery.isActive())
        cout << "\n\tDBE - QArchiver::this_email_in_the_database : " << tquery.lastError().text().toStdString() <<"\n";

    tquery.next();
    if (tquery.value(0).toInt()<1)
        return false;
    else
        return true;
}
