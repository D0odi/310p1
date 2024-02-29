#include <iostream>
#include <string>
#include "hash.h"
using namespace std;

Node::Node(std::string key, Node *next) : key(key), next(next) {}
SlotProperties::SlotProperties(int slot, int length, string keys) : slot(slot), length(length), keys(keys) {}

HT::HT(int numSlots) : numSlots(numSlots), slots(new Node *[numSlots])
{
    for (int i = 0; i < numSlots; i++)
    {
        slots[i] = NULL;
    }
}

void HT::insert(int slot, string key)
{
    Node *head = this->slots[slot];
    if (head == NULL)
    {
        Node *insertNode = new Node(key, NULL);
        head = insertNode;
        this->slots[slot] = head;
    }
    else
    {
        Node *current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        Node *newNode = new Node(key, NULL);
        current->next = newNode;
    }
}

SlotProperties *HT::slotProperties(int slot)
{
    Node *current = this->slots[slot];
    string result;
    int length = 0;

    while (current != NULL)
    {
        result += current->key + " ";
        length++;
        current = current->next;
    }
    return new SlotProperties(slot, length, result);
}

double HT::standardDeviation()
{
    int sum = 0;
    int m = 0;
    for (int i = 0; i < this->numSlots; i++)
    {
        SlotProperties *sp = this->slotProperties(i);
        sum += sp->length;
        m++;
        delete sp;
    }
    double mean = sum / m;
    double variance = 0;
    for (int i = 0; i < this->numSlots; i++)
    {
        SlotProperties *sp = this->slotProperties(i);
        variance += pow(sp->length - mean, 2);
        delete sp;
    }
    variance /= m;
    return sqrt(variance);
}

int hash_function(string text, int tableLength)
{
    unsigned long long hash = 0;
    int length = text.length();
    for (int i = 0; i < length; i++)
    {
        hash = text[i] + (hash << 6) + (hash << 16) - hash;
    }

    return (int)(hash % tableLength);
}

// make &&  ./encoder < inputs/mit_a.txt
//          ./encoder < inputs/sample_input.txt
//          ./encoder < inputs/common500.txt

// hash += text[i] * (i) % tableLength;
//      sample_input:   1.26491;
//      mit_a:          2.19545
//      common500:      3.07246
// hash += text[i];
//      sample_input:   1.09545;
//      mit_a:          2.76767
//      common500:      3.07246
// hash = (hash * 31 + text[i]) % tableLength;
//      sample_input:   1.09545;
//      mit_a:          2.55343;
//      common500:      2.87054;
// hash = (hash * 2 + text[i]);
// hash % tablelength;
//      sample_input:   1.54919;
//      mit_a:          2.33238;
//      common500:      3.09839;
// hash = (hash * 31) + text[i];
// (int)(hash % tableLength);
//      sample_input:   1.09545;
//      mit_a:          2.51794
//      common500:      2.86356;
// hash = 101
// hash = (hash * 31) + text[i]; ------------best
// (int)(hash % tableLength);
//      sample_input:   1.09545;
//      mit_a:          2.22261;
//      common500:      2.89828;

// unsigned long long hash = 1;
// int prime = 0;
// if (tableLength == 5)
// {
//     prime = 7;
// }
// else if (tableLength == 25)
// {
//     prime = 29;
// }
// else if (tableLength == 50)
// {
//     prime = 53;
// }
// else if (tableLength == 100)
// {
//     prime = 97;
// }
// int length = text.length();
// for (int i = 0; i < length; i++)
// {
//     hash = text[i] + hash * prime;
// }

// return (int)(hash % tableLength);