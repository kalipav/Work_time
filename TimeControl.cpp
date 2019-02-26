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
// [in] const char* - массив
// [in] const int& - длина массива
// [out] int - преобразованное значение
int wt::TimeControl::ConvertCharToInt (char* p_MAS_CHAR, const int& r_LENGTH)
{
    // проверка на длину массива
    if (r_LENGTH > MAX_CONVERT_LENGTH || r_LENGTH <= 0)
    {
        std::cout << "Error! Convertation failed. Wrong length.\n";
        abort();
    };
    /*
    // проверка на наличие исключительно цифр в массиве
    for (int i = 0; i < r_LENGTH; ++i)
    {
        // символ '0' - это 48 в десятич. системе, '1' = 49, ..., '9' = 57
        if ((int)p_MAS_CHAR[i] < 48 || (int)p_MAS_CHAR[i] > 57)
        {
            std::cout << "Error! Try to convert letter.\n";
            abort();
        }
    };
    */
    // начальное значение числа
    int number = 0;

    // буфер для символа при перевороте
    char buf;

    // переворачиваем массив для корректности разрядов
    if (r_LENGTH == 2)
    {
        // меняем местами элементы массива
        buf = p_MAS_CHAR[0];
        p_MAS_CHAR[0] = p_MAS_CHAR[1];
        p_MAS_CHAR[1] = buf;
    }
    else if (r_LENGTH == 3)
    {
        // меняем местами 0-ой и 2-ой элементы
        buf = p_MAS_CHAR[0];
        p_MAS_CHAR[0] = p_MAS_CHAR[2];
        p_MAS_CHAR[2] = buf;
    }
    else if (r_LENGTH == 4)
    {
        // меняем местами 0-ой и 3-ий, 1-ый и 2-ой элементы
        buf = p_MAS_CHAR[0];
        p_MAS_CHAR[0] = p_MAS_CHAR[3];
        p_MAS_CHAR[3] = buf;
        buf = p_MAS_CHAR[1];
        p_MAS_CHAR[1] = p_MAS_CHAR[2];
        p_MAS_CHAR[2] = buf;
    };

    // переводим число
	for (int i = 0; i < 10; ++i)
	{
        // символ '0' - это 48 в десятич. системе, '1' = 49, ..., '9' = 57
        if (p_MAS_CHAR[0] == 48 + i && r_LENGTH >= 1) number += i;
        if (p_MAS_CHAR[1] == 48 + i && r_LENGTH >= 2) number += i * 10;
        if (p_MAS_CHAR[2] == 48 + i && r_LENGTH >= 3) number += i * 100;
        if (p_MAS_CHAR[3] == 48 + i && r_LENGTH >= 4) number += i * 1000;
	};

	return number;
}

// вывод времени
void wt::TimeControl::Calculate()
{/*
    // создаем объект для вывода информации из файла
    std::ifstream fin ("Data.wt");

    // проверка открылся ли файл
	if (!fin)
	{
		cout << "Error! File not open.\n";
	}
	else
	{
        // перемещаем курсор в начало файла
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

                        // перемещаем курсор на 1 позицию вперед (пропускаем двоеточие и тире)
						fin.seekg(1, std::ios::cur);

                        // считываем первую цифру стартовых минут
                        masChar[0] = fin.get();

                        // считываем вторую цифру стартовых минут
                        masChar[1] = fin.get();

                        // конвертируем
						bufferDate.m_buffer.startMinute = ConvertCharToInt(masChar);

                        // перемещаем курсор на 1 позицию вперед (пропускаем двоеточие и тире)
						fin.seekg(1, std::ios::cur);

                        // считываем первую цифру финишных часов
                        masChar[0] = fin.get();

                        // считываем вторую цифру финишных часов
                        masChar[1] = fin.get();

                        // конвертируем
						bufferDate.m_buffer.finishHour = ConvertCharToInt(masChar);

                        // перемещаем курсор на 1 позицию вперед (пропускаем двоеточие и тире)
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

// показать подробно рабочее время
void wt::TimeControl::Show()
{
    // объект для вывода информации из файла
    std::ifstream fin ("Data.wt");

    // проверка открылся ли файл
	if (!fin)
	{
		cout << "Error! File not open.\n";
	}
	else
	{
        // переместить курсор в начало файла
		fin.seekg (0, std::ios::beg);

        // если первый символ в файле - 'v', то с файлом все в порядке
        if (fin.get() == 'v')
		{
            // буферная переменная для считывания из файла
			char buf;

            // продолжать считывание пока не будет достигнут конец файла
			while (!fin.eof())
			{
                // считать символ
                buf = fin.get();

                // вывод символа
				cout << buf;
			};
			cout << endl;
		}

        // файл не прошел проверку на целостность
		else
		{
			cout << "File crushed.\n";
		}
	};
	fin.close();
}

// сбросить всё рабочее время
void wt::TimeControl::Reset()
{
    // ключ для сброса
    std::string password = "reset";

    // переменная для ввода ключа пользователем (используется для защиты от случайного сброса)
	std::string userKey;

    // ввод ключа
	cout << "Enter \"reset\" for activate:\n";
	cout << "> ";
	cin >> userKey;

    // проверка корректности ввода
	if (password == userKey)
	{
        // создаем объект, стираем файл
		std::ofstream fout ("Data.wt");

        // проверяем открылся ли файл
		if (!fout)
		{
			cout << "Error! File not open.\n";
		}
		else
		{
            // индикатор корректного файла
            char m1[] = "v\n";

            // шаблон заполнения времени
            char m2[] = ".  :  -  :  \n";

            // записываем в файл 2 символа из массива1
			fout.write(m1, 2);

            // записываем массив2 столько раз, сколько дней
			for (int i = MIN_DAY; i <= MAX_DAY; ++i)
			{
				if (i >= 1 && i <= 9) // чтобы записать 01, 02, ..., 09 для поисковика
				{
                    fout.put('0');
				};
				fout << i;
				fout.write(m2, 13);
			};
			cout << "Reset realized.\n";
		};
		fout.close();
	}
	else
	{
		cout << "Reset cancelled.\n";
	}
}

// преобразование int в char
// [in]     const int& - возвращаемое число в int
// [in/out] char*      - массив char из 2-х цифр
void wt::TimeControl::ConvertIntToChar (const int& r_NUMBER, char* p_massChar)
{
	for (int i = 0; i < 10; ++i)
	{
        // символ '0' - это 48 в десятич. системе, '1' = 49, ..., '9' = 57
        if (r_NUMBER/10 == i) *p_massChar = i+48;
		if (r_NUMBER%10 == i) *(p_massChar+1) = i+48;
	};
}

// добавить рабочий день
// [in] const wt::Add_status& - флаг добавления/корректировки
void wt::TimeControl::Add (const wt::Add_status& flag)
{
    // из-за битовых полей в структуре необходимо ввести промежуточную переменную для ввода
    int temp;

    // осуществляем ввод дня, начала рабочего времени, конца рабочего времени
    cin >> temp;
    m_buffer.day = temp;
    cin >> temp;
    m_buffer.startHour = temp;
    cin >> temp;
    m_buffer.startMinute = temp;
    cin >> temp;
    m_buffer.finishHour = temp;
    cin >> temp;
    m_buffer.finishMinute = temp;

    // если введенные данные корректные, открываем файл для записи
	if (m_buffer.day >= MIN_DAY && m_buffer.day <= MAX_DAY &&
		m_buffer.startHour >= MIN_HOUR && m_buffer.startHour <= MAX_HOUR &&
		m_buffer.startMinute >= MIN_MINUTE && m_buffer.startMinute <= MAX_MINUTE &&
		m_buffer.finishHour >= MIN_HOUR && m_buffer.finishHour <= MAX_HOUR &&
		m_buffer.finishMinute >= MIN_MINUTE && m_buffer.finishMinute <= MAX_MINUTE)
	{
        // создаем объект для корректировки
		std::fstream fiout ("Data.wt", std::ios::in | std::ios::out);

        // проверяем открылся ли файл
		if (!fiout)
		{
			cout << "Error! File not open.\n";
		}
		else
		{
            // перемещаем курсор в начало файла
			fiout.seekg (0, std::ios::beg);

            // если первый символ в файле - 'v', то с файлом все в порядке
            if (fiout.get() == 'v')
			{
                    // создание массива, в котором хранятся даты и время в виде символов
                // число состоит из 2-х цифр
                char transformedNumbers[2] = {0,0};

                // конвертирует дату
                wt::TimeControl::ConvertIntToChar(m_buffer.day, transformedNumbers);

                    // запись времени в файл по дате
                // перемещаем курсор в начало файла
				fiout.seekg (0, std::ios::beg);

                // создаем массив для считывания (состоит из 3-х последовательных символов, считанных из файла)
				char symbolsFromFile[3] = {0,0,0};

                // записываем первые три символа
				for (int i = 0; i < 3; ++i)
				{
					symbolsFromFile[i] = fiout.get();
				};

                // поиск совпадений по 3 символам, шаблон - "ХХ."
                while (!fiout.eof())
				{
					if (symbolsFromFile[0] == transformedNumbers[0] && symbolsFromFile[1] == transformedNumbers[1] && symbolsFromFile[2] == '.')
					{
                        // хранит символ, следующий за символом '.', необходим для идентификации коррекции и ввода
                        char cellIndikator = fiout.get();

                        // возвращает курсор на позицию -1
                        fiout.seekg(-1, std::ios::cur);

                        // если ячейка занята и режим ввода
                        if (cellIndikator != ' ' && flag == wt::ADD)
						{
							cout << "Add aborted. See mode.\n";
							break;
						}

                        // если ячейка пуста и режим коррекции
                        else if (cellIndikator == ' ' && flag == wt::CORRECTION)
						{
							cout << "Correction aborted. See mode.\n";
                        }

                        // иначе осуществить ввод или коорекцию
                        else
						{
                            // устанавливает курсор записи
                            fiout.seekp (fiout.tellg(), std::ios::beg);

                            // конвертирует старт. час
                            wt::TimeControl::ConvertIntToChar(m_buffer.startHour, transformedNumbers);

                            // записывается старт. час
                            fiout << transformedNumbers[0] << transformedNumbers[1];

                            // пропуск символа
                            fiout.seekp (1, std::ios::cur);

                            // конвертирует старт. мин.
                            wt::TimeControl::ConvertIntToChar(m_buffer.startMinute, transformedNumbers);

                            // записывается старт. мин.
                            fiout << transformedNumbers[0] << transformedNumbers[1];

                            // пропуск символа
                            fiout.seekp (1, std::ios::cur);

                            // конвертирует финиш. час
                            wt::TimeControl::ConvertIntToChar(m_buffer.finishHour, transformedNumbers);

                            // записывается финиш. час
                            fiout << transformedNumbers[0] << transformedNumbers[1];

                            // пропуск символа
                            fiout.seekp (1, std::ios::cur);

                            // конвертирует финиш. мин.
                            wt::TimeControl::ConvertIntToChar(m_buffer.finishMinute, transformedNumbers);

                            // записывается финиш. мин.
                            fiout << transformedNumbers[0] << transformedNumbers[1];

                            // если флаг "добавление"
                            if (flag == wt::ADD)
							{
								cout << "New day added.\n";
							}
							else
							{
								cout << "Correction done.\n";
							}
						};

                        // после проверок, ввода, коррекции - выход из цикла
                        break;
					}

                    // пока не найдена дата, получить следующий символ из файла за одну итерацию
                    else
					{
						symbolsFromFile[0] = symbolsFromFile[1];
						symbolsFromFile[1] = symbolsFromFile[2];
						symbolsFromFile[2] = fiout.get();
					}
				} // скобка цикла while
			}
			else
			{
				cout << "File crushed.\n";
			}
		};
		fiout.close();
	}
	else
	{
		cout << "Incorrect enter data.\n";
	}
}

/*
void wt::TimeControl::Delete ()
{
	int day;
	cin >> day;
	if (day >= MIN_DAY && day <= MAX_DAY)
	{
		std::fstream fiout ("Data.wt", std::ios::in | std::ios::out);
		if (!fiout)
		{
			cout << "Error! File not open.\n";
		}
		else
		{
			fiout.seekg (0, std::ios::beg);
			if (fiout.get() == 'v')    // если первый символ в файле - 'v', то с файлом все в порядке
			{




				// создание массива, в котором хранятся даты и время в виде символов

				char transformedNumbers[2] = {0,0}; // число состоит из 2-х цифр
				wt::TimeControl::ConvertIntToChar(m_buffer.day, transformedNumbers); // конвертирует дату


				// запись времени в файл по дате

				fiout.seekg (0, std::ios::beg);

				char symbolsFromFile[3] = {0,0,0};
				for (int i = 0; i < 3; ++i)
				{
					symbolsFromFile[i] = fiout.get();
				};

				while (!fiout.eof())   // поиск совпадений по 3 символам "ХХ."
				{
					if (symbolsFromFile[0] == transformedNumbers[0] && symbolsFromFile[1] == transformedNumbers[1] && symbolsFromFile[2] == '.')
					{
						char cellIndikator = fiout.get(); // хранит символ, следующий за символом '.', необходим для идентификации коррекции и ввода
						fiout.seekg(-1, std::ios::cur);  // возвращает курсор на позицию -1

						if (cellIndikator != ' ' && flag == false) // если ячейка занята и режим ввода
						{
							cout << "Add aborted. See mode.\n";
							break;
						}
						else if (cellIndikator == ' ' && flag == true) // если ячейка пуста и режим коррекции
						{
							cout << "Correction aborted. See mode.\n";
						}
						else // иначе осуществить ввод или коорекцию
						{
							fiout.seekp (fiout.tellg(), std::ios::beg); // устанавливает курсор записи

							wt::TimeControl::ConvertIntToChar(m_buffer.startHour, transformedNumbers); // конвертирует старт. час
							fiout << transformedNumbers[0] << transformedNumbers[1]; // записывается старт. час

							fiout.seekp (1, std::ios::cur); // пропуск символа
							wt::TimeControl::ConvertIntToChar(m_buffer.startMinute, transformedNumbers); // конвертирует старт. мин.
							fiout << transformedNumbers[0] << transformedNumbers[1]; // записывается старт. мин.

							fiout.seekp (1, std::ios::cur); // пропуск символа
							wt::TimeControl::ConvertIntToChar(m_buffer.finishHour, transformedNumbers); // конвертирует финиш. час
							fiout << transformedNumbers[0] << transformedNumbers[1]; // записывается финиш. час

							fiout.seekp (1, std::ios::cur); // пропуск символа
							wt::TimeControl::ConvertIntToChar(m_buffer.finishMinute, transformedNumbers); // конвертирует финиш. мин.
							fiout << transformedNumbers[0] << transformedNumbers[1]; // записывается финиш. мин.

							if (flag == false)
							{
								cout << "New day added.\n";
							}
							else
							{
								cout << "Correction done.\n";
							}
						};

						break; // после проверок, ввода, коррекции - выход из цикла
					}
					else // пока не найдена дата, получить следующий символ из файла за одну итерацию
					{
						symbolsFromFile[0] = symbolsFromFile[1];
						symbolsFromFile[1] = symbolsFromFile[2];
						symbolsFromFile[2] = fiout.get();
					}
				} // скобка цикла while
			}
			else
			{
				cout << "File crushed.\n";
			}
		};
		fiout.close();
	}
	else
	{
		cout << "Incorrect enter data.\n";
	}
}
*/

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
    // устанавливаем курсор на начало файла
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

    // переносим курсор на позицию для считывания последних трех символов
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

        // массив для чисел дней
        char day[2];

        // конвертация числа в символьное значение
        ConvertIntToChar(i, day);

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
    // перемещаем курсор на позицию с именем для ввода имени
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
    // перемещаем курсор на позицию с годом
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
    // перемещаем курсор на позицию с месяцем
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
    // перемещаем курсор на позицию с днем недели
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
    // перемещаем курсор на позицию с количеством рабочих часов
    finout.seekp(POS_WORK_TIME, std::ios::beg);

    // пустые поля заполняем нулями
    if (buf.size() < WORK_TIME_LENGTH)
    {
        for (int i = 0; i < WORK_TIME_LENGTH - buf.size(); ++i)
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
    // перемещаем курсор на позицию с обеденным временем
    finout.seekp(POS_DINNER_TIME, std::ios::beg);

    // пустые поля заполняем нулями
    if (buf.size() < DINNER_TIME_LENGTH)
    {
        for (int i = 0; i < DINNER_TIME_LENGTH - buf.size(); ++i)
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

    // перемещаем курсор на позицию ввода имени для чтения
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
        if (name[i] != ' ')
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
    int length = YEAR_LENGTH > MONTH_LENGTH ? YEAR_LENGTH : MONTH_LENGTH;

    // буфер
    char buf[length];

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

    // февраль невисокосного года
    else if (month == FEBRUARY && year % 4 != 0)
    {
        days = 29;
    }

    // февраль високосного года
    else if (month == FEBRUARY && year % 4 == 0)
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
