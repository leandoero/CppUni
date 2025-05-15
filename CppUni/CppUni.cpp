﻿#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//https://codeforces.com/group/PZJYXH0KrS/contest/581398
//https://habr.com/ru/articles/661577/
//https://www.youtube.com/watch?v=4iDv8Zu8L3I
//https://www.youtube.com/watch?v=3-XLRh2M5YI&list=PLGhUJWLZ8uQ69hYB-AtVCerJ5yqh_5awR&index=3


void bfs(vector<vector<int>>& adj, vector<bool>& used, int start) {
	queue<int>q;
	q.push(start);
	used[start] = true;

	while (q.size() > 0) {
		int cur = q.front();
		q.pop();

		for (int i = 0; i < adj[cur].size(); ++i) {
			int next = adj[cur][i];
			if (used[next] == false) {
				used[next] = true;
				q.push(next);
			}
		}
	}
}


int main() {

	//1. матрица смежности

	int n, m;
	cin >> n >> m;

	vector<vector<int>> matrix(n, vector<int>(n));

	//2. список смежности
	int n, m;
	cin >> n >> m;
	vector<pair<int, int>>edge(m);
	for (auto& a : edge) {
		cin >> a.first >> a.second;
	}

	//3. список смежности
	int n, m;
	cin >> n >> m;
	vector<vector<int>> adj(n);

	for (int i = 0; i < m; i++)
	{
		int u, v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

}