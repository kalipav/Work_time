#include "TimeControl.h"
#include <fstream>

// конструктор
wt::TimeControl::TimeControl()
{
    m_buffer.day = 0;
    m_buffer.startHour = 0;
    m_buffer.startMinute = 0;
    m_buffer.finishHour = 0;
    m_buffer.finishMinute = 0;

    //cout << "Constructor.\n";
}

// преобразование char в int
// [in]  const char* - массив
// [in]  const int&  - длина массива, по умолчанию = 1
// [out] int         - преобразованное значение
int wt::TimeControl::ConvertCharToInt(const char* p_MAS_CHAR, const int& r_LENGTH)
{
    // максимальная длина преобразуемого массива
	const int MAX_CONVERT_LENGTH = 4;
    
    // копия массива
    char p_char_copy[MAX_CONVERT_LENGTH];

    // копируем массив
    for (int i = 0; i < r_LENGTH; ++i)
    {
        p_char_copy[i] = p_MAS_CHAR[i];
    };

    // проверка на длину массива
    if (r_LENGTH > MAX_CONVERT_LENGTH || r_LENGTH <= 0)
    {
        std::cout << "Error! Convertation failed. Wrong length.\n";
        abort();
    };

    // проверка на наличие исключительно цифр в массиве
    for (int i = 0; i < r_LENGTH; ++i)
    {
        // символ '0' - это 48 в десятич. системе, '1' = 49, ..., '9' = 57
        if ((int)(p_char_copy[i]) < 48 || (int)(p_char_copy[i]) > 57)
        {
            std::cout << "Error! Try to convert letter.\n";
            abort();
        };
    };

    // начальное значение числа
    int number = 0;

    // буфер для символа при перевороте
    char buf;

    // переворачиваем массив для корректности разрядов
    if (r_LENGTH == 2)
    {
        // меняем местами элементы массива
        buf = p_char_copy[0];
        p_char_copy[0] = p_char_copy[1];
        p_char_copy[1] = buf;
    }
    else if (r_LENGTH == 3)
    {
        // меняем местами 0-ой и 2-ой элементы
        buf = p_char_copy[0];
        p_char_copy[0] = p_char_copy[2];
        p_char_copy[2] = buf;
    }
    else if (r_LENGTH == 4)
    {
        // меняем местами 0-ой и 3-ий, 1-ый и 2-ой элементы
        buf = p_char_copy[0];
        p_char_copy[0] = p_char_copy[3];
        p_char_copy[3] = buf;
        buf = p_char_copy[1];
        p_char_copy[1] = p_char_copy[2];
        p_char_copy[2] = buf;
    };

    // переводим число
	for (int i = 0; i < 10; ++i)
	{
        // символ '0' - это 48 в десятич. системе, '1' = 49, ..., '9' = 57
		if (r_LENGTH >= 1)
		{
			if (p_char_copy[0] == 48 + i)
			{
				number += i;
			}
		};

		if (r_LENGTH >= 2)
		{
			if (p_char_copy[1] == 48 + i)
			{
				number += i * 10;
			}
		};

		if (r_LENGTH >= 3)
		{
			if (p_char_copy[2] == 48 + i)
			{
				number += i * 100;
			}
		};

		if (r_LENGTH == MAX_CONVERT_LENGTH)
		{
			if (p_char_copy[3] == 48 + i)
			{
				number += i * 1000;
			}
		};
	};

	return number;
}

// преобразование int в char
// [in]     const int& - возвращаемое число в int
// [in/out] char*      - массив char для цифр
// [in]     const int& - длина входного массива, по умолчанию - 1 элемент
void wt::TimeControl::ConvertIntToChar (const int& r_NUMBER, char* p_massChar, const int& r_LENGTH)
{
    // разбор по разрядам числа
    int thousands = r_NUMBER / 1000;
    int hundreds  = (r_NUMBER - thousands * 1000) / 100;
    int decades   = (r_NUMBER - thousands * 1000 - hundreds * 100) / 10;
    int ones      = r_NUMBER % 10;

    // подбор цифр
    for (int i = 0; i < 10; ++i)
    {
        // символ '0' - это 48 в десятич. системе, '1' = 49, ..., '9' = 57
        // если длина массива - ... символа
        if (r_LENGTH == 4)
        {
            if (thousands == i) p_massChar[0] = i+48;
            if (hundreds  == i) p_massChar[1] = i+48;
            if (decades   == i) p_massChar[2] = i+48;
            if (ones      == i) p_massChar[3] = i+48;
        }
        else if (r_LENGTH == 3)
        {
            if (hundreds == i) p_massChar[0] = i+48;
            if (decades  == i) p_massChar[1] = i+48;
            if (ones     == i) p_massChar[2] = i+48;
        }
        else if (r_LENGTH == 2)
        {
            if (decades == i) p_massChar[0] = i+48;
            if (ones    == i) p_massChar[1] = i+48;
        }
        else if (r_LENGTH == 1)
        {
            if (ones == i)    p_massChar[0] = i+48;
        };
    };
}

// добавить/откорректировать/удалить рабочий день
// [in] const wt::Add_status& - флаг добавления/корректировки/удаления
void wt::TimeControl::AddCorDel(const Status& flag)
{
    // индикация входа в метод
    if (flag == ADDITION)
    {
        std::cout << "Date addition.\n";
    }
    else if (flag == CORRECTION)
    {
        std::cout << "Date correction.\n";
    }
    else if (flag == DELETION)
    {
        std::cout << "Date deletion.\n";
    };

    // длина массива для ввода символов часов и минут
	const int symBufSize = 2;

    // массив для ввода символов часов и минут
    char symBuf[symBufSize];

	// ввод даты
	do
	{
		std::cout << "Enter date: ";
		symBuf[0] = _getch();
		std::cout << symBuf[0];
		symBuf[1] = _getch();
		std::cout << symBuf[1] << '\n';
        m_buffer.day = ConvertCharToInt(symBuf, symBufSize);
    } while (m_buffer.day < MIN_DAY ||
			 m_buffer.day > MAX_DAY);

        // проверяем доступность даты по информации из файла
    // создаем объект для работы с файлом
    std::fstream finout (FILE_NAME, std::ios::in | std::ios::out);

    // позиция даты, указывающая на поле с часами и минутами
    int pos = GetPosOfDay(m_buffer.day);
    
    // если произошла ошибка в поиске позиции даты
    if (pos == ERROR_POS)
    {
        std::cout << "Date hasn't found, error position.\n";
        finout.close();
        return;
    }

    // иначе устанавливаем указатель на позицию текущей даты
    else
    {
        finout.seekg(pos, std::ios::beg);
    };

    // символ для проверки даты, считываем первый байт даты
    char control = finout.get();

        // проверяем можно ли добавлять/корректировать/удалять данную дату
    // если дата заблокирована - выходим
    if (control == SYMBOL_BLOCK)
    {
        std::cout << "Warning! This date can't be in this month.\n";
        finout.close();
        return;
    };

    // если дата пуста - нельзя корректировать и удалять
    if (control == SYMBOL_EMPTY && (flag == CORRECTION || flag == DELETION))
    {
        std::cout << "Incorrect selection! Date is empty.\n";
        finout.close();
        return;
    };

    // если дата занята, то нельзя производить добавление
    if (control != SYMBOL_EMPTY && flag == ADDITION)
    {
        std::cout << "Incorrect selection! Date is not empty.\n";
        finout.close();
        return;
    };

	// указатель для записи поля даты, смещенный на -1, т.к. считали первый байт даты
	int filePointer = finout.tellg();
    --filePointer;

    // устанавливаем указатель на запись часов и минут
    finout.seekp(filePointer, std::ios::beg);

        // вводим часы и минуты
	// если добавляем или корректируем дату, то вводим начальное и конечное время
    if (flag == ADDITION || flag == CORRECTION)
    {
		// осуществляем ввод часов начала рабочего времени
		do
		{
			std::cout << "Enter start hours: ";
			symBuf[0] = _getch();
			std::cout << symBuf[0];
			symBuf[1] = _getch();
			std::cout << symBuf[1] << '\n';
			m_buffer.startHour = ConvertCharToInt(symBuf, symBufSize);
		} while (m_buffer.startHour < MIN_HOUR ||
				 m_buffer.startHour > MAX_HOUR);
	
		// осуществляем ввод минут начала рабочего времени
		do
		{
			std::cout << "Enter start minutes: ";
			symBuf[0] = _getch();
			std::cout << symBuf[0];
			symBuf[1] = _getch();
			std::cout << symBuf[1] << '\n';
			m_buffer.startMinute = ConvertCharToInt(symBuf, symBufSize);
		} while (m_buffer.startMinute < MIN_MINUTE ||
				 m_buffer.startMinute > MAX_MINUTE);

		// осуществляем ввод часов конца рабочего времени
		do
		{
			std::cout << "Enter finish hours: ";
			symBuf[0] = _getch();
			std::cout << symBuf[0];
			symBuf[1] = _getch();
			std::cout << symBuf[1] << '\n';
			m_buffer.finishHour = ConvertCharToInt(symBuf, symBufSize);
		} while (m_buffer.finishHour < MIN_HOUR ||
				 m_buffer.finishHour > MAX_HOUR);

		// осуществляем ввод минут конца рабочего времени
		do
		{
			std::cout << "Enter finish minutes: ";
			symBuf[0] = _getch();
			std::cout << symBuf[0];
			symBuf[1] = _getch();
			std::cout << symBuf[1] << '\n';
			m_buffer.finishMinute = ConvertCharToInt(symBuf, symBufSize);
		} while (m_buffer.finishMinute < MIN_MINUTE ||
				 m_buffer.finishMinute > MAX_MINUTE);

            // записываем дату
        // буфер для часов и минут, состоит из двух символов
        const int BUF_MIN_HOUR_LENGTH = 2;
        char bufMinHour[BUF_MIN_HOUR_LENGTH];

        // преобразуем час начала рабочего дня
        ConvertIntToChar(m_buffer.startHour, bufMinHour, BUF_MIN_HOUR_LENGTH);

        // записываем в файл
        for (int i = 0; i < BUF_MIN_HOUR_LENGTH; ++i)
        {
            finout.put(bufMinHour[i]);
        };

        // преобразуем минуты начала рабочего дня
        ConvertIntToChar(m_buffer.startMinute, bufMinHour, BUF_MIN_HOUR_LENGTH);

        // записываем в файл
        for (int i = 0; i < BUF_MIN_HOUR_LENGTH; ++i)
        {
            finout.put(bufMinHour[i]);
        };

        // преобразуем час конца рабочего дня
        ConvertIntToChar(m_buffer.finishHour, bufMinHour, BUF_MIN_HOUR_LENGTH);

        // записываем в файл
        for (int i = 0; i < BUF_MIN_HOUR_LENGTH; ++i)
        {
            finout.put(bufMinHour[i]);
        };

        // преобразуем минуты конца рабочего дня
        ConvertIntToChar(m_buffer.finishMinute, bufMinHour, BUF_MIN_HOUR_LENGTH);

        // записываем в файл
        for (int i = 0; i < BUF_MIN_HOUR_LENGTH; ++i)
        {
            finout.put(bufMinHour[i]);
        };
    }

    // если флаг - удаление, записываем пустые символы
    else if (flag == DELETION)
    {
        // символ ввода
        char symbol;

        // запрашиваем подтверждение на удаление
        std::cout << "If date is correct - enter 'y': ";
        symbol = _getch();
        std::cout << symbol << '\n';
        
        // если все верно - очищаем дату
        if (symbol == 'y')
        {
            // записываем пустые символы
            for (int i = 0; i < DAY_LENGTH; ++i)
            {
                finout.put(SYMBOL_EMPTY);
            };
        }

        // иначе выходим из метода
        else
        {
            std::cout << "Deletion canceled.\n";
            finout.close();
            return;
        };
    };

    finout.close();

    // принты успешности завершения метода
    if (flag == ADDITION)
    {
        std::cout << "Addition success.\n";
    }
    else if (flag == CORRECTION)
    {
        std::cout << "Correction success.\n";
    }
    else if (flag == DELETION)
    {
        std::cout << "Day " << m_buffer.day << " cleared.\n";
		return;
    };

    // вывод дня недели даты
    std::cout << GetWeekDay(m_buffer.day) << " ";

    // вывод информации по дате
    printf("%02d  %02d:%02d - %02d:%02d\n",
           m_buffer.day,
           m_buffer.startHour,
           m_buffer.startMinute,
           m_buffer.finishHour,
           m_buffer.finishMinute);
}

// проверить целостность файла, поля
// [out] bool - true - успешное завершение метода, false - выход из программы
bool wt::TimeControl::Check()
{
    // объект для проверки файла
    std::fstream finout(FILE_NAME, std::ios::in | std::ios::out);

    // проверка открылся ли файл
    if (!finout)
    {
        std::cout << "File is not open!\n";

        // буферная переменная
        char buf;

        // предложить пользователю создать новый файл
        std::cout << "Do you want to create a new file? (y - \"yes\"): ";

        // ввод
        buf = _getch();
        std::cout << buf << '\n';

        // обработка выбора пользователя
        if (buf == 'y')
        {
            // создать файл по шаблону
            if (!CreateTemplate())
            {
                std::cout << "Check ended with error!\n";
                return false;
            };

            // повторное открытие файла
            finout.open(FILE_NAME, std::ios::in | std::ios::out);

            // проверка открылся ли файл во второй раз
            if (!finout)
            {
                std::cout << "File is not open!\n";
                return false;
            };
        }
        else
        {
            std::cout << "Check ended with error!\n";
            return false;
        }
    };

    // проверка на целостность файла
    if (!IsCrushed(finout))
    {
        std::cout << "Check ended with error!\n";
        return false;
    };

    // закрываем файл
    finout.close();

    // успешное завершение метода
    return true;
}

// проверка на целостность файла
// [in/out] std::fstream& - объект для работы с файлом
// [out] bool - true - проверка прошла успешно, false - файл поврежден
bool wt::TimeControl::IsCrushed(std::fstream& r_finout)
{
    // устанавливаем указатель на начало файла
    r_finout.seekg(0, std::ios::beg);

    // строка для обработки файла
    std::string buf;

    // считывание первых трех символов файла
    for (int i = 0; i < 3; ++i)
    {
        buf += r_finout.get();
    };

    // проверка считанных символов
    if (buf != BEGIN_FILE_WORD)
    {
        std::cout << "File crushed!\n";
        return false;
    };

    // обнуляем буфер
    buf = "";

    // переносим указатель на позицию для считывания последних трех символов
    r_finout.seekg(FILE_LENGTH, std::ios::beg);

    // считываем три последних символа файла
    for (int i = 0; i < 3; ++i)
    {
        buf += r_finout.get();
    };

    // проверка считанных символов
    if (buf != END_FILE_WORD)
    {
        std::cout << "File crushed!\n";
        return false;
    };

    // файл цел
    return true;
}

// создать файл по шаблону
// [out] bool - удачное/неудачное завершение метода
bool wt::TimeControl::CreateTemplate()
{
    // объект для создания файла
    std::ofstream fout(FILE_NAME);

    // проверка открылся ли файл
    if (!fout)
    {
        std::cout << "File is not open!\n";
        return false;
    };

    // создаем строку для шаблона
    std::string template_str = "";

    // добавляем индикатор начала файла
    template_str += BEGIN_FILE_WORD;

    // добавляем место под имя
    template_str += "nam";
    for (int i = 0; i < NAME_LENGTH; ++i)
    {
        template_str += " ";
    };

    // добавляем место под год
    template_str += "yea";
    for (int i = 0; i < YEAR_LENGTH; ++i)
    {
        template_str += " ";
    };

    // добавляем место под месяц
    template_str += "mnt";
    for (int i = 0; i < MONTH_LENGTH; ++i)
    {
        template_str += " ";
    };

    // добавляем место под день недели для первого числа месяца
    template_str += "fst";
    for (int i = 0; i < WEEK_LENGTH; ++i)
    {
        template_str += " ";
    };

    // добавляем место под количество рабочих часов
    template_str += "wot";
    for (int i = 0; i < WORK_TIME_LENGTH; ++i)
    {
        template_str += " ";
    };

    // добавляем место под обеденное время
    template_str += "din";
    for (int i = 0; i < DINNER_TIME_LENGTH; ++i)
    {
        template_str += " ";
    };

    // добавляем место под даты
    for (int i = 1; i <= COUNT_DAYS; ++i)
    {
        template_str += "day";

        // массив для чисел дней (2 элемента)
        const int MAS_DAY_SIZE = 2;
        char day[MAS_DAY_SIZE];

        // конвертация числа в символьное значение
        ConvertIntToChar(i, day, MAS_DAY_SIZE);

        // копируем значение
        template_str += day[0];
        template_str += day[1];

        // заносим пробелы под день недели, время начала и время конца рабочего дня
        for (int i = 0; i < DAY_LENGTH; ++i)
        {
            template_str += " ";
        };
    };

    // добавляем место под индикатор окончания файла
    template_str += END_FILE_WORD;

    // записываем в файл шаблон
    fout << template_str;

    // закрываем файл
    fout.close();

    // заполнение шаблона
    FillTemplate();

    // удачное завершение метода
    std::cout << "File created.\n";

    return true;
}

// заполнение шаблона
void wt::TimeControl::FillTemplate()
{
    // объект для записи
    std::fstream finout(FILE_NAME, std::ios::in | std::ios::out);

    // строка-буфер
    std::string buf;

    // символ подтверждения имени
    char symbol;

    // запрашиваем имя у пользователя пока не будет введено подтверждение имени или пока имя длиннее поля под имя
    do
    {
        std::cout << "Enter your name (" << NAME_LENGTH << " symbols max): ";
        std::cin >> buf;

        std::cout << "If correct - enter 'y': ";
        symbol = _getch();
        std::cout << symbol << '\n';
    } while (symbol != 'y' || buf.size() > NAME_LENGTH);

    // записываем имя в файл
    // перемещаем указатель на позицию с именем для ввода имени
    finout.seekp(POS_NAME, std::ios::beg);

    // записываем имя
    finout << buf;

    // вводим год
    do
    {
        std::cout << "Enter year: ";
        std::cin >> buf;

        std::cout << "If correct - enter 'y': ";
        symbol = _getch();
        std::cout << symbol << '\n';
    } while (symbol != 'y' || buf.size() != YEAR_LENGTH);

    // записываем год в файл
    // перемещаем указатель на позицию с годом
    finout.seekp(POS_YEAR, std::ios::beg);

    // записываем год
    finout << buf;

    // вводим месяц
    do
    {
        std::cout << "Enter month: ";
        std::cin >> buf;

        std::cout << "If correct - enter 'y': ";
        symbol = _getch();
        std::cout << symbol << '\n';
    } while (symbol != 'y' || buf.size() > MONTH_LENGTH);

    // записываем месяц в файл
    // перемещаем указатель на позицию с месяцем
    finout.seekp(POS_MONTH, std::ios::beg);

    // если в месяце меньше цифр, чем длина поля, заполнить нулями пустые поля
    if (buf.size() < MONTH_LENGTH)
    {
        finout << '0';
    };

    // записываем месяц
    finout << buf;

    // вводим день недели первого числа месяца
    do
    {
        std::cout << "Enter weekday of 1st day of month\n";
        std::cout << "(1 - MON, 2 - TUE, 3 - WEN, 4 - THU, 5 - FRI, 6 - SAT, 7 - SUN): ";
        std::cin >> buf;

        std::cout << "If correct - enter 'y': ";
        symbol = _getch();
        std::cout << symbol << '\n';
    } while (symbol != 'y' || buf.size() > WEEK_LENGTH);

    // записываем день недели в файл
    // перемещаем указатель на позицию с днем недели
    finout.seekp(POS_WEEK, std::ios::beg);

    // записываем день недели
    finout << buf;

    // вводим количество рабочих часов в минутах
    do
    {
        std::cout << "Enter work time in minutes: ";
        std::cin >> buf;

        std::cout << "If correct - enter 'y': ";
        symbol = _getch();
        std::cout << symbol << '\n';
    } while (symbol != 'y' || buf.size() > WORK_TIME_LENGTH);

    // записываем количество рабочих часов в файл
    // перемещаем указатель на позицию с количеством рабочих часов
    finout.seekp(POS_WORK_TIME, std::ios::beg);

    // пустые поля заполняем нулями
    if (buf.size() < WORK_TIME_LENGTH)
    {
        for (int i = 0; i < WORK_TIME_LENGTH - (int)buf.size(); ++i)
        {
            finout << '0';
        }
    };

    // записываем количество рабочих часов
    finout << buf;

    // вводим обеденное время в минутах
    do
    {
        std::cout << "Enter dinner time in minutes: ";
        std::cin >> buf;

        std::cout << "If correct - enter 'y': ";
        symbol = _getch();
        std::cout << symbol << '\n';
    } while (symbol != 'y' || buf.size() > DINNER_TIME_LENGTH);

    // записываем обеденное время в файл
    // перемещаем указатель на позицию с обеденным временем
    finout.seekp(POS_DINNER_TIME, std::ios::beg);

    // пустые поля заполняем нулями
    if (buf.size() < DINNER_TIME_LENGTH)
    {
        for (int i = 0; i < DINNER_TIME_LENGTH - (int)buf.size(); ++i)
        {
            finout << '0';
        }
    };

    // записываем обеденное время
    finout << buf;

    finout.close();

    // устанавливаем количество дней в файле
    SetDays();
}

// приветствие пользователя
void wt::TimeControl::WelcomeUser()
{
    // объект для чтения
    std::ifstream fin(FILE_NAME);

    // перемещаем указатель на позицию ввода имени для чтения
    fin.seekg(POS_NAME, std::ios::beg);

    // буфер для имени
    char name[NAME_LENGTH];

    // чтение имени
    fin.read(name, NAME_LENGTH);

    // вывод приветствия на экран
    std::cout << "\nHello, ";
    for (int i = 0; i < NAME_LENGTH; ++i)
    {
        // пробелы не выводим
        if (name[i] != SYMBOL_EMPTY)
        {
            std::cout << name[i];
        };
    };
    std::cout << "!\n";

    fin.close();
}

// установка количества дней в файле в зависимости от месяца
void wt::TimeControl::SetDays()
{
    // объект ввода/вывода
    std::fstream finout (FILE_NAME, std::ios::in | std::ios::out);

    // длина буфера для считывания месяца и года (выбираем больший размер)
    const int LENGTH = YEAR_LENGTH > MONTH_LENGTH ? YEAR_LENGTH : MONTH_LENGTH;

    // буфер
    char buf[LENGTH];

    // устанавливаем позицию для считывания года из файла
    finout.seekg(POS_YEAR, std::ios::beg);

    // считываем из файла год
    for (int i = 0; i < YEAR_LENGTH; ++i)
    {
        buf[i] = finout.get();
    };

    // преобразуем год в int
    int year = ConvertCharToInt(buf, YEAR_LENGTH);

    // устанавливаем позицию для считывания месяца из файла
    finout.seekg(POS_MONTH, std::ios::beg);

    // считываем из файла месяц
    for (int i = 0; i < MONTH_LENGTH; ++i)
    {
        buf[i] = finout.get();
    };

    // преобразуем месяц в int
    int month = ConvertCharToInt(buf, MONTH_LENGTH);

    // количество дней в месяце
    int days;

    // определяем количество дней в месяце
    if (month == JANUARY ||
        month == MARCH   ||
        month == MAY     ||
        month == JULY    ||
        month == AUGUST  ||
        month == OCTOBER ||
        month == DECEMBER)
    {
        days = 31;
    }
    else if (month == APRIL     ||
             month == JUNE      ||
             month == SEPTEMBER ||
             month == NOVEMBER)
    {
        days = 30;
    }

    // февраль високосного года
    else if (month == FEBRUARY && year % 4 == 0)
    {
        days = 29;
    }

    // февраль невисокосного года
    else if (month == FEBRUARY && year % 4 != 0)
    {
        days = 28;
    };

        // блокируем в файле дни, которых нет в месяце
    // если дней меньше 31 - блокируем 31-ое число
    if (days < 31)
    {
        finout.seekg(POS_BLOCK_31, std::ios::beg);
        finout << SYMBOL_BLOCK;
    };

    // если дней меньше 30 - блокируем 30-ое число
    if (days < 30)
    {
        finout.seekg(POS_BLOCK_30, std::ios::beg);
        finout << SYMBOL_BLOCK;
    };

    // если дней меньше 29 - блокируем 29-ое число
    if (days < 29)
    {
        finout.seekg(POS_BLOCK_29, std::ios::beg);
        finout << SYMBOL_BLOCK;
    };
}

// установить следующий месяц
void wt::TimeControl::SetNextMonth()
{
    // индикация начала метода
    std::cout << "Start to set next month.\n";

    // объект для чтения/записи
    std::fstream finout (FILE_NAME, std::ios::in | std::ios::out);

    // проходим по файлу, очищаем дни
    for (int i = MIN_DAY; i <= MAX_DAY; ++i)
    {
        // позиция даты
        int pos;

        // вернуть позицию указанного дня в файле
        pos = GetPosOfDay(i);

        // если произошла ошибка в поиске позиции даты
        if (pos == ERROR_POS)
        {
            std::cout << "Date hasn't found, error position.\n";
            return;
        }

        // иначе очистить часы и минуты даты
        else
        {
            // устанавливаем указатель на позицию текущей даты
            finout.seekg(pos, std::ios::beg);

            // заполняем пробелами поле
            for (int i = 0; i < DAY_LENGTH; ++i)
            {
                finout.put(SYMBOL_EMPTY);
            };
        };
    };

        // считываем год из файла
    // устанавливаем указатель для чтения на позицию с годом
    finout.seekg(POS_YEAR, std::ios::beg);

    // создаем буфер для года
    char bufYear[YEAR_LENGTH];

    // считываем год из файла
    for (int i = 0; i < YEAR_LENGTH; ++i)
    {
        bufYear[i] = finout.get();
    };

    // преобразуем год в int
    int year = ConvertCharToInt(bufYear, YEAR_LENGTH);

        // считываем месяц из файла
    // устанавливаем указатель для чтения на позицию с месяцем
    finout.seekg(POS_MONTH, std::ios::beg);

    // создаем буфер для месяца
    char bufMonth[MONTH_LENGTH];

    // считываем месяц из файла
    for (int i = 0; i < MONTH_LENGTH; ++i)
    {
        bufMonth[i] = finout.get();
    };

    // преобразуем месяц в int
    int month = ConvertCharToInt(bufMonth, MONTH_LENGTH);

        // считываем день недели первого числа месяца
    // устанавливаем указатель на позицию с днем недели
    finout.seekg(POS_WEEK, std::ios::beg);

    // создаем буфер для дня недели
    char bufWeekDay;

    // считываем день недели из файла
    bufWeekDay = finout.get();

    // преобразуем день недели в int
    int weekDay = ConvertCharToInt(&bufWeekDay);

        // устанавливаем день недели для следующего месяца
    // сдвиг дня недели, возможные варианты - от +0 (28 дней) до +3 (31 день)
    int difference;

    // определяем сдвиг
    // если февраль невисокосного года - сдвига нет
    if (month == FEBRUARY && year % 4 != 0)
    {
        difference = 0;
    }

    // если февраль високосного года - сдвигаем на +1
    else if (month == FEBRUARY && year % 4 == 0)
    {
        difference = 1;
    }

    // если месяц - апрель, июнь, сентябрь или ноябрь, то сдвигаем на +2
    else if (month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER)
    {
        difference = 2;
    }

    // остальные месяцы - на +3
    else
    {
        difference = 3;
    };

    // новый день недели
    weekDay += difference;

    // если превысило максимальное значение (7 дней в неделе), вычесть 7 дней
    if (weekDay > ALL_WEEK_DAYS)
    {
        weekDay -= ALL_WEEK_DAYS;
    };

    // преобразуем день недели в char
    ConvertIntToChar(weekDay, &bufWeekDay);

    // устанавливаем указатель на позицию с днем недели
    finout.seekp(POS_WEEK, std::ios::beg);

    // записываем день недели в файл
    finout.put(bufWeekDay);

        // устанавливаем следующий год, если текущий месяц - декабрь
    if (month == DECEMBER)
    {
        // устанавливаем следующий год
        ++year;

        // преобразуем год в char
        ConvertIntToChar(year, bufYear, YEAR_LENGTH);

        // устанавливаем указатель для записи на позицию с годом
        finout.seekp(POS_YEAR, std::ios::beg);

        // записываем год в файл
        for (int i = 0; i < YEAR_LENGTH; ++i)
        {
            finout.put(bufYear[i]);
        };
    };

        // устанавливаем следующий месяц
    // увеличиваем месяц на +1
    if (month < DECEMBER)
    {
        ++month;
    }
    else
    {
        month = JANUARY;
    };

    // преобразуем месяц в char
    ConvertIntToChar(month, bufMonth, MONTH_LENGTH);

    // устанавливаем указатель на позицию с месяцем
    finout.seekp(POS_MONTH, std::ios::beg);

    // записываем месяц в файл
    for (int i = 0; i < MONTH_LENGTH; ++i)
    {
        finout.put(bufMonth[i]);
    };

    finout.close();

    // устанавливаем количество дней в файле в зависимости от вновь установленного месяца
    SetDays();
    
    std::cout << "Next month set.\n";
}

// вернуть принт дня недели даты
// [in]  const int&  - дата
// [out] std::string - строка с днем недели (символьная)
std::string wt::TimeControl::GetWeekDay(const int& r_DATE)
{
    // создаем объект для работы с файлом
    std::fstream finout (FILE_NAME, std::ios::in | std::ios::out);

    // буфер для дня недели
    char weekDayBuf;

    // устанавливаем указатель на день недели первого числа месяца
    finout.seekg(POS_WEEK, std::ios::beg);

	// считываем день недели
	weekDayBuf = finout.get();

    finout.close();

    // конвертируем
    int weekDay = ConvertCharToInt(&weekDayBuf);
    
	// день недели даты, -1 потому что в файле записан день недели ПЕРВОГО дня месяца
	int weekDayOfDate = weekDay + r_DATE - 1;

	// сокращаем на количество дней недели
	while (weekDayOfDate > ALL_WEEK_DAYS)
	{
		weekDayOfDate -= ALL_WEEK_DAYS;
	};

    // строка с наименованием дня недели
    std::string str;

    switch (weekDayOfDate)
    {
    case 1:
        str = MONDAY_SHOW;
        break;
    case 2:
        str = TUESDAY_SHOW;
        break;
    case 3:
        str = WEDNESDAY_SHOW;
        break;
    case 4:
        str = THURSDAY_SHOW;
        break;
    case 5:
        str = FRIDAY_SHOW;
        break;
    case 6:
        str = SATURDAY_SHOW;
        break;
    case 7:
        str = SUNDAY_SHOW;
        break;
    };

    return str;
}

// вернуть позицию указанного дня в файле
// возвращает -1, если не нашел указанный день
// [in]  const int& - дата
// [out] int        - позиция даты
int wt::TimeControl::GetPosOfDay(const int& r_DATE)
{
	// объект для чтения/записи
    std::fstream finout(FILE_NAME, std::ios::in | std::ios::out);

        // проходим по файлу, очищаем дни
    // длина буфера для поиска дней в файле
    const int BUF_LENGTH = 5;

    // буфер
    char dayBuf[BUF_LENGTH];

    // устанавливаем указатель на начало файла
    finout.seekg(0, std::ios::beg);

    // помещаем первые 5 символов в массив
    for (int i = 0; i < BUF_LENGTH; ++i)
    {
        dayBuf[i] = finout.get();
    };

    // длина массива с датой
    const int DATE_CHAR_LENGTH = 2;

    // дата в виде символьного массива
    char date_char[DATE_CHAR_LENGTH];

    // преобразуем дату
    ConvertIntToChar(r_DATE, date_char, DATE_CHAR_LENGTH);

    // считываем из файла символы пока не встретим "day" и дату "--"
    while (dayBuf[0] != 'd' || dayBuf[1] != 'a' || dayBuf[2] != 'y' || 
           dayBuf[3] != date_char[0] || dayBuf[4] != date_char[1])
    {
        // смещаем элементы на -1
        for (int i = 0; i < BUF_LENGTH - 1; ++i)
        {
            dayBuf[i] = dayBuf[i+1];
        };

        // последнему элементу присваиваем новый символ из файла
        dayBuf[BUF_LENGTH - 1] = finout.get();

        // если 3 последних элемента равны "end" - возвращаем значение "ошибочная позиция"
        if (dayBuf[2] == 'e' && dayBuf[3] == 'n' && dayBuf[4] == 'd')
        {
            finout.close();
            return ERROR_POS;
        };
    };
    
    // вернуть текущую позицию 
    return finout.tellg();
}

// показать время отработки
void wt::TimeControl::TimeToWork()
{	/*
    // создаем объект для вывода информации из файла
    std::ifstream fin ("Data.wt");

    // проверка открылся ли файл
	if (!fin)
	{
		cout << "Error! File not open.\n";
	}
	else
	{
        // перемещаем указатель в начало файла
		fin.seekg (0, std::ios::beg);

        // если первый символ в файле - 'v', то с файлом все в порядке
        if (fin.get() == 'v')
		{
            // массив для чисел, состоящих из 2-х цифр
            char masChar[2] = {0, 0};

            // переменная, содержащая текущее значение
            int bufferMinutes = 0;

            // masChar[0] не используется, т.к. для поиска достаточно одной буферной переменной
            masChar[1] = fin.get();

            // пока не будет достигнут конец файла, выполянять ряд операций
			while (!fin.eof())
			{
                // если найдена точка
                if (masChar[1] == '.')
				{
                    // считать след. символ
                    masChar[1] = fin.get();

                    // если вместо конкретного часа установлен пробел,
                    // значит время не занесено и учитывать этот день не нужно
                    if (masChar[1] == ' ')
					{
						continue;
					}

                    // если установлена дата, то ее необходимо учесть
                    else
					{
                        // создаем объект
						wt::TimeControl bufferDate;

                        // переписываем первую цифру стартового часа из 1-го элемента (это не ' ')
                        masChar[0] = masChar[1];

                        // считываем вторую цифру стартового часа
                        masChar[1] = fin.get();

                        // конвертируем
						bufferDate.m_buffer.startHour = ConvertCharToInt(masChar);

                        // перемещаем указатель на 1 позицию вперед (пропускаем двоеточие и тире)
						fin.seekg(1, std::ios::cur);

                        // считываем первую цифру стартовых минут
                        masChar[0] = fin.get();

                        // считываем вторую цифру стартовых минут
                        masChar[1] = fin.get();

                        // конвертируем
						bufferDate.m_buffer.startMinute = ConvertCharToInt(masChar);

                        // перемещаем указатель на 1 позицию вперед (пропускаем двоеточие и тире)
						fin.seekg(1, std::ios::cur);

                        // считываем первую цифру финишных часов
                        masChar[0] = fin.get();

                        // считываем вторую цифру финишных часов
                        masChar[1] = fin.get();

                        // конвертируем
						bufferDate.m_buffer.finishHour = ConvertCharToInt(masChar);

                        // перемещаем указатель на 1 позицию вперед (пропускаем двоеточие и тире)
						fin.seekg(1, std::ios::cur);

                        // считываем первую цифру финишных минут
                        masChar[0] = fin.get();

                        // считываем вторую цифру финишных минут
                        masChar[1] = fin.get();

                        // конвертируем
						bufferDate.m_buffer.finishMinute = ConvertCharToInt(masChar);

						// добавляет реальное рабочее время за день
                        bufferMinutes += bufferDate.m_buffer.finishHour * 60 +
                                         bufferDate.m_buffer.finishMinute    -
                                        (bufferDate.m_buffer.startHour  * 60 +
                                         bufferDate.m_buffer.startMinute);

                        // вычитаем 8ч 45м (525м)                                     ///////////////////////////////////////////////////
                        bufferMinutes -= 525;
					};
				}
				else
				{
                    // считываем один символ из файла
					masChar[1] = fin.get();
				}

			}; // закрывает while

            // условие для различия времени на отработку и свободного времени
			if (bufferMinutes > 0)
			{
				cout << "----------\n";
				cout << "Free time: " << bufferMinutes/60 << "h " << bufferMinutes%60 << "m.\n";
				cout << "----------\n";
			}
			else
			{
				cout << "-------------\n";
				cout << "Time to work: " << (-1)*bufferMinutes/60 << "h " << (-1)*bufferMinutes%60 << "m.\n";
				cout << "-------------\n";
			};
		}

        // файл не прошел проверку на целостность
		else
        {
			cout << "File crushed.\n";
		}
	};
	fin.close();
*/}

// показать подробную информацию по датам
void wt::TimeControl::Show()
{
	std::cout << "Show time of all days.\n";

	// создаем объект для чтения информации из файла
	std::ifstream fin("Data.wt");

	// пройти по дням недели 1 - 31
	for (int i = MIN_DAY; i <= MAX_DAY; ++i)
	{
		// позиция с информацией по времени даты
		int pos = GetPosOfDay(i);

		// устаналиваем указатель на позицию
		fin.seekg(pos);

		// символ проверки (первый символ поля времени даты)
		char check_symbol = fin.get();

		// возвращаем указатель на исходную позицию
		fin.seekg(pos);

		// проверяем дату на существование
		if (check_symbol == SYMBOL_BLOCK)
		{
			// если дата заблокирована, продолжить цикл
			continue;
		};

		// делать отступы перед понедельниками, если понедельник не первое число
		if (i != MIN_DAY && GetWeekDay(i) == MONDAY_SHOW)
		{
			std::cout << std::endl;
		};

		//отобразить день недели
		std::cout << GetWeekDay(i) << SYMBOL_EMPTY;

		// вернуть позицию на -2, чтобы отобразить дату
		pos -= 2;
		fin.seekg(pos);

		// длина буфера для даты, часов, минут, сам буфер 
		const int BUF_LENGTH = 2;
		char buf[BUF_LENGTH];

		// заполняем буфер даты
		for (int i = 0; i < BUF_LENGTH; ++i)
		{
			buf[i] = fin.get();
		};

		// выводим дату
		for (int i = 0; i < BUF_LENGTH; ++i)
		{
			std::cout << buf[i];
		};
		std::cout << SYMBOL_EMPTY << SYMBOL_EMPTY;

		// если времени нет, отобразить 6 пробелов и 1 дефис, иначе вывести время
		if (check_symbol == SYMBOL_EMPTY)
		{
			for (int i = 0; i < 6; ++i)
			{
				std::cout << SYMBOL_EMPTY;
			};
			std::cout << SYMBOL_DEFIS;
		}
		else
		{
			// копируем в буфер часы начала рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				buf[i] = fin.get();
			};

			// отображаем часы начала рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				std::cout << buf[i];
			};

			// знак ':'
			std::cout << ':';

			// копируем в буфер минуты начала рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				buf[i] = fin.get();
			};

			// отображаем минуты начала рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				std::cout << buf[i];
			};

			// знак " - "
			std::cout << " - ";

			// копируем в буфер часы окончания рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				buf[i] = fin.get();
			};

			// отображаем часы окончания рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				std::cout << buf[i];
			};

			// знак ':'
			std::cout << ':';

			// копируем в буфер минуты окончания рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				buf[i] = fin.get();
			};

			// отображаем минуты окончания рабочего дня
			for (int i = 0; i < BUF_LENGTH; ++i)
			{
				std::cout << buf[i];
			};
		};
		std::cout << '\n';
	};
	fin.close();
}