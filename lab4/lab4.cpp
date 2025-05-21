
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//https://www.youtube.com/watch?v=AflQ-zFa2qM
//https://proglib.io/p/10-algoritmov-dlya-raboty-s-grafami-kotorye-dolzhen-znat-kazhdyy-koder-2022-06-17

void bfs(int start, vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int u : graph[v]) {
            if (!visited[u]) {
                visited[u] = true;
                q.push(u);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    vector<bool> visited(n, false); 
    int components = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            components++;
            bfs(i, graph, visited);
        }
    }
    cout << components - 1 << endl;
    return 0;
}
