#include <QtCore/QCoreApplication>
#include <QApplication>
#include <QtSql>
#include <iostream>
#include <string>
using namespace std;

#include "qarchiver.h"
#include "configurations.h"
#include <process.h>

void printHelp();
void printConfig(QArchiver &theArchiver);

// Crate the Archiver Object
QArchiver archiver ;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    string buffer;
    QString cinBuffer;
    buffer.clear();
    cinBuffer.clear();

    cout <<"\n\n"
         <<"  Natshah Archiver [ Version 1.1.2 ]\n"
         <<"  Copyright (c) 2015 Natshah.com .  All rights reserved.\n\n";


    // Load configurations.
    archiver.config.load("configurations.xml");

    // Print the configurations Menu at the start.
    printConfig(archiver);

    // Create the Connection to the source database.
    if( !archiver.createSourceConnection() )
    {
        cout <<"\n\n"
             <<"     Error Connecting to the Source Database\n"
             <<"     Press Enter to exit ..\n";
        cin.get();
        return 1;
    }

    // Create the Connection to the Target database.
    if( !archiver.createTargetConnection() )
    {
        cout <<"\n\n"
             <<"     Error Connecting to the Target Database\n"
             <<"     Press Enter to exit ..\n";
        cin.get();
        return 1;
    }



    while (buffer !="exit" )
    {
        buffer.clear();
        cinBuffer.clear();

        // Print Archiver Promt.
        cout<<"Archiver> ";
        cin>>buffer;

        cinBuffer = QString::fromStdString(buffer);

            if ( cinBuffer=="start")
            {
                cout <<"\n+-------------------------------------------------------------+\n"
                     <<"|  Start Archiving                                            | \n"
                     <<"+-------------------------------------------------------------+\n\n";
                         archiver.archiving();
                cout <<"\n+-------------------------------------------------------------+\n"
                     <<"|  Finish Archiving                                           |\n"
                     <<"+-------------------------------------------------------------+\n\n";
            }
            else if (cinBuffer=="load")
            {
                // Load configurations.
                archiver.config.load("configurations.xml");
                cout <<"Archiver Settings have been loaded\n\n";
            }
            else if (cinBuffer=="help" || cinBuffer=="-h" || cinBuffer=="-help" || cinBuffer=="-?" || cinBuffer=="?")
                   printHelp();
            else if (cinBuffer=="configurations" || cinBuffer=="config")
                   printConfig(archiver);
            else if (cinBuffer=="clear" || cinBuffer=="cls" )
            {
                   system("cls");
                   a.flush();
                   cout<<"\n";
            }
            else if (cinBuffer=="exit" || cinBuffer=="quite" )
            {
                    cout<<"Bye\n";
                    a.exit();
                    return 0;
            }
            else
            {
                cout <<"'"<<cinBuffer.toStdString()<<"' is not recognized as an internal command\n"
                     <<" for help type 'help' or -h then Press Enter to see list of Commands\n";
                     QApplication::beep();
            }

     }
    return a.exec();
}




void printConfig(QArchiver &theArchiver)
{
    cout <<"\n+-------------------------------------------------------------+\n"
         <<"|        Source Database Configraitons                        |\n"
         <<"+-------------------------------------------------------------+\n"
         <<"|      Database Type : "<< theArchiver.config.sourceDatabaseType.toStdString() <<"\n"
         <<"|          Host Name : "<< theArchiver.config.sourceHostName.toStdString() <<"\n"
         <<"|      Database Name : "<< theArchiver.config.sourceDatabaseName.toStdString() <<"\n"
         <<"|    Database Prefix : "<< theArchiver.config.sourcePrefix.toStdString() <<"\n"
         <<"|   URLs Table Name : "<< theArchiver.config.sourceURLsTableName.toStdString() <<"\n"
         <<"+-------------------------------------------------------------+\n\n"
         <<"+-------------------------------------------------------------+\n"
         <<"|        Target Database Configraitons                        |\n"
         <<"+-------------------------------------------------------------+\n"
         <<"|      Database Type : "<< theArchiver.config.targetDatabaseType.toStdString() <<"\n"
         <<"|          Host Name : "<< theArchiver.config.targetHostName.toStdString() <<"\n"
         <<"|      Database Name : "<< theArchiver.config.targetDatabaseName.toStdString() <<"\n"
         <<"|    Database Prefix : "<< theArchiver.config.targetPrefix.toStdString() <<"\n"
         <<"|    URLs Table Name : "<< theArchiver.config.targetURLsTableName.toStdString() <<"\n"
         <<"+-------------------------------------------------------------+\n\n";
}

// print Help menu
void printHelp()
{
    cout<<"\n+---------------------------------------------------------------+\n"
        <<"|    List of all Archiver commands:                             |\n"
        <<"+---------------------------------------------------------------+\n"
        <<"|  ?                  : Synonym for 'help'.                     |\n"
        <<"|  clear / cls        : Clear the current input statement.      |\n"
        <<"|  exit / quite       : Exit. Same as quit.                     |\n"
        <<"|  help / -h          : Display this help.                      |\n"
        <<"|  load               : Load Settings.                          |\n"
        <<"|  start              : Start Archiving                         |\n"
        <<"|  config             : Show configurations                     |\n"
        <<"+---------------------------------------------------------------+\n\n";
}
