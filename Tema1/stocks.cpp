#include <bits/stdc++.h>
using namespace std;

class Stock {
 public:
    int currValue;
    int minValue;
    int maxValue;

    Stock(int _currValue, int _minValue, int _maxValue)
    : currValue(_currValue)
    , minValue(_minValue)
    , maxValue(_maxValue) { }
};

class Task {
 public:
    int n, b, l;
    vector<Stock> stocks;

    void read_input() {
        ifstream fin("stocks.in");
        fin >> n >> b >> l;
        for (int i = 0; i < n; i++) {
            int currValue, minValue, maxValue;
            fin >> currValue >> minValue >> maxValue;
            stocks.push_back(Stock(currValue, minValue, maxValue));
        }
        fin.close();
    }

    void solve() {
        vector<vector<vector<int>>> dp(n+1,
            vector<vector<int>>(l+1, vector<int>(b+1, 0)));
        /*se calculeaza cele mai profitabile actiuni in functie de bani(b) si 
            limita de pierdere(l), folosindu-se maxim i obiecte din vector*/
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= l; j++) {
                for (int k = 0; k <= b; k++) {
                    int lose = stocks[i-1].currValue - stocks[i-1].minValue;
                    int profit = stocks[i-1].maxValue - stocks[i-1].currValue;
                    /* daca obiectul nu depaseste banii ramasi si limita
                    de pierdere, se cauta o solutie mai buna */
                    if (k >= stocks[i-1].currValue && j >= lose)
                        dp[i][j][k] = profit +
                                    dp[i-1][j-lose][k-stocks[i-1].currValue];
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k]);
                }
            }
        }
        ofstream fout("stocks.out");
        fout << dp[n][l][b];
        fout.close();
    }
};

int main() {
    Task* stocks = new Task();
    if (!stocks) {
        std::cerr << "Obiectul nu a fost creat.\n";
        return -1;
    }
    stocks->read_input();
    stocks->solve();
    delete stocks;
    return 0;
}
