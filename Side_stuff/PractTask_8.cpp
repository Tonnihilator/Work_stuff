#include <iostream>
#include <exception>
#include <conio.h>
#include <Windows.h>


using namespace std;

template <typename T1, typename T2>
double div(T1 divident, T2 divider)
{
    try
    {
        if (divider == 0)
            throw "DivisionByZero";
        return divident / divider;
    }
    catch (const char* ex)
    {
        throw ex;
    }
}

class Ex
{
    public:
        ~Ex()
        {
            //cout << "exs died :(" << endl;
        }
        Ex(unsigned int _x) : x{ _x } 
        {
           // cout << "exs was born" << endl;
        }

        friend ostream& operator<<(ostream& out, Ex& exc)
        {
            out << exc.x;
            return out;
        }

    private:
        unsigned int x;
};

class Bar
{
    public:
        Bar()
        {
            y = 0;
        }

        void set(unsigned int a)
        {
            try
            {
                if (y + a > 100)
                {
                    Ex exc(y * a);
                    throw exc;
                }
                y = a;
                cout << "Entered number is : " << y << endl;
            }
            catch (Ex ex)
            {
                throw ex;
            }
        }

    private:
        unsigned int y;
};

class OffTheField
{
    public:
        OffTheField(short _xPos, short _yPos, short _direction) : xPos{ _xPos }, yPos{ _yPos }, direction{_direction}
        {
        }
        void errMsg()
        {
            cout << "Крестик находится по координатам (" << xPos + 1 << "; " << yPos + 1 << ") и не может продолжать движение ";
            switch (direction)
            {
                case 0:
                    cout << "вверх!   ";
                    break;
                case 1:
                    cout << "вправо! ";
                    break;
                case 2:
                    cout << "вниз!   ";
                    break;
                case 3:
                    cout << "влево!   ";
                    break;
            }
        }
    private:
        short xPos, yPos, direction;
};

class illegalCommand
{
    public:
        illegalCommand(short _xPos, short _yPos) : xPos{ _xPos }, yPos{ _yPos }
        {
        }
        void errMsg()
        {
            cout << "Крестик, находящийся по координатам (" << xPos + 1 << "; " << yPos + 1 << ") получил неправильную команду! Управляйте стрелками, или введи \"exit\"!:";
        }
    private:
        short xPos, yPos;
};

class Robot
{
    public:
        Robot(short _x, short _y) : fiesldSizeX{ _x }, fiesldSizeY{ _y } 
        {
            system("cls");
            printField();
        }

        bool processKey(char inputKey)
        {
            try
            {
                if (inputKey != 0x48 && inputKey != 0x50 && inputKey != 0x4B && inputKey != 0x4D)
                {
                    illegalCommand ex(roboXPos, roboYPos);
                    throw ex;
                }
                switch (inputKey)
                {
                case 0x48:
                    moveUp();
                    break;
                case 0x50:
                    moveDown();
                    break;
                case 0x4B:
                    moveLeft();
                    break;
                case 0x4D:
                    moveRight();
                    break;
                }
            }
            catch (illegalCommand ex)
            {
                printField();
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleCursorPosition(hConsole, { 1, (SHORT)(fiesldSizeY + 1) });
                ex.errMsg();

                if (wrongChar(inputKey))
                    return true;
                else
                    return false;
            }
        }

    private:
        short fiesldSizeX;
        short fiesldSizeY;
        short roboXPos = 0;
        short roboYPos = 0;
        char inputArr[4] = { 0 };

        void printField()
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(hConsole, { 0, (SHORT)(0) });
            cout << "Перемещайте крестик, нажимая на стрелки! (Введите \"Exit\" для выхода)" << endl;

            for (int i = 0; i < fiesldSizeY; i++)
            {
                SetConsoleCursorPosition(hConsole, { 1, (SHORT)(i + 1) });
                for (int j = 0; j < fiesldSizeX; j++)
                {
                    if (i == roboYPos && j == roboXPos)
                        cout << "\x1B[91m" << "X " << "\033[0m";
                    else
                        cout << "\x1B[93m" << ". " << "\033[0m";
                }
                cout << endl;
            }
            SetConsoleCursorPosition(hConsole, { 1, (SHORT)(fiesldSizeY + 1) });
            for (int i = 0; i < 115; i++)
                cout << " ";
        }

        void moveLeft()
        {
            try
            {
                if (roboXPos == 0)
                {
                    OffTheField ex(roboXPos, roboYPos, 3);
                    throw ex;
                }
                roboXPos--;
                printField();
            }
            catch (OffTheField ex)
            {
                printField();
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleCursorPosition(hConsole, { 1, (SHORT)(fiesldSizeY + 1) });
                ex.errMsg();
            }
        }

        void moveRight()
        {
            try
            {
                if (roboXPos == (fiesldSizeX - 1))
                {
                    OffTheField ex(roboXPos, roboYPos, 1);

                    OffTheField exc = ex;
                    throw ex;
                }
                roboXPos++;
                printField();
            }
            catch (OffTheField ex)
            {
                printField();
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleCursorPosition(hConsole, { 1, (SHORT)(fiesldSizeY + 1) });
                ex.errMsg();
            }
        }

        void moveDown()
        {
            try
            {
                if (roboYPos == (fiesldSizeY - 1))
                {
                    OffTheField ex(roboXPos, roboYPos, 2);
                    throw ex;
                }
                roboYPos++;
                printField();
            }
            catch (OffTheField ex)
            {
                printField();
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleCursorPosition(hConsole, { 1, (SHORT)(fiesldSizeY + 1) });
                ex.errMsg();
            }
        }

        void moveUp()
        {
            try
            {
                if (roboYPos == 0)
                {
                    OffTheField ex(roboXPos, roboYPos, 0);
                    throw ex;
                }
                roboYPos--;
                printField();
            }
            catch (OffTheField ex)
            {
                printField();
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleCursorPosition(hConsole, { 1, (SHORT)(fiesldSizeY + 1) });
                ex.errMsg();
            }
        }

        bool wrongChar(char inputKey)
        {
            inputArr[3] = inputArr[2];
            inputArr[2] = inputArr[1];
            inputArr[1] = inputArr[0];
            inputArr[0] = inputKey;

            if ((inputArr[0] == 't' || inputArr[0] == 'T') && (inputArr[1] == 'I' || inputArr[1] == 'i') && (inputArr[2] == 'X' || inputArr[2] == 'x') && (inputArr[3] == 'E' || inputArr[3] == 'e'))
                return false;
            else
                return true;
        }
};

int main()
{
    system("color 0");
    setlocale(LC_ALL, "Russian");

    /*double res = 0;
    try
    {
        res = div <double>(3, 5);
        cout << res << endl;
    }
    catch (const char* ex)
    {
        cout << ex << endl;
    }

    try
    {
        res = div <double>(3, 0);
        cout << res << endl;
    }
    catch (const char* ex)
    {
        cout << ex << endl;
    }

    Bar b;
    string inputStr = "1";
    cout << "Enter a real number: (type 0 for exit)" << endl;
    while (inputStr != "0")
    {
        try
        {
            cin >> inputStr;
            b.set(atoi(inputStr.c_str()));
        }
        catch (Ex& exc)
        {
            cout << "Sum is more then 100, and thats an exc for some reason. Here's multiplication result: " <<  exc << endl;
            break;
        }
    }

    Sleep(1000);*/

    ///// Что-то меня немного унесло, но пусть будет

    system("cls");
    int inputCh1, inputCh2;
    Robot robot(20,20);

    bool robotIsFunctioning = true;

    while (robotIsFunctioning)
    {
        if (_kbhit())
        {
            inputCh1 = _getch();
            if (inputCh1 == 0xE0 || inputCh1 == 0x00)
            {
                inputCh2 = _getch();
                robotIsFunctioning = robot.processKey(inputCh2);
                cin.clear();
            }
            else
                robotIsFunctioning = robot.processKey(inputCh1);
        }
    }

}