#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

const int MAX_N = 300;
const int MAX_D = 200;

vector<vector<int>> computeBracketCounts() {
    // dp[n][d] - количество последовательностей длины n с глубиной ровно d
    vector<vector<int>> dp(MAX_N + 1, vector<int>(MAX_D + 1, 0));

    // total[n][d] - количество последовательностей длины n с глубиной ≤ d
    vector<vector<int>> total(MAX_N + 1, vector<int>(MAX_D + 1, 0));

    // Базовый случай: пустая последовательность
    dp[0][0] = 1;
    for (int d = 0; d <= MAX_D; d++) {
        total[0][d] = 1;
    }

    for (int n = 2; n <= MAX_N; n += 2) {
        for (int d = 1; d <= MAX_D; d++) {
            int count = 0;

            // Все возможные разбиения (A)B
            for (int k = 0; k <= n - 2; k += 2) {
                int m = n - 2 - k;

                // Глубина достигается либо через (A), либо через B
                count += dp[k][d - 1] * (m == 0 ? 1 : total[m][d]);
                if (d > 1) {
                    count += (k == 0 ? 1 : total[k][d - 2]) * (m == 0 ? 0 : dp[m][d]);
                }
            }

            dp[n][d] = count;
            total[n][d] = total[n][d - 1] + count;
        }
    }

    return dp;
}

int main() {
    // Предварительный расчет
    auto dp = computeBracketCounts();

    string line;
    while (getline(cin, line)) {
        // Пропускаем пустые строки
        if (line.empty()) continue;

        istringstream iss(line);
        int n, d;

        // Проверяем корректность ввода
        if (!(iss >> n >> d)) {
            cout << 0 << endl;
            continue;
        }

        // Проверяем граничные условия
        if (n % 2 != 0 || n < 2 || n > MAX_N || d < 1 || d > MAX_D) {
            cout << 0 << endl;
            continue;
        }

        // Выводим результат
        cout << dp[n][d] << endl;
    }

    return 0;
}