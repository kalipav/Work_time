// класс, управляющий подсчетом времени
#include "TimeControl.h"

// ключ для установки следующего месяца
#define PASSWORD "next"

int main ()
{
    std::cout << "\tWORK TIME CONTROL\n";
	
    // проверить целостность файла, поля
    if (!wt::TimeControl::Check())
    {
        std::cout << "Errors found. Exit...\n";
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
                std::cout << "You try to set next month and delete all information.\n";

                // переменная для ввода ключа пользователем (используется для защиты от случайного сброса)
                std::string userKey;

                // ввод ключа
                cout << "Enter \""<< PASSWORD << "\" for activate:\n";
                cout << "> ";
                cin >> userKey;

                // проверка корректности ввода
                if (PASSWORD == userKey)
                {
                    wt::TimeControl::SetNextMonth();
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
            //
            break;

        // выйти из программы
        case 'q':
            return 0;

        default:
        	cout << "Unknown command.\n";
        };

        // проверить целостность файла, поля
        if (!wt::TimeControl::Check())
        {
            std::cout << "Errors found. Exit...\n";
            break;
        };
    };
}
