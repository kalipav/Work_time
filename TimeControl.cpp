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
// [in] const char* - массив, состоящий из 2-х символов
// [out] int - преобразованное значение
int& wt::TimeControl::ConvertCharToInt (const char* p_MAS_CHAR)
{
    int number = 0;

	for (int i = 0; i < 10; ++i)
	{
        // символ '0' - это 48 в десятич. системе, '1' = 49, ..., '9' = 57
        if (*p_MAS_CHAR == 48 + i) number += i * 10;
	    if (*(p_MAS_CHAR+1) == 48 + i) number += i;
	};

	return number;
}

// вывод времени
void wt::TimeControl::Calculate()
{
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
                        bufferMinutes -= WORK_MINUTES;
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
}

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
