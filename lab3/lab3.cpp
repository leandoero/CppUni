#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool isSafe(const vector<pair<int, int>>& queens) {
    for (int i = 0; i < queens.size(); i++) {
        for (int j = i + 1; j < queens.size(); j++) {
            if (queens[i].first == queens[j].first || queens[i].second == queens[j].second ||
                abs(queens[i].first - queens[j].first) == abs(queens[i].second - queens[j].second)) {
                return false;
            }
        }
    }
    return true;
}


//queens текущая расстановка которую я буду изменять
//initial изначальная расстановка
//queen_to_move индекс ферзя которого мы перемещаем 
//max_moves максимальное допустимое количество перемещений
//moves_made счетчик выполненных перемещений

bool task(vector<pair<int, int>>& queens,vector<pair<int, int>>& initial,int queen_to_move,int max_moves,int& moves_made) {                      

    if (moves_made >= max_moves) {
        return isSafe(queens);
    }   

    if (isSafe(queens)) {
        return true;
    }

    for (int i = 0; i < queens.size(); i++) {
        if (queen_to_move != -1 && queen_to_move != i) {
            continue;
        }

        pair<int, int> original_pos = queens[i];

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                if (row == queens[i].first && col == queens[i].second) {
                    continue;
                }
                queens[i] = { row, col };
                moves_made++;

                bool moved = (queens[i] != initial[i]);

                if (task(queens, initial, moved ? -1 : i, max_moves, moves_made)) {
                    return true;
                }              
                queens[i] = original_pos;
                moves_made--;
            }
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "ru");
    int k; 
    cout << "введите количество ферзей : ";
    cin >> k;

    vector<pair<int, int>> initial(k);
    cout << "введите строку и столбец ферзей : \n";
    for (int i = 0; i < k; i++) {
        cin >> initial[i].first >> initial[i].second;
    }

    for (int max_moves = 1; max_moves <= 10; max_moves++) {
        vector<pair<int, int>> current = initial;
        int moves_made = 0;
        if (task(current, initial, -1, max_moves, moves_made)) {
            cout << "минимальное количество перемещений: " << moves_made << endl;
            cout << "новая расстановка:\n";
            for (const auto& q : current) {
                cout << "(" << q.first << ", " << q.second << ") ";
            }
            cout << endl;
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}