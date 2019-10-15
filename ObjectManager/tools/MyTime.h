#ifndef __MYTIME_H__
#define __MYTIME_H__

#include <time.h>
#include <string>


///////////////////////////////////////////////////////////////////////////////

class MyTimeSpan
{
public:
    MyTimeSpan() : m_timeSpan(0)
    {}

    MyTimeSpan( time_t time ) : m_timeSpan(time)
    {}

    MyTimeSpan( int lDays, int nHours, int nMins, int nSecs)
    {
    m_timeSpan = nSecs + 60* (nMins + 60* (nHours + 24 * lDays));
    }

    int getDays() const {
    return( (int)m_timeSpan / (24*3600) );
    }

    int getTotalHours() const {
    return ( (int)m_timeSpan / 3600 );
    }

    int getHours() const {
    return (getTotalHours() % 24);
    }

    int getTotalMinutes() const {
    return ( (int)m_timeSpan / 60);
    }

    int getMinutes() const {
    return (getTotalMinutes() % 60);
    }

    int getTotalSeconds() const {
    return (int)m_timeSpan;
    }

    int getSeconds() const {
    return ( (int)m_timeSpan % 60);
    }

    time_t getTimeSpan() const {
    return m_timeSpan;
    }

    MyTimeSpan operator+( MyTimeSpan span ) const {
    return( MyTimeSpan( m_timeSpan+span.m_timeSpan ) );
    }

    MyTimeSpan operator-( MyTimeSpan span ) const {
    return( MyTimeSpan( m_timeSpan-span.m_timeSpan ) );
    }

    MyTimeSpan& operator+=( MyTimeSpan span ) {
    m_timeSpan += span.m_timeSpan;
    return( *this );
    }

    MyTimeSpan& operator-=( MyTimeSpan span ) {
    m_timeSpan -= span.m_timeSpan;
    return( *this );
    }

    bool operator==( MyTimeSpan span ) const {
    return( m_timeSpan == span.m_timeSpan );
    }

    bool operator!=( MyTimeSpan span ) const {
    return( m_timeSpan != span.m_timeSpan );
    }

    bool operator<( MyTimeSpan span ) const {
    return( m_timeSpan < span.m_timeSpan );
    }

    bool operator>( MyTimeSpan span ) const {
    return( m_timeSpan > span.m_timeSpan );
    }

    bool operator<=( MyTimeSpan span ) const {
    return( m_timeSpan <= span.m_timeSpan );
    }

    bool operator>=( MyTimeSpan span ) const {
    return( m_timeSpan >= span.m_timeSpan );
    }

public:
    //  * the only valid formats:
    //  %D - # of days
    //  %H - hour in 24 hour format
    //  %M - minute (0-59)
    //  %S - seconds (0-59)
    //  %% - percent sign
    std::string tostr(const char* pszFormat = "%D/%H/%M/%S") const;

private:
    time_t m_timeSpan;
};


class MyTime
{
public:
    static MyTime now() {
    return MyTime(time(NULL));
    }

    // parse time from string, avaliable format: %[w](y|Y|m|d|H|M|S)
    // %Y: long year field (1970-2026), %y: short year field(00-26)
    // %m: month field (1-12), %d: day field (1-31), 
    // %H: hour filed (0-23),  %M: minute filed (0-59), 
    // %S: second filed (0-59), %%: percent sign
    // w: field width
    // perfect programming art (:
    static MyTime parse(const char* szTimeStr, const char* szFormat = "%Y-%m-%d %H:%M:%S");

    MyTime() : m_time(0){}
    MyTime( time_t time ) : m_time(time){}

    MyTime( struct tm time ) {
    m_time = mktime(&time);
    }

    MyTime( int nYear, int nMonth, int nDay, int nHour = 0, int nMin = 0, int nSec = 0,
    int nDST = -1 ) 
    {
    struct tm atm;
    atm.tm_sec = nSec;
    atm.tm_min = nMin;
    atm.tm_hour = nHour;        
    atm.tm_mday = nDay;        
    atm.tm_mon = nMonth - 1;        // tm_mon is 0 based        
    atm.tm_year = nYear - 1900;     // tm_year is 1900 based
    atm.tm_isdst = nDST;
    m_time = mktime(&atm);        
    }

    MyTime(const MyTime& time) {
    m_time = time.m_time;
    }

    MyTime& operator=( time_t time ) {        
    m_time = time;        
    return( *this );
    }

    MyTime& operator+=( MyTimeSpan span ) {
    m_time += span.getTimeSpan();        
    return( *this );
    }

    MyTime& operator-=( MyTimeSpan span ) {
    m_time -= span.getTimeSpan();
    return (*this);
    }

    MyTimeSpan operator-( MyTime time ) const {
    return( MyTimeSpan( m_time-time.m_time ) );
    }

    MyTime operator-( MyTimeSpan span ) const {
    return( MyTime( m_time-span.getTimeSpan() ) );
    }

    MyTime operator+( MyTimeSpan span ) const {
    return( MyTime( m_time+span.getTimeSpan() ) );
    }

    bool operator==( MyTime time ) const {
    return( m_time == time.m_time );
    }

    bool operator!=( MyTime time ) const {
    return( m_time != time.m_time );
    }

    bool operator<( MyTime time ) const {
    return( m_time < time.m_time );
    }

    bool operator>( MyTime time ) const {
    return( m_time > time.m_time );
    }

    bool operator<=( MyTime time ) const {
    return( m_time <= time.m_time );
    }

    bool operator>=( MyTime time ) const {
    return( m_time >= time.m_time );
    }

    struct tm* getGmtTm( struct tm* ptm = NULL ) const {
    struct tm * ptmTemp;
    ptmTemp = gmtime(&m_time);

    if (ptmTemp == NULL)
        return NULL;

    if (ptm != NULL)
    {
        *ptm = *ptmTemp;
        return ptm;
    }
    else
    {
        return ptmTemp;
    }
    }

    struct tm* getLocalTm( struct tm* ptm = NULL ) const {
    struct tm * ptmTemp;
    ptmTemp = localtime(&m_time);

    if (ptmTemp == NULL)
        return NULL;

    if (ptm != NULL) {
        *ptm = *ptmTemp;
        return ptm;
    }
    else
    {
        return ptmTemp;
    }
    }

    time_t getTime() const {
    return m_time;
    }

    int getYear() const {
    struct tm * ptm;
    ptm = getLocalTm();
    return ptm ? (ptm->tm_year + 1900) : 0 ;         
    }

    int getMonth() const {
    struct tm * ptm;
    ptm = getLocalTm();
    return ptm ? (ptm->tm_mon + 1) : 0 ; 
    }

    int getDay() const {
    struct tm * ptm;
    ptm = getLocalTm();
    return ptm ? ptm->tm_mday : 0 ; 
    }

    int getHour() const {
    struct tm * ptm;
    ptm = getLocalTm();
    return ptm ? ptm->tm_hour : -1 ; 
    }

    int getMinute() const {
    struct tm * ptm;
    ptm = getLocalTm();
    return ptm ? ptm->tm_min : -1 ; 
    }

    int getSecond() const {
    struct tm * ptm;
    ptm = getLocalTm();
    return ptm ? ptm->tm_sec : -1 ;
    }

    int getDayOfWeek() const {
    struct tm * ptm;
    ptm = getLocalTm();
    return ptm ? ptm->tm_wday + 1 : 0 ;
    }

    // formatting using "C" strftime
    std::string tostr( const char* pszFormat="%Y-%m-%d %H:%M:%S") const;
    std::string togmtstr( const char* pszFormat="%Y-%m-%d %H:%M:%S") const;    

private:
    time_t m_time;
};

///////////////////////////////////////////////////////////////////////////////


#endif // __MYTIME_H__
