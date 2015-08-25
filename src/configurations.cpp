#include "configurations.h"

#include <iostream>
using namespace std;

configurations::configurations(QObject *parent) :
    QObject(parent)
{
}

/**************************************************************************************
 *     Load configurations for the program
 *     @fileName : File name with the path to the configraitons xml file.
 **************************************************************************************/
void configurations::load(QString fileName)
{


    // Open the xml file and load it to the memory
    // -----------------------------------------------
            QDomDocument doc("xml");
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly))
            {
                cout << "XMLR -  configurations::load - file.Open : " << file.errorString().toStdString() <<"\n";
                return;
            }
            if (!doc.setContent(&file)) {
                file.close();
                cout << "XMLR - configurations::load doc.setConnect :" << file.errorString().toStdString() <<"\n";
                return;
            }
            file.close();

            QDomElement configurationsElement = doc.documentElement();
            QDomNode databaseChiledNode  = configurationsElement.firstChild();

            while (!databaseChiledNode.isNull()) { // For all Database Chiled Nodes
                   QDomElement databaseChiledElement = databaseChiledNode.toElement();

                      // Get All configurations for Soruce Database.
                      // --------------------------------------------------------------------------

                            if(databaseChiledElement.tagName() == "sourceType")  // Get source Databse Type.
                            {
                                    QDomNode sourceTypeNode = databaseChiledNode.firstChild();
                                    this->sourceDatabaseType  = sourceTypeNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourceHost")  // Get source Databse host name.
                            {
                                    QDomNode sourceHostNameNode = databaseChiledNode.firstChild();
                                    this->sourceHostName  = sourceHostNameNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourceName")  // Get source Databse name.
                            {
                                    QDomNode sourceNameNode = databaseChiledNode.firstChild();
                                    this->sourceDatabaseName  = sourceNameNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourceUser")  // Get source User name.
                            {
                                    QDomNode sourceUserNode = databaseChiledNode.firstChild();
                                    this->sourceUserName  = sourceUserNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourcePassword")  // Get source password.
                            {
                                    QDomNode sourcePasswordNode = databaseChiledNode.firstChild();
                                    this->sourcePassword  = sourcePasswordNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourcePort")  // Get source Databse port.
                            {
                                    QDomNode sourcePortNode = databaseChiledNode.firstChild();
                                    this->sourcePort  = sourcePortNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourcePrefix")  // Get source Databse prefix.
                            {
                                    QDomNode sourcePrefixNode = databaseChiledNode.firstChild();
                                    this->sourcePrefix  = sourcePrefixNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourceDomainsTableName")  // Get source Domains Table Name.
                            {
                                    QDomNode sourceDomainsTableNameNode = databaseChiledNode.firstChild();
                                    this->sourceDomainsTableName  = sourceDomainsTableNameNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourceURLsTableName")  // Get source URLs Table Name.
                            {
                                    QDomNode sourceURLsTableNameNode = databaseChiledNode.firstChild();
                                    this->sourceURLsTableName  = sourceURLsTableNameNode.toText().data();
                            }

                            if(databaseChiledElement.tagName() == "sourceEmailsTableName")  // Get source Emails Table Name.
                            {
                                    QDomNode sourceEmailsTableNameNode = databaseChiledNode.firstChild();
                                    this->sourceEmailsTableName  = sourceEmailsTableNameNode.toText().data();
                            }
                     // --------------------------------------------------------------------------


                     // Get All configurations for Target Database.
                     // --------------------------------------------------------------------------

                               if(databaseChiledElement.tagName() == "targetType")  // Get target Databse Type.
                               {
                                       QDomNode targetTypeNode = databaseChiledNode.firstChild();
                                       this->targetDatabaseType  = targetTypeNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetHost")  // Get target Databse host name.
                               {
                                       QDomNode targetHostNameNode = databaseChiledNode.firstChild();
                                       this->targetHostName  = targetHostNameNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetName")  // Get target Databse name.
                               {
                                       QDomNode targetNameNode = databaseChiledNode.firstChild();
                                       this->targetDatabaseName  = targetNameNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetUser")  // Get target User name.
                               {
                                       QDomNode targetUserNode = databaseChiledNode.firstChild();
                                       this->targetUserName  = targetUserNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetPassword")  // Get target password.
                               {
                                       QDomNode targetPasswordNode = databaseChiledNode.firstChild();
                                       this->targetPassword  = targetPasswordNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "sourcePort")  // Get target Databse port.
                               {
                                       QDomNode targetPortNode = databaseChiledNode.firstChild();
                                       this->targetPort  = targetPortNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetPrefix")  // Get target Databse prefix.
                               {
                                       QDomNode targetPrefixNode = databaseChiledNode.firstChild();
                                       this->targetPrefix  = targetPrefixNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetDomainsTableName")  // Get target Domains Table Name.
                               {
                                       QDomNode targetDomainsTableNameNode = databaseChiledNode.firstChild();
                                       this->targetDomainsTableName  = targetDomainsTableNameNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetURLsTableName")  // Get target URLs Table Name.
                               {
                                       QDomNode targetURLsTableNameNode = databaseChiledNode.firstChild();
                                       this->targetURLsTableName  = targetURLsTableNameNode.toText().data();
                               }

                               if(databaseChiledElement.tagName() == "targetEmailsTableName")  // Get target Emails Table Name.
                               {
                                       QDomNode targetEmailsTableNameNode = databaseChiledNode.firstChild();
                                       this->targetEmailsTableName  = targetEmailsTableNameNode.toText().data();
                               }

                       // --------------------------------------------------------------------------


                            if(databaseChiledElement.tagName() == "WAITE_TIME")  // Get WAITE_TIME.
                            {
                                    QDomNode WAITE_TIMENode = databaseChiledNode.firstChild();
                                    this->WAITE_TIME  = WAITE_TIMENode.toText().data().toInt();
                            }

                            if(databaseChiledElement.tagName() == "PROGRESS_PAR_SHOW_TIME")  // Get PROGRESS_PAR_SHOW_TIME.
                            {
                                    QDomNode PROGRESS_PAR_SHOW_TIMENode = databaseChiledNode.firstChild();
                                    this->PROGRESS_PAR_SHOW_TIME  = PROGRESS_PAR_SHOW_TIMENode.toText().data().toInt();
                            }

               databaseChiledNode = databaseChiledNode.nextSibling();
            }
}
