#include "TimeControl.h"
#include "TimeControl.cpp"

int main ()
{
    char command;

    for (;;)
    {
    	cout << endl;
    	wt::TimeControl::Calculate();
    	cout << "> ";
    	cin >> command;

        switch (command)
        {
        case 'a':
        	{
        		wt::TimeControl dayParameters;
        		dayParameters.Add();
        	};
            break;

        case 'c':
        	{
        		wt::TimeControl dayParameters;
        		dayParameters.Add(true);   // true - режим коррекции
        	};
            break;

       // case 'd':
        	//wt::TimeControl::Delete();
           // break;

        case 's':
        	wt::TimeControl::Show();
            break;

        case 'r':
        	wt::TimeControl::Reset();
            break;

        case 'q':
            return 0;
            break;

        default:
        	cout << "Unknown command.\n";
        }
    }
}
