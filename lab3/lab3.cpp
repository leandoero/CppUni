﻿#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Функция проверки, не бьют ли ферзи друг друга
bool isSafe(const vector<pair<int, int>>& queens) {
    // Перебираем все пары ферзей
    for (int i = 0; i < queens.size(); i++) {
        for (int j = i + 1; j < queens.size(); j++) {
            // Проверка на одной строке или столбце
            if (queens[i].first == queens[j].first ||
                queens[i].second == queens[j].second ||
                // Проверка по диагонали (разность координат по x и y одинакова)
                abs(queens[i].first - queens[j].first) == abs(queens[i].second - queens[j].second)) {
                return false; // Ферзи бьют друг друга
            }
        }
    }
    return true; // Конфликтов нет
}

// Рекурсивная функция для поиска решения
bool solve(vector<pair<int, int>>& queens,          // Текущие позиции ферзей
    vector<pair<int, int>>& initial,         // Начальные позиции
    int queen_to_move,                       // Какой ферзь должен двигаться (-1 - любой)
    int max_moves,                          // Максимальное число перемещений
    int& moves_made) {                      // Счетчик выполненных перемещений

    // Если превысили лимит перемещений - проверяем текущую расстановку
    if (moves_made >= max_moves) {
        return isSafe(queens);
    }

    // Если текущая расстановка корректна - возвращаем успех
    if (isSafe(queens)) {
        return true;
    }

    // Перебираем всех ферзей для возможного перемещения
    for (int i = 0; i < queens.size(); i++) {
        // Если указано перемещать конкретного ферзя, пропускаем остальных
        if (queen_to_move != -1 && queen_to_move != i) continue;

        // Сохраняем исходную позицию ферзя для возможного отката
        pair<int, int> original_pos = queens[i];

        // Перебираем все клетки доски
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                // Пропускаем текущую позицию ферзя
                if (row == queens[i].first && col == queens[i].second) continue;

                // Перемещаем ферзя на новую позицию
                queens[i] = { row, col };
                moves_made++; // Увеличиваем счетчик перемещений

                // Проверяем, было ли это первое перемещение для этого ферзя
                bool moved = (queens[i] != initial[i]);

                // Рекурсивно пытаемся решить с новыми параметрами:
                // Если ферзь уже двигался (moved = true), то queen_to_move = -1 (можем двигать любого)
                // Иначе продолжаем двигать этого же ферзя (queen_to_move = i)
                if (solve(queens, initial, moved ? -1 : i, max_moves, moves_made)) {
                    return true; // Решение найдено
                }

                // Откатываем изменения, если решение не найдено
                queens[i] = original_pos;
                moves_made--;
            }
        }
    }

    return false; // Решение не найдено
}

int main() {
    int k; // Количество ферзей
    cout << "Введите количество ферзей: ";
    cin >> k;

    vector<pair<int, int>> initial(k); // Начальные позиции ферзей
    cout << "Введите позиции ферзей (строка столбец для каждого):\n";
    for (int i = 0; i < k; i++) {
        cin >> initial[i].first >> initial[i].second; // Читаем позиции
    }

    // Пробуем найти решение, постепенно увеличивая максимальное число перемещений
    for (int max_moves = 1; max_moves <= 10; max_moves++) {
        vector<pair<int, int>> current = initial; // Копируем начальные позиции
        int moves_made = 0; // Счетчик перемещений

        // Пытаемся найти решение с текущим max_moves
        if (solve(current, initial, -1, max_moves, moves_made)) {
            cout << "Минимальное количество перемещений: " << moves_made << endl;
            cout << "Новая расстановка:\n";
            for (const auto& q : current) {
                cout << "(" << q.first << ", " << q.second << ") ";
            }
            cout << endl;
            return 0; // Завершаем программу после нахождения решения
        }
    }

    // Если решение не найдено после 10 попыток
    cout << "NO\n";
    return 0;
}