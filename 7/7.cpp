﻿#include <iostream>
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

void addValue(Chain*& list, int x, int z)
{
    //Chain* current = list;
    //Chain* prev = nullptr;

    //while (current != nullptr) {
    //    if (current->data == z) {
    //        // Создаем новый элемент x
    //        Chain* newNode = new Chain;
    //        newNode->data = x;

    //        if (prev == nullptr) {
    //            // Если prev равен nullptr, это означает, что мы вставляем перед первым элементом
    //            newNode->next = current;
    //            list = newNode;
    //        }
    //        else {
    //            // Вставляем newNode перед текущим элементом
    //            newNode->next = current;
    //            prev->next = newNode;
    //        }
    //    }

    //    prev = current;
    //    current = current->next;
    //}

    //// Если элемент z был первым в списке, мы не вошли в цикл, поэтому вставляем newNode в начало
    //if (prev == nullptr && list->data == z) {
    //    Chain* newNode = new Chain;
    //    newNode->data = x;
    //    newNode->next = list;
    //    list = newNode;
    //}
    Chain* current = list;
    Chain* prev = nullptr;

    while (current != nullptr) {
        if (current->data == z) {
            // Создаем новый элемент x
            Chain* newNode = new Chain;
            newNode->data = x;

            if (prev == nullptr) {
                // Если prev равен nullptr, это означает, что мы вставляем перед первым элементом
                newNode->next = current;
                list = newNode; // Обновляем указатель на начало списка
            }
            else {
                // Вставляем newNode перед текущим элементом
                newNode->next = current;
                prev->next = newNode;
            }
        }

        prev = current;
        current = current->next;
    }
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

    addValue(head, 5, 2);

    PrintDirect(head);

    deleteList(&head);
}
