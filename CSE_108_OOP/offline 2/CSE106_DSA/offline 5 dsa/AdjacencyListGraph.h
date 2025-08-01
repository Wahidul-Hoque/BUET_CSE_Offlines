#ifndef ADJACENCY_LIST_GRAPH_H
#define ADJACENCY_LIST_GRAPH_H

#include "GraphADT.h"
#include "queue.h"

class AdjacencyListGraph : public GraphADT
{
private:
    // TODO: Take necessary private members
    linkedList **adjList;
    int listSize;
    int capacity;
    linkedList nodes;
    void resizeList(int newCapacity)
    {
        linkedList **newList = new linkedList *[newCapacity];
        for (int i = 0; i < newCapacity; i++)
        {
            newList[i] = new linkedList;
            init(newList[i]);
        }
        for (int i = 0; i < listSize; i++)
        {
            *newList[i] = *adjList[i];
        }
        for (int i = 0; i < listSize; i++)
        {
            free_list(adjList[i]);
            delete &adjList[i];
        }
        delete[] adjList;
        adjList = newList;
        capacity = newCapacity;
    }

public:
    AdjacencyListGraph()
    {
        capacity = 100;
        listSize = 0;
        adjList = new linkedList *[capacity];
        for (int i = 0; i < capacity; i++)
        {
            adjList[i] = new linkedList;
            init(adjList[i]);
        }
        init(&nodes);
    }
    ~AdjacencyListGraph()
    {
        for (int i = 0; i < capacity; i++)
        {
            free_list(adjList[i]);
            delete adjList[i];
        }
        delete[] adjList;
        free_list(&nodes);
    }

    void AddNode(int v) override
    {
        if (is_present(v, &nodes))
        {
            return;
        }
        if (v >= listSize)
        {
            if (v >= capacity)
            {
                resizeList(v * 2);
            }
            for (int i = listSize; i <= v; i++)
            {
                init(adjList[i]);
            }
            listSize = v + 1;
        }
        append(v, &nodes);
        // TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
    }

    void AddEdge(int u, int v) override
    {
        AddNode(u);
        AddNode(v);
        if (!is_present(v, adjList[u]))
        {
            append(v, adjList[u]);
            append(u, adjList[v]);
        }
        // TODO: Add a new edge between the nodes u and v
    }

    bool CheckEdge(int u, int v) const override
    {
        if (u >= listSize || v >= listSize || !is_present(u, &nodes) || !is_present(v, &nodes))
        {
            return false;
        }
        return is_present(v, adjList[u]);
        // TODO: Check whether there is an edge between two nodes u and v
    }

    void RemoveNode(int v) override
    {
        if (!is_present(v, &nodes))
        {
            return;
        }
        clear(adjList[v]);
        for (int i = 0; i < listSize; i++)
        {
            if (is_present(v, adjList[i]))
            {
                delete_item(v, adjList[i]);
            }
        }
        // TODO: Remove a node.
        delete_item(v, &nodes);
    }

    void RemoveEdge(int u, int v) override
    {
        if (u >= listSize || v >= listSize || !is_present(u, &nodes) || !is_present(v, &nodes))
        {
            return;
        }
        if (is_present(v, adjList[u]))
        {
            delete_item(v, adjList[u]);
            delete_item(u, adjList[v]);
        }
        // TODO: remove an edge
    }

    bool CheckPath(int u, int v) const override
    {
        if (!is_present(u, &nodes) || !is_present(v, &nodes) || u >= listSize || v >= listSize)
        {
            return false;
        }
        ArrayQueue q(listSize);
        linkedList visited;
        init(&visited);

        q.enqueue(u);
        append(u, &visited);
        while (!q.empty())
        {
            int current = q.dequeue();
            if (current == v)
            {
                clear(&visited);
                return true;
            }
            for (node *temp = adjList[current]->head; temp != nullptr; temp = temp->next)
            {
                if (!is_present(temp->element, &visited))
                {
                    q.enqueue(temp->element);
                    append(temp->element, &visited);
                }
            }
        }
        clear(&visited);
        return false;
        // TODO: Return true if there is a path between nodes u and v. Otherwise return false
    }

    void FindShortestPath(int u, int v) const override
    {
        if (!is_present(u, &nodes) || !is_present(v, &nodes) || u >= listSize || v >= listSize)
        {
            std::cout << "No path exists\n";
            return;
        }
        ArrayQueue q(listSize);
        linkedList visited;
        init(&visited);
        int *parent = new int[listSize];
        for (int i = 0; i < listSize; i++)
            parent[i] = -1;
        q.enqueue(u);
        append(u, &visited);
        parent[u] = u;
        bool found = false;
        while (!q.empty() && !found)
        {
            int current = q.dequeue();
            for (node *temp = adjList[current]->head; temp != nullptr; temp = temp->next)
            {
                if (!is_present(temp->element, &visited))
                {
                    q.enqueue(temp->element);
                    append(temp->element, &visited);
                    parent[temp->element] = current;
                    if (temp->element == v)
                    {
                        found = true;
                        break;
                    }
                }
            }
        }

        if (found)
        {
            linkedList path;
            init(&path);
            int current = v;
            while (current != u)
            {
                append(current, &path);
                current = parent[current];
            }
            append(u, &path);
            std::cout << "Shortest path: ";
            for (node *temp = path.tail; temp != nullptr; temp = temp->prev)
            {
                std::cout << temp->element << " ";
            }
            std::cout << "\n";
            free_list(&path);
        }
        else
        {
            std::cout << "No path exists\n";

            delete[] parent;
            clear(&visited);
        }

        // TODO: Find the shortest path between the nodes u and v and print it.
    }

    int FindShortestPathLength(int u, int v) const override
    {
        if (!is_present(u, &nodes) || !is_present(v, &nodes) || u >= listSize || v >= listSize)
        {
            return -1;
        }

        ArrayQueue q(listSize);
        linkedList visited;
        init(&visited);
        int *distance = new int[listSize];
        for (int i = 0; i < listSize; i++)
            distance[i] = -1;
        q.enqueue(u);
        append(u, &visited);
        distance[u] = 0;
        while (!q.empty())
        {
            int current = q.dequeue();
            if (current == v)
            {
                clear(&visited);
                int result = distance[current];
                delete[] distance;
                return result;
            }

            for (node *temp = adjList[current]->head; temp != nullptr; temp = temp->next)
            {
                if (!is_present(temp->element, &visited))
                {
                    q.enqueue(temp->element);
                    append(temp->element, &visited);
                    distance[temp->element] = distance[current] + 1;
                }
            }
            
        }
        delete[] distance;
        clear(&visited);
        return -1;

        // TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
    }

    linkedList GetNeighbors(int u) const override
    {
        linkedList neighbors;
        init(&neighbors);
        if (!is_present(u, &nodes) || u >= listSize)
        {
            return neighbors;
        }
        for (node *temp = adjList[u]->head; temp != nullptr; temp = temp->next)
        {
            append(temp->element, &neighbors);
        }
        return neighbors;
        // TODO: Return the list of neighbors.
    }
};

#endif // ADJACENCY_LIST_GRAPH_H
