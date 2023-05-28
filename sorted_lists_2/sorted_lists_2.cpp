#include <fstream>
#include <iostream>

using namespace std;

struct elem
{
    int info;
    elem* next;
};
typedef elem* set;

void show_set(set top)
{
    top = top->next;
    while (top != NULL)
    {
        cout << top->info << ' ';
        top = top->next;
    }
    cout << endl;
}

set create()
{
    set top = new elem;
    top->info = -1;
    top->next = NULL;
    return top;
}

bool is_empt(set top)
{
    return top->next == NULL && top->info == -1;
}

void add(set &top, int x)
{
    set p = top;
    set q;
    bool is_added = false;
    while (p->next != NULL && !is_added)
    {
        if (x <= p->next->info)
        {
            q = p->next;
            p->next = new elem;
            p->next->info = x;
            p->next->next = q;
            p = q;
            is_added = true;
        }
        else
        {
            p = p->next;
        }
    }
    if (!is_added)
    {
        p->next = new elem;
        p->next->info = x;
        p->next->next = NULL;
    }
}

void insertion_sort(set &top)
{
    set p = top;
    top = new elem;
    top->next = p;
    set q;
    set r;

    p = p->next;
    while (p->next)
    {
        if (p->info <= p->next->info)
        {
            p = p->next;
            continue;
        }
        q = p->next;
        p->next = p->next->next;
        r = top;
        while(q->info > r->next->info)
        {
            r = r->next;
        }
        q->next = r->next;
        r->next = q;
    }
    p = top;
    top = top->next;
    delete p;
}

void del(set &top, int x)
{
    set p = top;
    set q;
    bool is_empty = is_empt(top);
    if (is_empty) cout << "Empty set" << endl;

    while (p->next != NULL && p->next->next != NULL)
    {
        if (p->next->info == x)
        {
            q = p->next;
            p->next = p->next->next;
            delete q;
        }
        else
        {
            p = p->next;
        }
        
    }
    if (p->next != NULL && p->next->next == NULL && p->next->info == x)
    {
        q = p->next;
        p->next = NULL;
        delete q;
    }

}

bool is_equal(set top1, set top2)
{
    bool is_eq = true;
    set p1 = top1;
    set p2 = top2;

    while (p1->next != NULL && p2->next != NULL && is_eq)
    {
        if (p1->next->info != p2->next->info)
        {
            is_eq = false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    
    if (p1->next != NULL || p2->next != NULL) is_eq = false;

    return is_eq;
}

set merge(set top1, set top2)
{
    set top3 = create();
    set p3 = top3;
    set p1 = top1;
    set p2 = top2;

    while (p1->next != NULL && p2->next != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        if (p1->next->info <= p2->next->info)
        {
            p3->info = p1->next->info;
            p1 = p1->next;
        }
        else
        {
            p3->info = p2->next->info;
            p2 = p2->next;
        }
    }
    while (p2->next != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        p3->info = p2->next->info;
        p2 = p2->next;
    }
    while (p1->next != NULL)
    {
        p3->next = new elem;
        p3 = p3->next;
        p3->info = p1->next->info;
        p1 = p1->next;
    }

    p3->next = NULL;
    return top3;
}

set intersection(set top1, set top2)
{
    set top3 = create();
    set p3 = top3;
    set p1 = top1;
    set p2 = top2;

    while (p1->next != NULL && p2->next != NULL)
    {
        if (p1->next->info < p2->next->info)
        {
            p1 = p1->next;
        }
        else if (p2->next->info < p1->next->info)
        {
            p2 = p2->next;
        }
        else
        {
            p3->next = new elem;
            p3 = p3->next;
            p3->info = p1->next->info;
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    p3->next = NULL;
    return top3;
}

void delete_set(set top)
{
    set p = top;
    set q;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        delete q;
    }
}

set prime_numbers(int n)
{
    set top = create();
    for (int i = 1; i <= n; i++) add(top, i);
    set q;
    for (int k = 2; k <= n; k++)
    {
        set p = top;
        while (p->next != NULL)
        {
            if (p->next->info != k && p->next->info % k == 0) p->next->info = -2;
            p = p->next;
        }
    }
    del(top, -2);
    return top;
}

int main()
{

    //insertion_sort(top);
    //show_set(top);

    //set top = create();
    //show_set(top);
    //cout << is_empt(top) << endl;

    //for (int i = 0; i < 10; i++) add(top, i);
    //add(top, 3);
    //show_set(top);

    //for (int i = 1; i < 10; i++) del(top, i);
    //show_set(top);

    //set top1 = create();
    //for (int i = 5; i < 15; i++) add(top1, i);
    //show_set(top1);

    //set top3 = merge(top, top1);
    //show_set(top3);

    //cout << is_equal(top, top1) << endl;

    //set top3 = intersection(top, top1);
    //show_set(top3);

    int* n = new int;
    cout << "Input n: " << endl;
    cin >> *n;
    set primes = prime_numbers(*n);
    show_set(primes);

}


