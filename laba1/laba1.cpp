// laba1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "D:/Library/CustomMenu/CustomMenu/CustomMenu.h"
#include <iostream>

struct Date {
    char number[9];
    float pay;
}typedef DATA;

struct Node {
    DATA info;
    NODE* next;
    NODE* prev;
}typedef NODE;


class BasePay
{
public:
	BasePay();
	~BasePay();
    void AddCar();
private:
    DATA ReadData();
private:
    NODE* first;
public:
    static CustomMenu menu;
};

BasePay::BasePay()
{
    CustomMenu menu(1500, 850);
    menu.AddPointMenu("Создать(Добавить)");
    menu.AddPointMenu("Показать данные");
    menu.AddPointMenu("Сумма всех штрафов");
    menu.AddPointMenu("Удалить");
    first = NULL;
}

BasePay::~BasePay()
{
    delete first;
}


void BasePay::AddCar() {
    DATA info = ReadData();
    NODE* temp;
    NODE* end;
    bool flagFirst = true;
    std::string text;
    text = "Хотите сохранить машину с номером ";
    text += info.number;
    text += " с штрафом ";
    text += info.pay;
    menu.YesOrNoWindow(text);
    if (!first) {
        first = new NODE;
        first->next = first;
        first->prev = first;
        first->info = info;
    }
    else {
        end = first;
        temp = new NODE;
        temp->next = first;
        temp->info = info;
        if (first->next = first) {
            first->next = temp;
            first->prev = temp;
            return;
        }
        for (; end->next != first || flagFirst; end = end->next) {
            flagFirst = false;
        };
        end->next = temp;
        temp->next = first;
        first->prev = temp;
        return;
    }
}

DATA BasePay::ReadData() {
    std::string number;
    DATA info;
    float pay;
    do
    {
        menu.ClearWorkSpace();
        menu.SetCursorPositionByY(0);
        std::cout << "Ведите номер автомобиля ________";
        menu.SetCursorPositionByX(24);
        std::cin >> number;
        if (number.length() > 9)
            menu.ShowInfoWindow("Веденый номер больше 9");
        if (number.length() < 8)
            menu.ShowInfoWindow("Веденый номер меньше 8");
    } while (number.length() > 9 || number.length() < 8);
    for (int i = 0; i < number.length(); i++)
        info.number[i] = number[i];
    do
    {
        menu.SetCursorPositionByY(0);
        std::cout << "Ведите номер автомобиля " << number;
        menu.SetCursorPositionByY(1);
        std::cout << "Ведите сумму штрафа: ";
        if (pay < 0)
            menu.ShowInfoWindow("Штраф не может быть отрицательным");
    } while (pay < 0);
    info.pay = pay;
    return info;
}

int main()
{
    std::cout << "Hello World!\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
