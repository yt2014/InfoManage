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
     m_currentRecord->permission = "";
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

bool CUserManage_UIControl::set_CurrentRecord(OneUserInfo * currentRecord)
{
    if(currentRecord!=NULL)
    {
        m_currentRecord->name = currentRecord->name;
        m_currentRecord->password = currentRecord->password;
        m_currentRecord->permission = currentRecord->permission;
    }
    return true;
}


CUserManage_UIControl::~CUserManage_UIControl()
{
    delete m_currentRecord;
}

bool CUserManage_UIControl::set_Permission(uint Permission)
{
    m_currentRecord->permission = QString.number(Permission);
}
