#include <bits/stdc++.h>
using namespace std;

#define INF ((long int)1e17)

class Task {
 public:
	int n;
	vector<int> mountains;

	void read_input() {
		ifstream fin("valley.in");
		fin >> n;
		for (int i = 0; i < n; i++) {
			int mountain;
			fin >> mountain;
			mountains.push_back(mountain);
		}
		fin.close();
	}


	void solve() {
		// vector ce retine costurile din stanga vaii
		vector<long int> first(n, 0);
		// vector ce retine costurile din dreapta vaii
		vector<long int> second(n, 0);
		// numarul minim gasit in partea din stanga vaii
		long int min_mountainL = mountains[0];
		// numarul minim gasit in partea din dreapta vaii
		long int min_mountainR = mountains[n-1];
		for (int i = 1; i < n-1; i++) {
			first[i] = first[i-1];
			// daca muntele din dreapta este mai inalt, costul creste
			if (min_mountainL < mountains[i])
				first[i] += mountains[i] - min_mountainL;
			else
				min_mountainL = mountains[i];
			second[i] = second[i-1];
			/*porneste de la sfarsitul vectorului si calculeaza costurile pana
			la anumite puncte din vale*/
			if (min_mountainR < mountains[n-i-1])
				second[i] += mountains[n-i-1] - min_mountainR;
			else
				min_mountainR = mountains[n-i-1];
		}
		long int min = INF;
		// se considera fiecare punct ca fiind centrul vaii si se alege minimul
		for (int i = 1; i < n-1; i++) {
			if (min > first[i-1] + second[n-i-1])
				min = first[i-1] + second[n-i-1];
			if(i == 1 && mountains[1] > mountains[0] &&
									mountains[2] > mountains[0])
				min += mountains[1] - mountains[0];
		}

		ofstream fout("valley.out");
		fout << min;
		fout.close();
	}
};

int main() {
    Task* valley = new Task();
    if (!valley) {
        std::cerr << "Obiectul nu a fost creat!\n";
        return -1;
    }
    valley->read_input();
    valley->solve();
    delete valley;
    return 0;
}
