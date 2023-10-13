#include <iostream>
#include <fstream>

using namespace std;

struct Chain
{
    int data;
    Chain* next;
};

void PrintDirect(Chain* p)
{
    if (p == NULL)
    {
        return;
    }
    cout << p->data << " ";
    PrintDirect(p->next);
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

//Chain* createNewLists(Chain* p)
//{
//    Chain* current = p;
//    Chain* newNode_1 = new Chain();
//    Chain* newNode_2 = new Chain();
//
//    while (current != NULL)
//    {
//        if (current->data >= 0)
//        {
//            newNode_1->data = current->data;
//        }
//        else
//        {
//            newNode_2->data = current->data;
//        }
//        current = current->next;
//        newNode_1->next = current;
//        newNode_2->next = current;
//    }
//
//    return newNode_1, newNode_2;
//}

std::pair<Chain*, Chain*> createNewLists(Chain* p)
{
    Chain* current = p;
    Chain* C1_head = nullptr;
    Chain* C1_tail = nullptr;
    Chain* C2_head = nullptr;

    while (current != nullptr)
    {
        if (current->data >= 0)
        {
            if (C1_head == nullptr)
            {
                C1_head = new Chain{ current->data, nullptr };
                C1_tail = C1_head;
            }
            else
            {
                C1_tail->next = new Chain{ current->data, nullptr };
                C1_tail = C1_tail->next;
            }
        }
        else
        {
            C2_head = new Chain{ current->data, C2_head };
        }

        current = current->next;
    }

    return std::make_pair(C1_head, C2_head);
}

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
    cout << endl;

    pair<Chain*, Chain*> res = createNewLists(head);
    cout << "Неотрицательные: ";
    if(res.first == NULL)
        cout << "Список пуст";
    PrintDirect(res.first);
    cout << endl << "Отрицательные: ";
    if(res.second == NULL)
        cout << "Список пуст";
    PrintDirect(res.second);

    deleteList(&res.first);
    deleteList(&res.second);
}

