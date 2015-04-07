#include "sergeantabstruct.h"


CSergeant_Common::CSergeant_Common()
{
    db = QSqlDatabase::database("PersonInfo",true);

}

void CSergeant_Common::Store_Common()
{

}

CSergeant_Common::~CSergeant_Common()
{
    if(db.isOpen())
    {
        db.close();
    }

}

CSergeant_Common::CSergeant_Common(Sergeant_Common common_filds)
{
    //open the data base.
    db = QSqlDatabase::database("PersonInfo",true);

    m_Ser_Common.m_Name = common_filds.m_Name;
    m_Ser_Common.m_AccessDate = common_filds.m_AccessDate;
    m_Ser_Common.m_Department = common_filds.m_Department;
    m_Ser_Common.m_IndicateNumber = common_filds.m_IndicateNumber;
    m_Ser_Common.m_LatestTotalScore = common_filds.m_LatestTotalScore;
}
