#ifndef ADJACENCY_MATRIX_GRAPH_H
#define ADJACENCY_MATRIX_GRAPH_H

#include "GraphADT.h"
#include "arrayList.h"
#include "queue.h"

class AdjacencyMatrixGraph : public GraphADT
{
private:
    //TODO: Consider necessary private members as per your discretion
    int** matrix; 
    int matrixSize; 
    int capacity;
    arrayList  nodes; 
    void resizeMatrix(int newCapacity)
    {
        int** newMatrix = new int*[newCapacity];
        for (int i = 0; i < newCapacity; i++){
            newMatrix[i] = new int[newCapacity]();     
        }
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                newMatrix[i][j] = matrix[i][j];
            }
        }
        for (int i = 0; i < matrixSize; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = newMatrix;
        capacity = newCapacity;
    }


public:

    AdjacencyMatrixGraph()
    {   
        capacity = 100;
        matrixSize = 0;
        matrix = new int*[capacity];
        for (int i = 0; i < capacity; i++) {
            matrix[i] = new int[capacity](); 
        }
        init(&nodes);
    }

    ~AdjacencyMatrixGraph()
    {
        for (int i = 0; i < capacity; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        clear(&nodes);
    }

    void AddNode(int v) override
    {   
        if(is_present(v, &nodes)){
            return;
        }

        append(v, &nodes);
        if (v >= matrixSize)
        {
            matrixSize = v + 1;
            if (matrixSize > capacity)
            {
                resizeMatrix(matrixSize * 2);
            }
        }
        
        //TODO: Add a new node v and resize the matrix if your current matrix is almost going to be full.
    
    }

    void AddEdge(int u, int v) override
    {
        AddNode(u);
        AddNode(v);

        matrix[u][v] = 1; 
        matrix[v][u] = 1;
        //TODO: Add a new edge between the nodes u and v
    }

    bool CheckEdge(int u, int v) const override
    {
        if (u >= matrixSize || v >= matrixSize || u<0 || v<0)
        {
            return false;
        }
        return matrix[u][v] == 1;
        //TODO: Check whether there is an edge between two nodes u and v
    }

    void RemoveNode(int v) override
    {
        if(!is_present(v, &nodes))
        {
            return; // Node does not exist
        }
        for(int i = 0; i < matrixSize; i++)
        {
            matrix[i][v] = 0; 
            matrix[v][i] = 0; 
        }
        delete_item(v, &nodes);
        //TODO: Remove a node.
    }

    void RemoveEdge(int u, int v) override
    {
        if ( u >= matrixSize || v >= matrixSize || u<0 || v<0)
        {
            return;
        }
        matrix[u][v] = 0;
        matrix[v][u] = 0;
        //TODO: remove an edge
    }

    bool CheckPath(int u, int v) const override
    {
        //TODO: Return true if there is a path between nodes u and v. Otherwise return false
        if(!is_present(u, &nodes) || !is_present(v, &nodes) || u >= matrixSize || v >= matrixSize || u<0 || v<0)
        {
            return false;
        }
        ArrayQueue q(matrixSize);
        arrayList visited;
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
            for (int i = 0; i < matrixSize; i++)
            {
                if (matrix[current][i] == 1 && !is_present(i, &visited))
                {
                    q.enqueue(i);
                    append(i, &visited);
                }
            }
        }
        clear(&visited);
        return false;

    }

    void FindShortestPath(int u, int v) const override

    {
        if (!is_present(u, &nodes) || !is_present(v, &nodes) || u >= matrixSize || v >= matrixSize || u<0 || v<0){
            std::cout << "No path exists\n";
            return;
        }
        ArrayQueue q(matrixSize);
        arrayList visited;
        init(&visited);
        int* parent = new int[matrixSize];
        for (int i = 0; i < matrixSize; i++) {
            parent[i] = -1; 
        }
        q.enqueue(u);
        append(u, &visited);
        parent[u] = u;

        bool found = false;
        while (!q.empty() && !found)
        {
            int current = q.dequeue();
            for (int i = 0; i < matrixSize; i++)
            {
                if (matrix[current][i] == 1 && !is_present(i, &visited))
                {
                    q.enqueue(i);
                    append(i, &visited);
                    parent[i] = current; 
                    if (i == v)
                    {
                        found = true;
                        break; 
                    }
                }
            }
        }
        if(found){
            arrayList path;
            init(&path);
            int step = v;
            while (step != u && step != -1) {
                append(step, &path);
                step = parent[step];
            }
            append(u, &path);
            std::cout << "Shortest path: ";
            for (int i=path.size - 1; i >= 0; i--)
            {
                std::cout << path.array[i] << " ";
            }
            std::cout << "\n";
            clear(&path);
            


        }
        else {
            std::cout << "No path exists\n";
        }
        delete[] parent;
        clear(&visited);
        //TODO: Find the shortest path between the nodes u and v and print it.
    }

    int FindShortestPathLength(int u, int v) const override
    {
        if (!is_present(u, &nodes) || !is_present(v, &nodes) )
        {
            return -1; 
        }
        ArrayQueue q(matrixSize);
        arrayList visited;
        init(&visited);
        int* distance = new int[matrixSize];
        for (int i = 0; i < matrixSize; i++) distance[i] = INT_MAX;

        q.enqueue(u);
        append(u, &visited);
        distance[u] = 0;

        while (!q.empty())
        {
            int current = q.dequeue();
            if (current == v)
            {
                int result = distance[v];
                delete[] distance;
                clear(&visited);
                return result;
            }

            for (int i = 0; i < matrixSize; i++)
            {
                if (matrix[current][i] == 1 && !is_present(i, &visited))
                {
                    q.enqueue(i);
                    append(i, &visited);
                    distance[i] = distance[current] + 1;
                }
            }
        }

        delete[] distance;
        clear(&visited);
        return -1;
        //TODO: Return the shortest path length between nodes u and v if any such path exists. Otherwise return -1.
    }
    linkedList GetNeighbors(int u) const override
    {
        linkedList neighbors;
        init(&neighbors);
        if(!is_present(u, &nodes))
        {
            return neighbors; 
        }
        for (int i = 0; i < matrixSize; i++)
        {
            if (matrix[u][i] == 1 && is_present(i, &nodes))
            {
                append(i, &neighbors); // Add neighbor to the list
            }
        }
        return neighbors;

        //TODO return a list of neighbors of node u

    }

};

#endif // ADJACENCY_MATRIX_GRAPH_H
