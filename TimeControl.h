#ifndef _TIMECONTROL_H_
#define _TIMECONTROL_H_

    // константы, контролирующие корректность ввода пользователя
#define MIN_DAY 1
#define MAX_DAY 31
#define MIN_HOUR 0
#define MAX_HOUR 23
#define MIN_MINUTE 0
#define MAX_MINUTE 59
#define WORK_MINUTES 525 // Рабочее время 8ч 45м или 525м                        //////////////////////////////////////////////////////

#include <string>
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;

namespace wt
{
    // флаги для метода Add: добавление и коррекция
    enum Add_status {ADD, CORRECTION};

    // класс, управляющий подсчетом времени
    class TimeControl
    {
    private:
        // структура буфера
        struct dayTime
        {
            int day:8;
            int startHour:4;
            int finishHour:4;
            int startMinute:8;
            int finishMinute:8;
        } m_buffer;

        // преобразование int в char
        static void ConvertIntToChar (const int&, char*);

        // преобразование char в int
        static int& ConvertCharToInt (const char*);

    public:
        // конструктор
        TimeControl();

        // добавить рабочий день
        void Add(const wt::Add_status& flag = ADD);


        //static void Delete();

        // сбросить всё рабочее время
        static void Reset();

        // показать подробно рабочее время
        static void Show();

        // вывод времени
        static void Calculate();
    };
};

#endif
