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
    uint permission;
}OneUserInfo;

#define PERMISSION_SHIFT_USER 0
#define PERMISSION_SHIFT_SERGEANT 2
#define PERMISSION_SHIFT_CADRES 4
#define PERMISSION_SHIFT_OPERATOR 6
#define PERMISSION_SHIFT_SECRETMAN 8
#define PERMISSION_SHIFT_INVALID 10


typedef QList<OneUserInfo> UserInfoList;


class CAccountTable:CDatabaseTable
{
public:
    CAccountTable(QString DatabaseAlias = "PersonInfo",QString TableName = "Account");
    virtual ~CAccountTable();
    void setDatabaseAlias(QString DatabaseAlias);
    void setTableName(QString TableName);
    UserInfoList getListAllFromDatabase();
    int isUserNameExist(OneUserInfo RecordToStore);//if not exist, return value set to -1, else return value set to the index.
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
