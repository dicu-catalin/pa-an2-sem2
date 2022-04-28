#include <bits/stdc++.h>
using namespace std;

#define INF ((long int)1e17)

class Task {
 public:
	int n;
	vector<pair<int, int>> mountains;

	void read_input() {
		ifstream fin("ridge.in");
		fin >> n;
		for (int i = 0; i < n; i++) {
			int height, cost;
			fin >> height >> cost;
			mountains.push_back(make_pair(height, cost));
		}
		fin.close();
	}

	void solve() {
		/* dimensiunea este data de faptul ca dintr-un munte nu este necesar 
		sa se scada de mai mult de 2 ori, deoarece ar fi irelevant */
		vector<vector<long int>> dp(n, vector<long int>(3, INF));
		// cazurile de baza

		dp[0][2] = 2 * mountains[0].first;
		dp[0][1] = mountains[0].second;
		dp[0][0] = 0;

		for (int i = 1; i < n; i++)
			for (int j = 0; j < 3; j++) {
				// daca muntele a ajuns la nivelul minim, se trece la urmatorul
				if(mountains[i].first < j)
					break;
				/* daca muntele este diferit de muntele anterior, dupa ce au
				fost scazute j nivele, se calculeaza costul */
				if(mountains[i-1].first != mountains[i].first - j)
					dp[i][j] = j * mountains[i].second + dp[i-1][0];
				if(mountains[i-1].first - 1 >= 0 &&
							mountains[i-1].first - 1 != mountains[i].first - j)
					dp[i][j] = min(dp[i][j], j*mountains[i].second + dp[i-1][1]);
				if(mountains[i-1].first - 2 >= 0 &&
							mountains[i-1].first - 2 != mountains[i].first - j)
					dp[i][j] = min(dp[i][j], j*mountains[i].second + dp[i-1][2]);
			}
		ofstream fout("ridge.out");
		fout << min(min(dp[n-1][0], dp[n-1][1]), dp[n-1][2]);
		fout.close();
	}
};

int main() {
    Task* ridge = new Task();
    if (!ridge) {
        std::cerr << "Obiectul nu a fost creat!\n";
        return -1;
    }
    ridge->read_input();
    ridge->solve();
    delete ridge;
    return 0;
}
