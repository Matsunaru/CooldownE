#include <iostream>
#include <windows.h>
#include <thread>
using namespace std;

bool insAndDownPressed = false;

void setCursorPosition(int x, int y)//sets cursor position
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void klawisz()//first Key graber
{
    while (true)
    {
        if (GetAsyncKeyState(0x36) & 0x8000)//grabing "6"
        {
            for (int i = 60; i >= 0; i--)
            {
                setCursorPosition(0, 0);//seting cursor on position 0,0
                cout << i << endl;
                Sleep(1000);
            }
        }
    }
}

void klawisz2()//2nd key graber
{
    while (true)
    {
        if ((GetAsyncKeyState(0x2D) & 0x8000) && (GetAsyncKeyState(0x28) & 0x8000)) //checking if ins and arrow down is press if yes, then 'true'
        {
            insAndDownPressed = true;
        }
        {
            if ((insAndDownPressed == true) && (GetAsyncKeyState(0x43) & 0x8000))//checking if down&ins is true, and if 'c' was press
            {

                for (int i = 60; i >= 0; i--)
                {
                    setCursorPosition(0, 1);// seting pos on 0,1
                    cout << i << endl;
                    Sleep(1000);
                }
                insAndDownPressed = false;// returing ins&down on false
            }
        }
    }
}

int main()
{
    thread t1(klawisz);//atach key graber on thread t1
    thread t2(klawisz2);//atach 2nd key graber on thread t2

    t1.detach();//detach t1 from main program
    t2.detach();//detach t2 from main program

    while (true)//it make program stay always on
    {
        Sleep(1000);
    }
    return 0;
}

