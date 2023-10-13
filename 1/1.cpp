#include <iostream>
#include <sstream>

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

Chain* ins_sorted_rec(Chain* first, int k)
{
    if (first == NULL || k < first->data)
    {
        Chain* temp = new Chain();
        temp->data = k;
        temp->next = first;
        return temp;
    }
    else
    {
        first->next = ins_sorted_rec(first->next, k);
        return first;
    }
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
    int x;
    string line;
    cout << "Введите числа: ";
    /*cin >> x;
    first = ins_sorted_unrec(first, x);
    first1 = ins_sorted_rec(first1, x);
    while (cin.get() != '\n')
    {
        cin >> x;
        first = ins_sorted_unrec(first, x);
        first1 = ins_sorted_rec(first1, x);
    }*/
    getline(cin, line);
    istringstream iss(line);
    
   
    while (iss >> x)
    {
        first = ins_sorted_unrec(first, x);
        first1 = ins_sorted_rec(first1, x);
    }

    
    Chain* p = first;
    Chain* p1 = first1;

    if (p == NULL && p1 == NULL)
    {
        cout << "Список пуст";
            return 0;
    }
        

    cout << "Список, упорядоченный по неубыванию значений элементов рекурсивно: " << endl;

    PrintDirect(p);
    cout << endl << "Список, упорядоченный по неубыванию значений элементов нерекурсивно: " << endl;
    PrintDirect(p1);

    deleteList(&p);
    deleteList(&p1);
}
