#ifndef SERGEANTABSTRUCT_H
#define SERGEANTABSTRUCT_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QDate>


typedef struct
{
   QString m_Name;
   uint m_IndicateNumber;
   uint m_LatestTotalScore;
   QString m_Department;
   QDate m_AccessDate;
}Sergeant_Common;


class CSergeant_Common
{
private:
     Sergeant_Common m_Ser_Common;
public:

     QSqlDatabase db;

    CSergeant_Common();
    CSergeant_Common(Sergeant_Common);
    virtual ~CSergeant_Common();
    virtual void Store_Common();
};

#endif // SERGEANTABSTRUCT_H

