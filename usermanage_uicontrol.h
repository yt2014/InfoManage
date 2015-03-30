#ifndef USERMANAGE_UICONTROL_H
#define USERMANAGE_UICONTROL_H

#include "AccountTable.h"



typedef enum
{
    Op_Idle,
    Op_Add,
    Op_Update,
    Op_Delete,
    Op_Query
}Operation_Status;


class CUserManage_UIControl
{
private:
    Operation_Status m_Current_Op_Status;
    CAccountTable * m_accountTable;
    int m_currentIndex;
    OneUserInfo * m_currentRecord;
public:
    bool set_Status(Operation_Status current_op_status);
    bool set_index(int index);
    bool set_CurrentRecord(OneUserInfo * currentRecord);
    bool set_Permission(uint Permission);
    CUserManage_UIControl();
    CUserManage_UIControl(CAccountTable * ptr_accountTable);

    virtual ~CUserManage_UIControl();

};

#endif // USERMANAGE_UICONTROL_H

