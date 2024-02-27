#include <iostream>
#include <string>
#include <cmath>
// You are free to use additional libraries as long as it's not PROHIBITED per instruction.

using namespace std;

class Node
{
public:
    string key;
    Node *next;
    Node(string key, Node *next);
};

struct SlotProperties
{
    int slot;
    int length;
    string keys;
    SlotProperties(int slot, int length, string keys);
};

class HT
{
private:
    int numSlots;
    Node **slots;

public:
    HT(int numSlots);
    void insert(int slot, string key);
    SlotProperties *slotProperties(int slot);
    double standardDeviation();
};

int hash_function(string text, int tableLength);
