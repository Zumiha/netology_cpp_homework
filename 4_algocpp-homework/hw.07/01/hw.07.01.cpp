#include <iostream>
#include <fstream>

int** Crt2DArr(int n) {
    int** Arr = new int* [n]();
    for (int i = 0; i < n; i++) {
        Arr[i] = new int[n]();
    }
    return Arr;
}

void Del2DArr(int** Arr, int n) {
    for (int i = 0; i < n; i++) {
        delete[] Arr[i];
    }
    delete[] Arr;
}

void DFS(int** graph, bool* visited, int graph_size, int vertex) {
    std::cout << vertex + 1 << " ";
    visited[vertex] = true;
    for (int i = 0; i < graph_size; i++) {
        if ((graph[vertex][i] != 0) && (!visited[i]))
            DFS(graph, visited, graph_size, i);
    }
}

void DFS(int** graph, int graph_size) {
	std::cout << "Порядок обхода вершин: ";
	bool* visited = new bool[graph_size];

	for (int i = 0; i < graph_size; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < graph_size; i++) {
		if (!visited[i]) {
			DFS(graph, visited, graph_size, i);
		}
	}

	delete[] visited;
}

int main() {
   
    int g_size;
    std::ifstream file("input.txt");

    if (file.is_open()) {
        
        file >> g_size;
        int** deep_graph = Crt2DArr(g_size);
       
        while (!file.eof()) {
            for (int i = 0; i < g_size; i++) {
                for (int j = 0; j < g_size; j++) {
                    file >> deep_graph[i][j];
                }
            }
        }

        file.close();

        DFS(deep_graph, g_size);
        Del2DArr(deep_graph, g_size);
    }
    else {
        std::cout << "Файл не открывается!" << std::endl;
    }

    return 0;
}