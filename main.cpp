// класс, управляющий подсчетом времени
#include "TimeControl.h"
#include "TimeControl.cpp"

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
    	cin >> command;

        switch (command)
        {
        // добавить рабочий день
        case 'a':
        	{
        		wt::TimeControl dayParameters;
        		dayParameters.Add();
        	};
            break;

        // откорректировать рабочий день
        case 'c':
        	{
        		wt::TimeControl dayParameters;
                dayParameters.Add(wt::CORRECTION); // флаг на коррекцию
        	};
            break;

       // case 'd':
           // wt::TimeControl::Delete();
           // break;

        // показать подробно рабочее время
        case 's':
        	wt::TimeControl::Show();
            break;

        // сбросить всё рабочее время
        case 'r':
        	wt::TimeControl::Reset();
            break;

        // выйти из программы
        case 'q':
            return 0;

        // установить следующий месяц
        case 'n':
            {
                /*// ключ для установки следующего месяца
                std::string password = "next";

                // переменная для ввода ключа пользователем (используется для защиты от случайного сброса)
                std::string userKey;

                // ввод ключа
                cout << "Enter \"next\" for activate:\n";
                cout << "> ";
                cin >> userKey;

                // проверка корректности ввода
                if (password == userKey)
                {*/
                    wt::TimeControl::SetNextMonth();
                //};

                std::cout << "Next month set.\n";
            };
            break;

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
