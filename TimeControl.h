#ifndef _TIMECONTROL_H_
#define _TIMECONTROL_H_

#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_HOUR 0
#define MAX_HOUR 23
#define MIN_MINUTE 0
#define MAX_MINUTE 59
#define WORK_MINUTES 525 // Рабочее время 8ч 45м или 525м

#include <string>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;

namespace wt
{
    struct dayTime
    {
        int day;
    	int startHour;
    	int startMinute;
    	int finishHour;
    	int finishMinute;
    };

    class TimeControl
    {
    private:
        dayTime m_buffer;
        static void ConvertIntToChar (const int&, char*);
        static int ConvertCharToInt (const char*);

    public:
        TimeControl();
        void Add(bool flag = false); // флаг false (по умолчанию) - режим вставки нового значения, true - режим коррекции
        //static void Delete();
        static void Reset();
        static void Show();
        static void Calculate();
    };
};

#endif
