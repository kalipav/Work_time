#include "TimeControl.h"
#include <fstream>


wt::TimeControl::TimeControl()
{
    m_buffer.day = 0;
    m_buffer.startHour = 0;
    m_buffer.startMinute = 0;
    m_buffer.finishHour = 0;
    m_buffer.finishMinute = 0;

    //cout << "Constructor.\n";
}


int wt::TimeControl::ConvertCharToInt (const char* p_MAS_CHAR)
{
	int number = 0;

	for (int i = 0; i < 10; ++i)
	{
	    if (*p_MAS_CHAR == 48 + i) number += i * 10;  // '0' = 48 (десятич.), '1' = 49, ..., '9' = 57
	    if (*(p_MAS_CHAR+1) == 48 + i) number += i;
	};

	return number;
}


void wt::TimeControl::Calculate()
{
	std::ifstream fin ("Data.wt", std::ios::in);
	if (!fin)
	{
		cout << "Error! File not open.\n";
	}
	else
	{
		fin.seekg (0, std::ios::beg);
		if (fin.get() == 'v')    // если первый символ в файле - 'v', то с файлом все в порядке
		{
			char masChar[2] = {0, 0}; // для чисел, состоящих из 2-х цифр
			int bufferMinutes = 0;    // содержит текущее значение

			masChar[1] = fin.get(); // masChar[0] не используется, т.к. для поиска достаточно одной буферной переменной

			while (!fin.eof())
			{
				if (masChar[1] == '.') // если найдена точка
				{
					masChar[1] = fin.get(); // считать след. символ

					if (masChar[1] == ' ') // если вместо конкретного часа установлен пробел, значит время не занесено и учитывать этот день не нужно
					{
						continue;
					}
					else // если установлена дата, то ее необходимо учесть
					{
						wt::TimeControl bufferDate;

						masChar[0] = masChar[1]; // переписываем первую цифру стартового часа из 1-го элемента (это не ' ')
						masChar[1] = fin.get(); // считываем вторую цифру стартового часа
						bufferDate.m_buffer.startHour = ConvertCharToInt(masChar);
						fin.seekg(1, std::ios::cur);

						masChar[0] = fin.get(); // считываем первую цифру стартовых минут
						masChar[1] = fin.get(); // считываем вторую цифру стартовых минут
						bufferDate.m_buffer.startMinute = ConvertCharToInt(masChar);
						fin.seekg(1, std::ios::cur);

						masChar[0] = fin.get(); // считываем первую цифру финишных часов
						masChar[1] = fin.get(); // считываем вторую цифру финишных часов
						bufferDate.m_buffer.finishHour = ConvertCharToInt(masChar);
						fin.seekg(1, std::ios::cur);

						masChar[0] = fin.get(); // считываем первую цифру финишных минут
						masChar[1] = fin.get(); // считываем вторую цифру финишных минут
						bufferDate.m_buffer.finishMinute = ConvertCharToInt(masChar);

						// добавляет реальное рабочее время за день
						bufferMinutes += bufferDate.m_buffer.finishHour * 60 + bufferDate.m_buffer.finishMinute - (bufferDate.m_buffer.startHour * 60 + bufferDate.m_buffer.startMinute);
						bufferMinutes -= WORK_MINUTES; // вычитает 8ч 45м (525м)
					};
				}
				else
				{
					masChar[1] = fin.get();
				}

			}; // закрывает while

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
		else
		{
			cout << "File crushed.\n";
		}
	};
	fin.close();
}


void wt::TimeControl::Show()
{
	std::ifstream fin ("Data.wt", std::ios::in);
	if (!fin)
	{
		cout << "Error! File not open.\n";
	}
	else
	{
		fin.seekg (0, std::ios::beg);
		if (fin.get() == 'v')    // если первый символ в файле - 'v', то с файлом все в порядке
		{
			char buf;
			while (!fin.eof())
			{
				buf = fin.get(); // из-за кодировки
				cout << buf;
			};
			cout << endl;
		}
		else
		{
			cout << "File crushed.\n";
		}
	};
	fin.close();
}


void wt::TimeControl::Reset()
{
	std::string password = "reset"; // ключ для сброса
	std::string userKey;

	cout << "Enter \"reset\" for activate:\n";
	cout << "> ";
	cin >> userKey;

	if (password == userKey)
	{
		std::ofstream fout ("Data.wt");
		if (!fout)
		{
			cout << "Error! File not open.\n";
		}
		else
		{
			char m1[] = "v\n"; // индикатор корректного файла
			char m2[] = ".  :  -  :  \n"; // шаблон заполнения времени

			fout.write(m1, 2);
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


void wt::TimeControl::ConvertIntToChar (const int& r_NUMBER, char* p_massChar)
{
	for (int i = 0; i < 10; ++i)
	{
		if (r_NUMBER/10 == i) *p_massChar = i+48; // '0' = 48 (десятич.), '1' = 49, ..., '9' = 57
		if (r_NUMBER%10 == i) *(p_massChar+1) = i+48;
	};
}


void wt::TimeControl::Add (bool flag) //флаг false (по умолчанию) - режим вставки нового значения, true - режим коррекции
{
	cin >> m_buffer.day >> m_buffer.startHour >> m_buffer.startMinute >> m_buffer.finishHour >> m_buffer.finishMinute;
	if (m_buffer.day >= MIN_DAY && m_buffer.day <= MAX_DAY &&
		m_buffer.startHour >= MIN_HOUR && m_buffer.startHour <= MAX_HOUR &&
		m_buffer.startMinute >= MIN_MINUTE && m_buffer.startMinute <= MAX_MINUTE &&
		m_buffer.finishHour >= MIN_HOUR && m_buffer.finishHour <= MAX_HOUR &&
		m_buffer.finishMinute >= MIN_MINUTE && m_buffer.finishMinute <= MAX_MINUTE)
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
