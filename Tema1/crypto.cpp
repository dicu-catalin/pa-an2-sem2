#include <bits/stdc++.h>
using namespace std;

#define INF ((int)1e9)

// compara nivelul curent a doua calculatoare
bool cmp(pair<int, int> a, pair<int, int> b) {
	return a.first < b.first;
}

class Crypto {
 public:
	int n, b;
	int curr_crypto = INF;
	vector<pair<int, int>> computers;

	void read_input() {
		ifstream fin("crypto.in");
        fin >> n >> b;
        for (int i = 0; i < n; i++) {
            int crypto_per_hour, upgrade_cost;
            fin >> crypto_per_hour >> upgrade_cost;
            if (curr_crypto > crypto_per_hour)
            	curr_crypto = crypto_per_hour;
            computers.push_back(make_pair(crypto_per_hour, upgrade_cost));
        }
        fin.close();
        // sorteaza calculatoarele dupa nivelul lor curent
        sort(computers.begin(), computers.end(), cmp);
	}

	void solve(){
		// retine ultimul calculator care a primit upgrade
		int last_upgraded = -1;
		// costul total de upgrade al calculatoarelor selectate
		int upgrade_all = 0;
		while(b > 0) {
			for (int i = last_upgraded + 1; i < n; i++) {
				/* atunci cand gaseste un calculator cu un nivel superior celor
					selectate pana atunci, se opreste din selectat */
				if (computers[i].first != curr_crypto)
					break;
				upgrade_all += computers[i].second;
				last_upgraded = i;
			}
			/* daca s-au selectat toate calculatoarele, le imbunatateste la 
				nivelul maxim */
			if (last_upgraded + 1 == n) {
				curr_crypto += b / upgrade_all;
				break;
			}
			/* calculeaza diferenta dintre calculatoarele selectate si priml
				calculator neselectat pentru upgrade */
			int power_diff = computers[last_upgraded + 1].first -
									computers[last_upgraded].first;
			// aduce calculatoarele selectate la acelasi nivel cu primul neales
			if (power_diff <= b / upgrade_all) {
				curr_crypto += power_diff;
				b -= upgrade_all * power_diff;
			} else {
				/*daca nu se pot aduce toate la nivelul computerului neselectat
				atunci sunt imbunatatite la maxim, iar programul se termina */
				curr_crypto += b / upgrade_all;
				break;
			}
		}

		ofstream fout("crypto.out");
		fout << curr_crypto;
		fout.close();
	}
};

int main() {
	Crypto* crypto = new Crypto();
	if (!crypto) {
    	std::cerr << "new failed: WTF are you doing? Throw your PC!\n";
    	return -1;
	}
	crypto->read_input();
	crypto->solve();
	delete crypto;
	return 0;
}
