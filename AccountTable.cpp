#include "AccountTable.h"

CAccountTable::CAccountTable(QString DatabaseAlias = "PersonInfo",QString TableName = "Account")
{
    m_DatabaseAlias = DatabaseAlias;
    m_TableName = TableName;
    m_UserInfoList = UserInfoList();
}

CAccountTable::~CAccountTable()
{
    if(m_UserInfoList.count()!=0)
    {
       m_UserInfoList.clear();
    }
}

void CAccountTable::setDatabaseAlias(QString DatabaseAlias)
{
     m_DatabaseAlias = DatabaseAlias;
}

void CAccountTable::setTableName(QString TableName)
{
    m_TableName = TableName;
}
