#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file)
    {
        cerr << "Unable to open file\n";
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1)
    {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2)
    {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read Phil's words
        // Start your code here
        string w;
        in_file >> w;
        if (bst1->find(w))
        {
            bst1->update(w, bst1->get(w) + 1);
        }
        else
        {
            bst1->insert(w, 1);
        }
        // End your code here
    }
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read Claire's words
        // Start your code here
        string w;
        in_file >> w;
        if (bst2->find(w))
        {
            bst2->update(w, bst2->get(w) + 1);
        }
        else
        {
            bst2->insert(w, 1);
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here
    cout << "Phil's words:\nBST (In-order): ";
    bst1->print('I');
    cout << "\n\n";
    cout << "Claire's words:\nBST (In-order): ";
    bst2->print('I');
    cout << "\n";
    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true)
    {
        string word;
        in_file >> word;
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here
        if (bst1->find(word))
        {
            cout << "Phil has " << word << "!\n";
            int count = bst1->get(word) - 1;
            if (count == 0)
            {
                bst1->remove(word);
            }
            else
                bst1->update(word, count);
        }
        if (bst2->find(word))
        {
            cout << "Claire has " << word << "!\n";
            int count = bst2->get(word) - 1;
            if (count == 0)
            {
                bst2->remove(word);
            }
            else
                bst2->update(word, count);
        }
        if (bst1->empty() || bst2->empty())
        {
            if (bst1->empty() && bst2->empty())
            {
                cout << "Game is a tie!\n";
            }
            else if (bst1->empty())
            {
                cout << "Phil wins!\n";
            }
            else
            {
                cout << "Claire wins!\n";
            }
            break;
        }
        cout << "\nPhil's remaining words:\n";
        cout << "BST (In-order): ";
        bst1->print('I');
        cout << "\n\nClaire's remaining words:\n";
        cout << "BST (In-order): ";
        bst2->print('I');
        cout << "\n\n";
        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}