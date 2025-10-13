#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    vector<int> v(10000);
    int A, B;
    iota(v.begin(), v.end(), 1);
    random_shuffle(v.begin(), v.end());

    for (int a=0; a<10000; a++) {
        cout << "? A " << v[a] << endl;
        cin >> A;
        if (A==1)
            for (int b=0; b<10000; b++) {
                cout << "? B " << v[b] << endl;
                cin >> B;
                if (B==1)
                    return !(cout << "! " << v[a]+v[b] << endl);
            }
    }
}
