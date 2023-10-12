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

Chain* sumList(Chain* List_1, Chain* List_2)
{
    Chain* current_1 = List_1;
    Chain* current_2 = List_2;
    Chain* res = NULL;
    Chain* tail = NULL;

    while (current_1 != NULL || current_2 != NULL)
    {
        int value1 = (current_1 != NULL) ? current_1->data : 0;
        int value2 = (current_2 != NULL) ? current_2->data : 0;
        int sum = value1 + value2;

        Chain* newNode = new Chain{ sum, NULL };

        if (res == NULL)
        {
            res = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }

        if (current_1 != NULL)
        {
            current_1 = current_1->next;
        }

        if (current_2 != NULL)
        {
            current_2 = current_2->next;
        }
    }

    return res;
}

int main()
{
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

    Chain* res = sumList(head_1, head_2);
    cout << endl;
    PrintDirect(res);
}

