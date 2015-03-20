#include "AccountTable.h"

CAccountTable::CAccountTable(QString DatabaseAlias,QString TableName)
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

UserInfoList CAccountTable::getListAllFromDatabase()
{
    if(m_UserInfoList.count()!=0)
    {
         m_UserInfoList.clear();
    }
    if(openDatabase())
    {
        QSqlQuery query(db);

        QString strSelect = "select * from " + m_TableName;
        if(query.exec(strSelect))
        {
               QSqlRecord columns = query.record();

               int index_Name = columns.indexOf("UserName");
               int index_Password = columns.indexOf("password");
               int index_permission = columns.indexOf("permission");

               while(query.next())
               {
                   OneUserInfo oneinfo;
                   oneinfo.name = query.value(index_Name).toString();
                   oneinfo.password = query.value(index_Password).toString();
                   oneinfo.permission = query.value(index_permission).toString();

                   m_UserInfoList.append(oneinfo);

               }
        }
        return m_UserInfoList;
    }
    else
    {
      //  QMessageBox::warning(this,QObject::tr("warning"),QObject::tr("can't open database!"),QMessageBox::Ok);
        qDebug()<<"can't open database!";
        return m_UserInfoList;
    }
}


bool CAccountTable::openDatabase()
{
    db = QSqlDatabase::database(m_DatabaseAlias,true);

    if(db.isValid()&&db.isOpen())
    {
        return true;
    }
    else
    {
        return false;
    }
}
