#include <iostream>

using namespace std;

struct Chain
{
    int data;
    Chain* next;
};

// список, упорядоченный по неубыванию значений элементов
Chain* ins_sorted_unrec(Chain* first, int k)
{
    Chain* before, * after, * temp;
    temp = new Chain();
    temp->data = k;
    temp->next = NULL;
    if (first == NULL)
    {
        first = temp;
    }
    else if (k < first->data)
    {
        temp->next = first;
        first = temp;
    }
    else
    {
        before = first;
        after = first;
        while ((after != NULL) && (after->data <= k))
        {
            before = after;
            after = after->next;
        }
        temp->next = after;
        before->next = temp;
    }
    return first;
}

Chain* Union(Chain* list1, Chain* list2)
{
    Chain* mergedList = NULL;
    Chain* temp = NULL;

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->data <= list2->data)
        {
            if (mergedList == NULL)
            {
                mergedList = temp = new Chain{ list1->data, NULL };
            }
            else
            {
                temp->next = new Chain{ list1->data, NULL };
                temp = temp->next;
            }
            list1 = list1->next;
        }
        else
        {
            if (mergedList == NULL)
            {
                mergedList = temp = new Chain{ list2->data, NULL };
            }
            else
            {
                temp->next = new Chain{ list2->data, NULL };
                temp = temp->next;
            }
            list2 = list2->next;
        }
    }

    if (list1 != NULL)
    {
        if (mergedList == NULL)
        {
            mergedList = list1;
        }
        else
        {
            temp->next = list1;
        }
    }
    else if (list2 != NULL)
    {
        if (mergedList == NULL)
        {
            mergedList = list2;
        }
        else
        {
            temp->next = list2;
        }
    }

    return mergedList;
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

int main()
{
    setlocale(LC_ALL, "Russian");

    Chain* first = NULL;
    Chain* first1 = NULL;
    //char c,d;
    int x, x1;
    cout << "Введите числа первого списка: ";
    cin >> x;
    first = ins_sorted_unrec(first, x);
    while (cin.get() != '\n')
    {
        cin >> x;
        first = ins_sorted_unrec(first, x);
        
    }
    cout << endl << "Введите числа второго списка: ";
    cin >> x1;
    first1 = ins_sorted_unrec(first1, x1);
    while (cin.get() != '\n')
    {
        cin >> x1;
        first1 = ins_sorted_unrec(first1, x1);
    }

    Chain* p = first;
    Chain* p1 = first1;
    cout << endl << "Первый упорядоченный список: " << endl;
    PrintDirect(p);

    cout << endl << "Второй упорядоченный список: " << endl;
    PrintDirect(p1);
    Chain* res = Union(p, p1);

    cout << endl << "Объединенный список: " << endl;
    PrintDirect(res);
    
    
    deleteList(&p);
    deleteList(&p1);
    //deleteList(&res);
}