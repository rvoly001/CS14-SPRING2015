// CS 14 Lab
// Lab Number 2
// Name: Robinson Vo-Ly
// SID: 861166275
// Date: 4/14/2015
#include <iostream>
#include <forward_list>
#include <list>
#include "lab2.h"

using namespace std;

typedef int T;

//Checks if the number is a prime number
bool isPrime (int i)
{
    if (i <= 3) 
    {
        if (i > 1)
        {
            return true;
        }
    }
    
    if (i % 2 == 0 || i % 3 == 0) 
    {
        return false;
    }
    
    for (int j = 5; j * j <= i; j += 6) 
    {
        if (i % j == 0 || i % (j + 2) == 0) 
        {
            return false;
        }
    }
    
    return true;
}

//Recursively goes through list and counts number of primes
int primeCount (forward_list<int> lst)
{
    int count = 0;
    
    if (lst.empty()) 
    {
        return count;
    }

    forward_list<int>::iterator i = lst.begin();
    
    if (isPrime(*i))
    {
        count += 1;
    }
    
    lst.pop_front();
    
    return count + primeCount(lst);
}

//Copies list1 into list2 in reverse order with O(N) spaces left
template <typename T>
void listCopy (forward_list<T> list1, forward_list<T> &list2)
{
    typename forward_list<T>::iterator i;
    typename forward_list<T>::iterator j;
    
    forward_list<T> temp = list2;
    temp.reverse();
    list2.clear();
    
    for (i = list1.begin(); i != list1.end(); ++i)
    {
        list2.push_front(*i);
    }
    
    for (j = temp.begin(); j != temp.end(); ++j)
    {
        list2.push_front(*j);
    }
}

//Prints items in the list which are in position P;
template <typename T>
void printLots (forward_list<T> L, forward_list<int> P)
{
    typename forward_list<T>::iterator l1;
    forward_list<int>::iterator pos;
    
    for (pos = P.begin(); pos != P.end(); ++pos)
    {
        l1 = L.begin();
        for (int i = 0; i < *pos; ++i)
        {
            if (l1 == L.end() && i < *pos)
            {
                cout << "Error: Out of bounds" << endl;
                return;
            }
            else
            {
                ++l1;
            }
        }
        
        cout << *l1 << ' ';
    }
    
    cout << endl;
}

//displays elements in the forward list, basic helper function
void display (forward_list<int> list)
{
    forward_list<int>::iterator i;
    
    for (i = list.begin(); i != list.end(); ++i)
    {
        cout << *i << ' ';
    }
    cout << endl;
}

int main()
{
    cout << "-----" << endl;
    cout << "Function 1 Test (primeCount)"<< endl;
    cout << "-----" << endl;
    
    forward_list<int> test1 = {1, 3, 2, 6, 9};
    forward_list<int>::iterator i;
    
    display(test1);
    
    cout << "Number of primes: " << primeCount(test1) << endl;
    
    cout << "-----" << endl;
    cout << "Function 2 Test (listCopy)" << endl;
    cout << "-----" << endl;
    
    forward_list<int> test2 = {2, 4, 6};
    forward_list<int> copy = {14, 12, 10};
    listCopy(copy, test2);
    
    //2, 4, 6, 10, 12, 14
    display(test2);
    
    cout << "-----" << endl;
    cout << "Function 3 Test (printLots)" << endl;
    cout << "-----" << endl;
    
    forward_list<int> positions = {0, 2, 4};
    forward_list<int> positions2 = {0, 5, 10};
    forward_list<char> test3 = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    
    //Prints positions 0, 2, 4 which is a, c, e.
    printLots(test3, positions);
    
    //Prints out of bounds
    printLots(test3, positions2);
    
    cout << "-----" << endl;
    cout << "Function 4 Test (elementSwap)" << endl;
    cout << "-----" << endl;
    
    List<int> test4 = List<int>();
    test4.push_back(1);
    test4.push_back(2);
    test4.push_back(3);
    test4.push_back(4);
    test4.push_back(5);
    test4.display();
    //1, 2, 3, 4, 5
    
    test4.elementSwap(2);
    //1, 2, 4, 3, 5
    test4.display();
    
    //display error;
    test4.elementSwap(4);
    
    //should be 2, 1, 3, 5, 4
    test4.elementSwap(0);
    
    test4.display();
    
    return 0;
}