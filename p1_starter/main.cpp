/*
CSE 310 Hash Function DIY Contest
Instructor: Yiran "Lawrence" Luo
Your name(s): Lev Natekin, Arya Yadav
Your team alias:
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "hash.h"
using namespace std;

int main()
{

    int k = 0; // number of slots
    int n = 0; // number of tokens/keys
    string texts[500];

    // WARNING: Start of the tokenizer that loads the input from std::cin, DO NOT change this part!
    cin >> k;
    string line;
    getline(cin, line);

    while (getline(cin, line))
    {
        texts[n] = line;
        n++;
    }
    // WARNING: End of the tokenizer, DO NOT change this part!

    HT hashTable(k);

    cout << "Table length: " << k << endl;

    for (int i = 0; i < n; i++)
    {
        int hash = hash_function(texts[i], k);

        // cout << texts[i] << ": " << slot << endl;

        hashTable.insert(hash, texts[i]);
    }

    cout << "==== Printing the contents of the first 5 slots ====" << endl;

    for (int j = 0; j < 5; j++)
    {
        SlotProperties *sp = hashTable.slotProperties(j);
        cout << "Slot " << j << ": " << sp->keys << endl;
        delete sp;
    }

    cout << "==== Printing the slot lengths ====" << endl;

    for (int j = 0; j < k; j++)
    {
        SlotProperties *sp = hashTable.slotProperties(j);
        cout << "Slot " << j << ": " << sp->length << endl;
        delete sp;
    }

    cout << "==== Printing the standard variance =====" << endl;

    cout << hashTable.standardDeviation() << endl;

    return 0;
}