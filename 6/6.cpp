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

Chain* del0(Chain* first, int x)
{
    Chain* temp = nullptr;
    Chain* current = first;
    Chain* before = first;
    bool b = false;

    while ((current != nullptr) && !b) 
    {
        if (current->data == 0) 
        {
            b = true;  // Нашли первый ноль, завершаем цикл
        }
        else if (current->data == x) 
        {
            if (temp == nullptr) 
            {
                // Если temp равен nullptr, это значит, что найденное число x первый раз
                // Поэтому мы устанавливаем temp на текущий элемент и удаляем его из списка
                temp = current;
                current = current->next;
                
                if (before == temp) 
                {
                    // Если удаляемый элемент был первым в списке, обновляем указатель на первый элемент
                    first = current;
                }
                else 
                {
                    before->next = current;
                }
                delete temp;
            }
            else 
            {
                // Если temp не nullptr, это значит, что мы уже удалили один элемент с числом x,
                // поэтому удаляем текущий элемент, не меняя temp
                temp = current;
                current = current->next;
                delete temp;
                if (before == temp) 
                {
                    first = current;
                }
                else 
                {
                    before->next = current;
                }
            }
        }
        else 
        {

            // Продолжаем поиск
            before = current;
            current = current->next;
        }
    }

    return first;
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

    if (head == NULL)
    {
        cout << "Список пуст";
        return 0;
    }

    PrintDirect(head);

    cout << endl << "Введите удаляемое значение: ";
    int x;
    cin >> x;

    Chain* res = del0(head, x);

    if (res == NULL)
    {
        cout << "Список пуст";
        return 0;
    }

    PrintDirect(res);

    deleteList(&res);
}