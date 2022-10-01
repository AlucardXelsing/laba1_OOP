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
    Node* next;
    Node* prev;
}typedef NODE;


class BasePay
{
public:
	BasePay();
	~BasePay();
    void AddCar();
    void DeleteCar();
    void PrintAllCar();
private:
    DATA ReadData();
    bool ExistNumber(std::string number);
private:
    NODE* first;
public:
    CustomMenu menu=CustomMenu(1500,850);
};

BasePay::BasePay()
{
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

void BasePay::PrintAllCar() {
    lineInTable head[3];
    char textPay[26];
    NODE* temp=first;
    head[0].length = 20;
    head[1].length = 20;
    head[2].length = -1;
    head[0].name = "Номер";
    head[1].name = "Штраф, р";
    menu.Drawtable(head);
    if (!first)
        return;
    do
    {
        head[0].name.clear();
        head[1].name.clear();
        sprintf(textPay, "%14.2f", temp->info.pay);
        head[0].name = temp->info.number;
        head[1].name = textPay;
        menu.Drawtable(head, 0, 0);
        temp = temp->next;
    } while (temp!=first);
}

bool BasePay::ExistNumber(std::string number) {
    bool flagFirst = true;
    bool findNumber=true;
    NODE* temp = first;
    if (!first)
        return true;
    for (; temp != first || flagFirst; temp = temp->next) {
        if (flagFirst)
            flagFirst = false;
        findNumber = true;
        for (int i = 0; i < number.length(); i++) {
            if (number[i] != temp->info.number[i]) {
                findNumber = false;
                break;
            }
        }
        if (findNumber)
            return true;
    }
    return false;
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

void BasePay::DeleteCar() {
    std::string number;
    NODE* temp=first;
    std::string text;
    bool firstFlag = true;
    bool findNumber = false;
    do
    {
        menu.ClearWorkSpace();
        menu.SetCursorPositionByY(0);
        std::cout << "Ведите номер автомобиля ________(для выхода ведите exit)";
        menu.SetCursorPositionByX(24);
        std::cin >> number;
        if (number == "exit")
            return;
        if (number.length() > 9) {
            menu.ShowInfoWindow("Веденый номер больше 9");
            continue;
        }
        if (number.length() < 8) {
            menu.ShowInfoWindow("Веденый номер меньше 8");
            continue;
        }
        if (ExistNumber(number)) {
            menu.ShowInfoWindow("Такой номер уже существует");
            continue;
        }
    } while (number.length() > 9 || number.length() < 8 || ExistNumber(number));
    for (; temp != first || firstFlag; temp = temp->next) {
        if (firstFlag)
            firstFlag = false;
        findNumber = true;
        for (int i = 0; i < number.length(); i++) {
            if (number[i] != temp->info.number[i]) {
                findNumber = false;
                break;
            }
        }
        if (findNumber)
            break;
    }
    text = "Хотите удалить автомобиль с номером ";
    text += temp->info.number;
    text += " с штрафом ";
    text += temp->info.pay;
    if (menu.YesOrNoWindow(text))
        return;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    delete temp;
}

DATA BasePay::ReadData() {
    std::string number;
    DATA info;
    float pay=0;
    do
    {
        menu.ClearWorkSpace();
        menu.SetCursorPositionByY(0);
        std::cout << "Ведите номер автомобиля ________";
        menu.SetCursorPositionByX(24);
        std::cin >> number;
        if (number.length() > 9) {
            menu.ShowInfoWindow("Веденый номер больше 9");
            continue;
        }
        if (number.length() < 8) {
            menu.ShowInfoWindow("Веденый номер меньше 8");
            continue;
        }
        if (ExistNumber(number)) {
            menu.ShowInfoWindow("Такой номер уже существует");
            continue;
        }
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
    BasePay pays;
    int pointMenu = 2;
    while ( pointMenu != -1) {
        pointMenu = pays.menu.MoveInMenu();
        pays.menu.ClearWorkSpace();
        switch (pointMenu)
        {
        case 1:
            pays.AddCar();
            break;
        case 2:
            pays.PrintAllCar();
            break;
        case 4:
            pays.DeleteCar();
            break;
        default:
            break;
        }
    }
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
