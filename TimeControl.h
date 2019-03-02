#ifndef _TIMECONTROL_H_
#define _TIMECONTROL_H_

    // константы, контролирующие корректность ввода пользователя
#define MIN_DAY            1
#define MAX_DAY            31
#define MIN_HOUR           0
#define MAX_HOUR           23
#define MIN_MINUTE         0
#define MAX_MINUTE         59
#define FILE_NAME          "Data.wt"
#define MAX_CONVERT_LENGTH 4

    // длины полей для размещения информации в файле
#define NAME_LENGTH        16
#define YEAR_LENGTH        4
#define MONTH_LENGTH       2
#define WEEK_LENGTH        1
#define WORK_TIME_LENGTH   4
#define DINNER_TIME_LENGTH 3
#define COUNT_DAYS         31
#define DAY_LENGTH         8

    // флаги файла
#define BEGIN_FILE_WORD "beg"
#define END_FILE_WORD   "end"
#define FILE_LENGTH     454

    // позиции параметров в файле
#define POS_NAME        6
#define POS_YEAR        25
#define POS_MONTH       32
#define POS_WEEK        37
#define POS_WORK_TIME   41
#define POS_DINNER_TIME 48

    // позиции для блокировки дней, которых нет в месяце
#define SYMBOL_BLOCK 'X'
#define POS_BLOCK_29 420
#define POS_BLOCK_30 433
#define POS_BLOCK_31 446

    // месяцы
enum MONTHS {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER,
    ALL_MONTHS = 12
};

    // дни недели
enum WEEK_DAYS {
    MONDAY = 1,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY,
    ALL_WEEK_DAYS = 7
};

#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>

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
        // по умолчанию - 1 элемент
        static void ConvertIntToChar (const int&, char*, const int& r_LENGTH = 1);

        // преобразование char в int
        // длина массива по умолчанию = 1
        static int ConvertCharToInt (const char*, const int& r_LENGTH = 1);

        // создать файл по шаблону
        static bool CreateTemplate();

        // проверка на целостность файла
        static bool IsCrushed(std::fstream&);

        // заполнение шаблона
        static void FillTemplate();

        // установка количества дней в файле в зависимости от месяца
        static void SetDays();

    public:
        // конструктор
        TimeControl();

        // добавить рабочий день
        void Add(const wt::Add_status& flag = ADD);

        // очистить время дня
        //static void Delete();

        // сбросить всё рабочее время
        static void Reset();

        // показать подробно рабочее время
        static void Show();

        // вывод времени
        static void Calculate();

        // проверка файла
        static bool Check();

        // приветствие пользователя
        static void WelcomeUser();

        // установить следующий месяц
        static void SetNextMonth();
    };
};

#endif
