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
    int getIndex(void);
    //set_CurrentRecord is used in Op_Idle and Op_Query status.
    bool set_CurrentRecord(const OneUserInfo * currentRecord);
    OneUserInfo * getCurrentRecord(void);
    //the following 3 member functions are used in Op_Add, Op_Update,Op_Delete.
    bool set_Name(QString strName);
    bool set_Password(QString strPassword);
    bool set_Permission(uint value,int shifting);
    Operation_Result ProcessOKEvent();
    CUserManage_UIControl();
    CUserManage_UIControl(CAccountTable * ptr_accountTable);

    virtual ~CUserManage_UIControl();

};

#endif // USERMANAGE_UICONTROL_H

