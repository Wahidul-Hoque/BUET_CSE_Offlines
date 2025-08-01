#ifndef LISTBST_H
#define LISTBST_H

#include "BST.hpp"
#include <iostream>
#include <stdexcept>

/**
 * Binary Search Tree implementation using linked list structure
 *
 * @tparam Key - The type of keys stored in the BST
 * @tparam Value - The type of values associated with keys
 */
template <typename Key, typename Value>
class ListBST : public BST<Key, Value>
{
private:
    /**
     * Node class for the binary search tree
     */
    class Node
    {
    public:
        Key key;
        Value value;
        Node *left;
        Node *right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node *root;
    size_t node_count;

    // TODO: Implement private helper functions as needed
    // Start your private helper functions here
    void clear_helper(Node *node)
    {
        if (node == nullptr)
            return;
        clear_helper(node->left);
        clear_helper(node->right);
        delete node;
    }
    Node *insert_helper(Node *node, Key key, Value val, bool &inserted)
    {
        if (node == nullptr)
        {
            inserted = true;
            return new Node(key, val);
        }
        if (key < node->key)
        {
            node->left = insert_helper(node->left, key, val, inserted);
        }
        else if (key > node->key)
        {
            node->right = insert_helper(node->right, key, val, inserted);
        }
        else
        {
            inserted = false;
        }
        return node;
    }
    Node *remove_helper(Node *node, Key k, bool &removed)
    {
        if (node == nullptr)
        {
            removed = false;
            return nullptr;
        }
        if (k < node->key)
        {
            node->left = remove_helper(node->left, k, removed);
        }
        else if (k > node->key)
        {
            node->right = remove_helper(node->right, k, removed);
        }
        else
        {
            removed = true;
            if (node->left == nullptr)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                Node *min_node = find_min_node(node->right);
                node->key = min_node->key;
                node->value = min_node->value;
                node->right = remove_helper(node->right, min_node->key, removed);
            }
        }
        return node;
    }
    Node *find_node(Node *node, Key key) const
    {
        if (node == nullptr)
            return nullptr;
        if (key == node->key)
            return node;
        else if (key < node->key)
            return find_node(node->left, key);
        else
            return find_node(node->right, key);
    }
    Node *find_min_node(Node *node) const
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    Node *find_max_node(Node *node) const
    {
        while (node->right != nullptr)
            node = node->right;
        return node;
    }
    void print_default_helper(Node *node, std::ostream &out) const
    {
        if (node == nullptr)
        {
            return;
        }
        out << "(" << node->key << ":" << node->value;
        if (node->left == nullptr && node->right != nullptr)
        {
            out << " ()";
            out << " ";
            print_default_helper(node->right, out);
        }
        else if (node->left != nullptr && node->right == nullptr)
        {
            out << " ";
            print_default_helper(node->left, out);
        }
        else if (node->left != nullptr && node->right != nullptr)
        {
            out << " ";
            print_default_helper(node->left, out);
            out << " ";
            print_default_helper(node->right, out);
        }

        out << ")";
    }
    void print_inorder_helper(Node *node, std::ostream &os) const
    {
        if (node == nullptr)
            return;
        print_inorder_helper(node->left, os);
        os << "(" << node->key << ":" << node->value << ") ";
        print_inorder_helper(node->right, os);
    }

    void print_preorder_helper(Node *node, std::ostream &os) const
    {
        if (node == nullptr)
            return;
        os << "(" << node->key << ":" << node->value << ") ";
        print_preorder_helper(node->left, os);
        print_preorder_helper(node->right, os);
    }

    void print_postorder_helper(Node *node, std::ostream &os) const
    {
        if (node == nullptr)
            return;
        print_postorder_helper(node->left, os);
        print_postorder_helper(node->right, os);
        os << "(" << node->key << ":" << node->value << ") ";
    }
    // End your private helper functions here

public:
    /**
     * Constructor
     */
    ListBST() : root(nullptr), node_count(0) {}

    /**
     * Destructor
     */
    ~ListBST()
    {
        // TODO: Implement destructor to free memory
        clear_helper(root);
    }

    /**
     * Insert a key-value pair into the BST
     */
    bool insert(Key key, Value value) override
    {
        // TODO: Implement insertion logic
        bool inserted = false;
        root = insert_helper(root, key, value, inserted);
        if (inserted)
            node_count++;
        return inserted;
    }

    /**
     * Remove a key-value pair from the BST
     */
    bool remove(Key key) override
    {
        // TODO: Implement removal logic
        bool removed = true;
        root = remove_helper(root, key, removed);
        if (removed)
            node_count--;
        return removed;
    }

    /**
     * Find if a key exists in the BST
     */

    bool find(Key key) const override
    {
        // TODO: Implement find logic
        Node *t = root;
        while (t)
        {
            if (key < t->key)
                t = t->left;
            else if (key > t->key)
                t = t->right;
            else
                return true;
        }
        return false;
    }

    /**
     * Find a value associated with a given key
     */
    Value get(Key key) const override
    {
        // TODO: Implement get logic
        Node *node = find_node(root, key);
        if (node == nullptr)
            throw std::runtime_error("Key not found");
        return node->value;
    }

    /**
     * Update the value associated with a given key
     */
    void update(Key key, Value value) override
    {
        // TODO: Implement update logic
        Node *node = find_node(root, key);
        if (node == nullptr)
            throw std::runtime_error("Key not found");
        node->value = value;
    }

    /**
     * Clear all elements from the BST
     */
    void clear() override
    {
        // TODO: Implement clear logic
        clear_helper(root);
        root = nullptr;
        node_count = 0;
    }

    /**
     * Get the number of keys in the BST
     */
    size_t size() const override
    {
        // TODO: Implement size logic
        return node_count;
    }

    /**
     * Check if the BST is empty
     */
    bool empty() const override
    {
        // TODO: Implement empty check logic
        return node_count == 0;
    }

    /**
     * Find the minimum key in the BST
     */
    Key find_min() const override
    {
        // TODO: Implement find_min logic
        if (root == nullptr)
            throw std::runtime_error("BST is empty");
        Node *node = find_min_node(root);
        return node->key;
    }

    /**
     * Find the maximum key in the BST
     */
    Key find_max() const override
    {
        // TODO: Implement find_max logic
        if (root == nullptr)
            throw std::runtime_error("BST is empty");
        Node *node = find_max_node(root);
        return node->key;
    }

    /**
     * Print the BST using specified traversal method
     */
    void print(char traversal_type = 'D') const override
    {
        // TODO: Implement print logic
        if (traversal_type == 'D' || traversal_type == 'd')
            print_default_helper(root, std::cout);
        else if (traversal_type == 'I' || traversal_type == 'i')
            print_inorder_helper(root, std::cout);
        else if (traversal_type == 'P' || traversal_type == 'p')
            print_preorder_helper(root, std::cout);
        else if (traversal_type == 'O' || traversal_type == 'o')
            print_postorder_helper(root, std::cout);
        else
            throw std::invalid_argument("Invalid traversal type");
    }
};

#endif // LISTBST_H