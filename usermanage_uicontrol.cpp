#include "usermanage_uicontrol.h"


CUserManage_UIControl::CUserManage_UIControl()
{

}

CUserManage_UIControl::CUserManage_UIControl(CAccountTable * ptr_accountTable)
    :m_accountTable(ptr_accountTable),m_currentIndex(-1)
{
     m_currentRecord = new  OneUserInfo();
     m_currentRecord->name = "";
     m_currentRecord->password = "";
     m_currentRecord->permission = 0;
}

bool CUserManage_UIControl::set_Status(Operation_Status current_op_status)
{
   m_Current_Op_Status = current_op_status;
   return true;
}

bool CUserManage_UIControl::set_index(int index)
{
    m_currentIndex = index;
    return true;
}

int CUserManage_UIControl::getIndex()
{
    return m_currentIndex;
}

bool CUserManage_UIControl::set_CurrentRecord(const OneUserInfo * currentRecord)
{
    if(currentRecord!=NULL)
    {
       m_currentRecord->name = currentRecord->name;
       m_currentRecord->password = currentRecord->password;
       m_currentRecord->permission = currentRecord->permission;
    }
    return true;
}

OneUserInfo *CUserManage_UIControl::getCurrentRecord()
{
    return m_currentRecord;
}

bool CUserManage_UIControl::set_Name(QString strName)
{
    m_currentRecord->name = strName;
    return true;
}

bool CUserManage_UIControl::set_Password(QString strPassword)
{
    m_currentRecord->password = strPassword;
    return true;
}

CUserManage_UIControl::~CUserManage_UIControl()
{
    delete m_currentRecord;
}


bool CUserManage_UIControl::set_Permission(uint value,int shifting)
{
    if(shifting != -1)
    {
        uint permission_temp = m_currentRecord->permission;
        permission_temp = permission_temp & (~(0x03<<shifting));
        permission_temp = permission_temp | (value << shifting);
        m_currentRecord->permission = permission_temp;
        return true;
    }
    else
    {
        return false;
    }

}

Operation_Result CUserManage_UIControl::ProcessOKEvent()
{
    Operation_Result ret = Operation_Success;
    switch (m_Current_Op_Status)
    {
    case Op_Idle:
    {

    }
        break;
    case Op_Add:
    {
        ret = m_accountTable->addOneRecord(*m_currentRecord);
    }
        break;
    case Op_Update:
    {
        ret = m_accountTable->UpdateOneRecord(*m_currentRecord);
    }
        break;
    case Op_Query:
    {

    }
        break;
    case Op_Delete:
    {
        m_accountTable->DeleteOneRecord(*m_currentRecord);
    }
        break;
    default:
        break;
    }

    return ret;
}
