#include "Header.h"

int main()
{
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	setlocale(0,"");
	List students;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    string menu0 = "Считывание списка с файла\n";
    string menu1 = "Добавление элемента в список\n";
    string menu2 = "Сохранение списка в файл\n";
    string menu3 = "Вывод списка\n";
    int k = 0;

    while (1)
    {
        switch (k)
        {
        case 0:
            SetConsoleTextAttribute(handle, 14);
            cout << menu0;
            SetConsoleTextAttribute(handle, 7);
            cout << menu1;
            cout << menu2;
            cout << menu3;
            break;
        case 1:
            cout << menu0;
            SetConsoleTextAttribute(handle, 14);
            cout << menu1;
            SetConsoleTextAttribute(handle, 7);
            cout << menu2;
            cout << menu3;
            break;
        case 2:
            cout << menu0;
            cout << menu1;
            SetConsoleTextAttribute(handle, 14);
            cout << menu2;
            SetConsoleTextAttribute(handle, 7);
            cout << menu3;
            break;
        case 3:
            cout << menu0;
            cout << menu1;
            cout << menu2;
            SetConsoleTextAttribute(handle, 14);
            cout << menu3;
            SetConsoleTextAttribute(handle, 7);
            break;
        }
        int f;
        while (1)
        {
            f = _getch();
            if (f == 13)
            {
                system("cls");
                switch (k)
                {
                case 0:
                    students.clear();
                    load_from_file(students);
                    break;
                case 1:
                    MENU1(students);
                    break;
                case 2:
                    savetofile(students);
                    break;
                case 3:
                    students.showlist();
                    break;
                }
                break;
            }
            else if (f == 72)
            {
                k--;
                break;
            }
            else if (f == 80)
            {
                k++;
                break;
            }
            else if (f == 27)
            {
                break;
            }
        }
        if (f == 27)
            break;
        if (k < 0)
            k = 3;
        if (k > 3)
            k = 0;
        system("cls");
    }

	students.~List();
	return 0;
}