#ifndef ACCOUNTTABLE_H
#define ACCOUNTTABLE_H
#include "DatabaseTable.h"

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QList>
#include <QVariant>
#include <QDebug>

typedef struct
{
    QString name;
    QString password;
    QString permission;
}OneUserInfo;

typedef QList<OneUserInfo> UserInfoList;


class CAccountTable:CDatabaseTable
{
public:
    CAccountTable(QString DatabaseAlias = "PersonInfo",QString TableName = "Account");
    virtual ~CAccountTable();
    void setDatabaseAlias(QString DatabaseAlias);
    void setTableName(QString TableName);
    UserInfoList getListAllFromDatabase();
    bool isUserNameExist(OneUserInfo RecordToStore);
    bool openDatabase();
    Operation_Result addOneRecord(OneUserInfo RecordToStore);
    Operation_Result UpdateOneRecord(OneUserInfo RecordToUpdate);
    Operation_Result DeleteOneRecord(OneUserInfo RecordToDelete);
private:
    QString m_DatabaseAlias;
    QString m_TableName;
    UserInfoList m_UserInfoList;
    QSqlDatabase db;
};

#endif // ACCOUNTTABLE_H
