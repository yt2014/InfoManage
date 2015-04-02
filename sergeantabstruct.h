#ifndef SERGEANTABSTRUCT_H
#define SERGEANTABSTRUCT_H

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QDate>

class CSergeant_Abstruct_Member
{
private:
    QString m_Name;
    uint m_IndicateNumber;
    uint m_LatestTotalScore;
    QString m_Department;
    QDate m_AccessDate;
public:
    void setLatestTotalScore(uint score);
    uint getLatestTotalScore(void);
    void setLastAccessDate(QDate AccessDate);
    CSergeant_Abstruct_Member();
    virtual ~CSergeant_Abstruct_Member();
};

#endif // SERGEANTABSTRUCT_H

