// класс, управляющий подсчетом времени
#include "TimeControl.h"
#include "TimeControl.cpp"

int main ()
{
    // переменная для записи команды
    char command;

    // бесконечный цикл для switch
    for (;;)
    {
    	cout << endl;

        // вывод времени
    	wt::TimeControl::Calculate();

        // ввод команды
    	cout << "> ";
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

        default:
        	cout << "Unknown command.\n";
        }
    }
}
