#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    while (cin >> s) {
        if (s=="#") return 0;
        string lower, upper, number;
        sort(s.begin(), s.end());
        for (char c: s)
            if (islower(c)) lower+=c;
            else if (isupper(c)) upper+=c;
            else number+=c;
        cout << lower+upper+number << '\n';
    }
}
