#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Chain
{
    int data;
    Chain* next;
};

void Append(Chain** p, int newData)
{
    Chain* newNode = new Chain();
    newNode->data = newData;
    newNode->next = nullptr;

    Chain* last = *p;

    if (*p == NULL)
    {
        *p = newNode;
        return;
    }

    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
}

void deleteList(Chain** headRef)
{
    Chain* current = *headRef;
    Chain* next = NULL;

    while (current != NULL)
    {
        next = current->next;
        delete current;
        current = next;
    }

    *headRef = NULL;
}

void PrintDirect(Chain* p)
{
    if (p == NULL)
    {
        return;
    }
    cout << p->data << " ";
    PrintDirect(p->next);
}

Chain* deleteAfterX(Chain* first, int x)
{
    Chain* newList = NULL;
    Chain* temp, * before;
    before = first;
    temp = first;
    int i = 1;

    while (temp != nullptr)
    {
        if (temp->data == x && i == 1)
        {
            before = temp;
            temp = temp->next;
            i = 2;
        }
        else if (i == 2)
        {
            before->next = temp->next;
            Chain* nextTemp = temp->next;
            temp->next = newList;
            newList = temp;
            temp = nextTemp;
        }
        else
        {
            before = temp;
            temp = temp->next;
        }
    }

    return newList;
}

void PrintReverseDirect(Chain* p)
{
    if (p == NULL)
    {
        return;
    }
    PrintReverseDirect(p->next);
    cout << p->data << " ";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    ifstream inputFile("input.txt");

    string line;
    Chain* head_1 = NULL;
    Chain* head_2 = NULL;

    if (getline(inputFile, line))
    {
        istringstream iss(line);
        int value;
        while (iss >> value)
        {
            Append(&head_1, value);
        }
    }

    if (getline(inputFile, line))
    {
        istringstream iss(line);
        int value;
        while (iss >> value)
        {
            Append(&head_2, value);
        }
    }

    inputFile.close();

    if (head_1 == NULL)
    {
        cout << "Первый список пуст";
        return 0;
    }

    if (head_2 == NULL)
    {
        cout << "Второй список пуст";
        return 0;
    }

    PrintDirect(head_1);
    cout << endl;
    PrintDirect(head_2);

    cout << endl << "Введите значение после которого нужно вставить числа во второй список: ";
    int x;
    cin >> x;

    Chain* res = deleteAfterX(head_1, x);

    while (res != nullptr) 
    {
        Chain* newNode = new Chain();
        newNode->data = res->data;
        newNode->next = head_2;

        head_2 = newNode;
        res = res->next;
    }

    cout << "Первый список: " << endl;
    PrintDirect(head_1);

    cout << endl << "Полученный список: " << endl;
    PrintDirect(head_2);
}