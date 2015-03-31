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

    if(db.isOpen())
    {
        db.close();
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
                   oneinfo.permission = query.value(index_permission).toInt();

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

bool CAccountTable::isUserNameExist(OneUserInfo RecordToStore)
{
    QString strToFind =  RecordToStore.name;

    int num_records = m_UserInfoList.count();
    int i=0;
    for(i=0;i<num_records;i++)
    {
        if(m_UserInfoList.at(i).name == strToFind)
            break;
    }
    if(i<num_records)
    {
        return true;
    }
    else
    {
        return false;
    }

}

Operation_Result CAccountTable::addOneRecord(OneUserInfo RecordToStore)
{
    Operation_Result value_ret = AddFailed;



     if(db.isOpen())
     {
        value_ret =  DataBaseNotOpen;
     }
     else
     {
         if(isUserNameExist(RecordToStore))
         {
             value_ret = AddExistRecord;
         }
         else
         {
             QSqlQuery query(db);

             QString strSQL = "insert into " + m_TableName + " (UserName,password,permission) values (\'"
                                                              + RecordToStore.name + "\',\'"
                                                              + RecordToStore.password + "\',"
                                                              + RecordToStore.permission + ")";
            if(query.exec(strSQL))
            {
                value_ret = Operation_Success;
            }
            else
            {
                value_ret = AddFailed;
            }

         }

     }

return value_ret;

}
Operation_Result CAccountTable::UpdateOneRecord(OneUserInfo RecordToUpdate)
{
    Operation_Result value_ret = UpdateFailed;

    if(db.isOpen())
    {
       value_ret =  DataBaseNotOpen;
    }
    else
    {
        if(!isUserNameExist(RecordToStore))
        {
            value_ret = UpdateFailed;
        }
        else
        {
            QSqlQuery query(db);

            QString strSQL = "update " + m_TableName + " set password = '" + RecordToUpdate.password
                                                        +"',permission = " + RecordToUpdate.permission
                                                        +" where UserName = '" + RecordToUpdate.name
                                                        +"'";
           if(query.exec(strSQL))
           {
               value_ret = Operation_Success;
           }
           else
           {
               value_ret = UpdateFailed;
           }

        }

    }

    return value_ret;
}
Operation_Result CAccountTable::DeleteOneRecord(OneUserInfo RecordToDelete)
{
    Operation_Result value_ret = DeleteFailed;

    if(db.isOpen())
    {
       value_ret =  DataBaseNotOpen;
    }
    else
    {
        if(!isUserNameExist(RecordToStore))
        {
            value_ret = DeleteNotExistRecord;
        }
        else
        {
            QSqlQuery query(db);

            QString strSQL = "delete from " + m_TableName + " where UserName = '" + RecordToDelete.name
                                                        +"'";
           if(query.exec(strSQL))
           {
               value_ret = Operation_Success;
           }
           else
           {
               value_ret = DeleteFailed;
           }

        }

    }

    return value_ret;
}
