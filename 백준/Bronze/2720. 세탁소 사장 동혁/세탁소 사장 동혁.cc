#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		for (int i: {25,10,5,1}) {
			cout << n/i << ' ';
			n%=i;
		}
		cout << '\n';
	}
}