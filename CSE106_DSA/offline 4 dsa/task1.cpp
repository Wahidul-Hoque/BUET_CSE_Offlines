#include <iostream>
#include <fstream>
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
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst)
    {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    while (in_file >> c)
    {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here
        try
        {
            if (c == 'F')
            {
                in_file >> val;
                if (bst->find(val))
                {
                    cout << "Key " << val << " found in BST.\n";
                }
                else
                    cout << "Key " << val << " not found in BST.\n";
            }
            else if (c == 'E')
            {
                if (bst->empty())
                    cout << "Empty\n";
            }
            else if (c == 'I')
            {
                in_file >> val;
                if (bst->insert(val, val))
                {
                std:
                    cout << "Key " << val << " inserted into BST, BST (Default): ";
                    bst->print('D');
                    cout << "\n";
                }
                else
                {
                    cout << "Insertion failed! Key " << val << " already exists in BST, BST (Default): ";
                    bst->print('D');
                    cout << "\n";
                }
            }
            else if (c == 'M')
            {
                in_file >> str;
                if (str[0] == 'M' && str[1] == 'i' && str[2] == 'n')
                {
                    cout << "Minimum value: " << bst->find_min() << "\n";
                }
                else if (str[0] == 'M' && str[1] == 'a' && str[2] == 'x')
                {
                    cout << "Maximum value: " << bst->find_max() << "\n";
                }
            }
            else if (c == 'D')
            {
                in_file >> val;
                if (bst->remove(val))
                {
                    cout << "Key " << val << " removed from BST, BST (Default): ";
                    bst->print('D');
                    cout << "\n";
                }
                else
                {
                    cout << "Removal failed! Key " << val << " not found in BST, BST (Default): ";
                    bst->print('D');
                    cout << "\n";
                }
            }
            else if (c == 'T')
            {
                in_file >> str;
                if (str[0] == 'I' && str[1] == 'n')
                {
                    cout << "BST (In-order): ";
                    bst->print('I');
                    cout << "\n";
                }
                else if (str[0] == 'P' && str[1] == 'r' && str[2] == 'e')
                {
                    cout << "BST (Pre-order): ";
                    bst->print('P');
                    cout << "\n";
                }
                else if (str[0] == 'P' && str[1] == 'o' && str[2] == 's' && str[3] == 't')
                {
                    cout << "BST (Post-order): ";
                    bst->print('O');
                    cout << "\n";
                }
            }
            else if (c == 'S')
            {
                cout << "Size: " << bst->size() << "\n";
            }
        }
        catch (const std::runtime_error &e)
        {
            cout << e.what() << "\n";
        }
        catch (const std::invalid_argument &e)
        {
            cout << e.what() << "\n";
        }
        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}
