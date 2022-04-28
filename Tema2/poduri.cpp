#include <bits/stdc++.h>
using namespace std;

class Poduri {
	public:
		int n, m, x, y;
		// matricea de poduri
		vector<vector<int>> grid;

		void read_input() {
			ifstream fin("poduri.in");
			fin >> n >> m >> x >> y;
			x--;
			y--;
			for (int i = 0; i < n; i++) {
				grid.push_back(vector<int> (m , 0));
				for (int j = 0; j < m; ++j) {
					char bridge;
					fin >> bridge;
					if (bridge == 'V')
						grid[i][j] = 1;
					else if (bridge == '.')
						grid[i][j] = -1;
					else if (bridge == 'D')
						grid[i][j] = 2;
				}
			}
			fin.close();
		}

		// verifica daca s-a iesit din matrice(daca s-a ajuns pe uscat)
		bool check(int x, int y) {
			if (x >= n || y >= m || x < 0 || y < 0)
				return false;
			return true;
		}

		int solve(vector<vector<int>> dist) {
			queue<pair<int, int>> q;
			dist[x][y] = 1;
			// adauga in coada perechea de coordonate in care se afla Gigel
			q.push(make_pair(x, y));
			/* se viziteaza toate punctele in care se poate ajunge, din fiecare
			punct deja vizitat si se opreste atunci cand iese din matrice
			(cand ajunge pe uscat) si intoarce numarul de poduri trecute */
			while (!q.empty()) {
				x = q.front().first;
				y = q.front().second;
				q.pop();
				if (grid[x][y] == 1) {
					if (check(x+1, y) && dist[x+1][y] == 0) {
						q.push(make_pair(x+1, y));
						dist[x+1][y] = dist[x][y] + 1;
					} else if (!check(x+1, y)) {
						return dist[x][y];
					}

					if (check(x-1, y) && dist[x-1][y] == 0) {
						q.push(make_pair(x-1, y));
						dist[x-1][y] = dist[x][y] + 1;
					} else if (!check(x-1, y)) {
						return dist[x][y];
					}
				} else if (grid[x][y] == 0) {
					if(check(x, y+1) && dist[x][y+1] == 0) {
						q.push(make_pair(x, y+1));
						dist[x][y+1] = dist[x][y] + 1;
					} else if (!check(x, y+1)) {
						return dist[x][y];
					}
					if(check(x, y-1) && dist[x][y-1] == 0) {
						q.push(make_pair(x, y-1));
						dist[x][y-1] = dist[x][y] + 1;
					} else if (!check(x, y-1)) {
						return dist[x][y];
					}
				} else if (grid[x][y] == 2) {
					if (check(x+1, y) && dist[x+1][y] == 0) {
						q.push(make_pair(x+1, y));
						dist[x+1][y] = dist[x][y] + 1;
					} else if (!check(x+1, y)) {
						return dist[x][y];
					}

					if (check(x-1, y) && dist[x-1][y] == 0) {
						q.push(make_pair(x-1, y));
						dist[x-1][y] = dist[x][y] + 1;
					} else if (!check(x-1, y)) {
						return dist[x][y];
					}

					if (check(x, y+1) && dist[x][y+1] == 0) {
						q.push(make_pair(x, y+1));
						dist[x][y+1] = dist[x][y] + 1;
					} else if (!check(x, y+1)) {
						return dist[x][y];
					}

					if(check(x, y-1) && dist[x][y-1] == 0) {
						q.push(make_pair(x, y-1));
						dist[x][y-1] = dist[x][y] + 1;
					} else if (!check(x, y-1)) {
						return dist[x][y];
					}
				}
			}
			return -1;
		}
};

int main() {
    auto* task = new Poduri();
    if (!task) {
        return -1;
    }
    task->read_input();
    vector<vector<int>> dist(task->n, vector<int>(task->m, 0));
    int rez = task->solve(dist);
    ofstream fout("poduri.out");
    fout << rez;
    fout.close();
    delete task;
    return 0;
}
