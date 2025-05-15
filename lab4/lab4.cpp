
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//https://www.youtube.com/watch?v=AflQ-zFa2qM

// Функция BFS для поиска одной компоненты связности
void bfs(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        // Обходим всех соседей текущей вершины
        for (int u : graph[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}

int main() {
    int n, m; // Количество городов и дорог
    cin >> n >> m;

    // Создаём граф
    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--; // Приводим к индексам от 0
        graph[a].push_back(b);
        graph[b].push_back(a); // Дороги двусторонние
    }

    vector<bool> visited(n, false); // Массив посещённых вершин
    int components = 0; // Количество компонент связности

    // Находим все компоненты связности
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++;
            bfs(i, graph, visited);
        }
    }

    // Для соединения всех компонент нужно построить components - 1 дорог
    cout << components - 1 << endl;

    return 0;
}
