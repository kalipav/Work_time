// класс, управляющий подсчетом времени
#include "TimeControl.h"

// пароль для установки следующего месяца
#define PASSWORD "next"

int main()
{
    std::cout << "\tWORK TIME CONTROL\n";
	
    // проверить целостность файла, полей
    if (!wt::TimeControl::Check())
    {
        std::cout << "Errors found. Exit...\n";
        _getch();
        return 0;
    };
    
    // приветствие пользователя
    wt::TimeControl::WelcomeUser();

    cout << "Enter 'h' for help.\n";

    // переменная для записи команды
    char command;

    // бесконечный цикл для switch
    for (;;)
    {
        // ввод команды
        cout << "\n> ";
    	command = _getch();
		std::cout << command << "\n";

        switch (command)
        {
        // добавить рабочий день
        case 'a':
        	{
                wt::TimeControl dayParams;
				dayParams.AddCorDel(ADDITION); // флаг на добавление
        	};
            break;

        // откорректировать рабочий день
        case 'c':
        	{
                wt::TimeControl dayParams;
                dayParams.AddCorDel(CORRECTION); // флаг на коррекцию
        	};
            break;

        // удалить рабочий день
        case 'd':
            {
                wt::TimeControl dayParams;
                dayParams.AddCorDel(DELETION); // флаг на удаление
            };
            break;

        // установить следующий месяц
        case 'n':
            {
                std::cout << "\nYou try to set next month and delete all information.\n";

                // переменная для ввода ключа пользователем (используется для защиты от случайного сброса)
                std::string userKey;

                // ввод ключа
                cout << "Enter \""<< PASSWORD << "\" and press \"ENTER\" for activate:\n";
                cout << "> ";
                cin >> userKey;

                // проверка корректности ввода
                if (PASSWORD == userKey)
                {
                    wt::TimeControl::SetNextMonth();
                }
                else
                {
                    std::cout << "Incorrect word. Operation has canceled.\n";
                };
            };
            break;

        // показать подробную информацию по датам
        case 's':
        	wt::TimeControl::Show();
            break;

        // показать время отработки
        case 't':
			{
				wt::TimeControl dayParams;
				dayParams.TimeToWork(); 
			};
			break;

        // справка
        case 'h':
            wt::TimeControl::Help();
            break;

        // выйти из программы
        case 'q':
            return 0;

        default:
        	cout << "Unknown command.\n";
        };

        // проверить целостность файла, полей
        if (!wt::TimeControl::Check())
        {
            std::cout << "Errors found. Exit...\n";
            _getch();
            return 0;
        };
    };
}
