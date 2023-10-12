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

    // Удаление первого элемента с данными x без оператора delete
    if (first != nullptr && first->data == x)
    {
        Chain* temp = first;
        first = first->next;
        delete temp; // Этот оператор delete используется здесь
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

    Chain* head = NULL;

    ifstream inputFile("input.txt");
    int value;

    while (inputFile >> value)
    {
        Append(&head, value);
    }

    Chain* res = deleteAfterX(head, 2);

    PrintReverseDirect(res);

    deleteList(&head);
    deleteList(&res);
}

