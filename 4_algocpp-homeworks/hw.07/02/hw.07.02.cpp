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

void DisplayGraph(int** arr, int n) {
    std::cout << "Матрица смежности графа: " << std::endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) std::cout << arr[i][j] << " ";
        std::cout << std::endl;
    }
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
	
	bool* visited = new bool[graph_size];
	for (int i = 0; i < graph_size; i++) {
		visited[i] = false;
	}

    std::cout << "Порядок обхода вершин: ";
	for (int i = 0; i < graph_size; i++) {
		if (!visited[i]) {
			DFS(graph, visited, graph_size, i);
		}
	}

	delete[] visited;
}

void WFS(int** graph, int graph_size, int start_vertex) {
	
    bool* visited = new bool[graph_size];
	for (int i = 0; i < graph_size; i++) {
		visited[i] = false;
	}

	int* queue = new int[graph_size];
	int head = 0, tail = -1;

    visited[start_vertex] = true;
    queue[++tail] = start_vertex;
		
	std::cout << "Порядок обхода вершин: ";
	while (head <= tail) {
		int vertex = queue[head++];
		std::cout << vertex + 1 << " ";

		for (int i = 0; i < graph_size; i++) {
			if (graph[vertex][i] && !visited[i]) {
				queue[++tail] = i;
                visited[i] = true;				
			}
		}
	}

	delete[] visited;
	delete[] queue;
}

int main() {
   
    int g_size;
    std::ifstream file("input.txt");

    if (file.is_open()) {
        
        file >> g_size;
        int** wide_graph = Crt2DArr(g_size);
       
        while (!file.eof()) {
            for (int i = 0; i < g_size; i++) {
                for (int j = 0; j < g_size; j++) {
                    file >> wide_graph[i][j];
                }
            }
        }

        file.close();

        int start_vertex = 0;
        while (true) {
        std::cout << "В графе " << g_size << " вершин. Введите номер вершины, с которой начнётся обход: ";
            std::cin >> start_vertex;
            if ((start_vertex < 1) || (start_vertex > g_size)) {
                std::cout << "Такой вершины в графе нет." << std::endl;
            }
            else {
                start_vertex -= 1;
                break;
            }
        }

        WFS(wide_graph, g_size, start_vertex);
        Del2DArr(wide_graph, g_size);
    }
    else {
        std::cout << "Файл не открывается!" << std::endl;
    }

    return 0;
}