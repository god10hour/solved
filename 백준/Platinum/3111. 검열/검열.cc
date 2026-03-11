#include <bits/stdc++.h>
using namespace std;

int n;
string a, t;
deque<char> ldq, rdq;

bool left_match() {
    int s=ldq.size();
    if (n>s) return false;
    for (int i=0; i<n; i++)
        if (a[i]!=ldq[s-n+i]) return false;
    return true;
}
bool right_match() {
    int s=rdq.size();
    if (n>s) return false;
    for (int i=0; i<n; i++)
        if (a[i]!=rdq[i]) return false;
    return true;
}

bool match(int i) {
    for (int j=0; j<n; j++)
        if (a[j]!=(i+j<ldq.size()? ldq[i+j]: rdq[i+j-ldq.size()]))
            return false;
    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> a >> t;
    n=a.size();
    int l=0, r=t.size()-1;
    while (l<=r) {
        while (l<=r) {
            ldq.push_back(t[l++]);
            if (left_match()) {
                ldq.erase(ldq.end()-n, ldq.end());
                break;
            }
        }
        while (l<=r) {
            rdq.push_front(t[r--]);
            if (right_match()) {
                rdq.erase(rdq.begin(), rdq.begin()+n);
                break;
            }
        }
    }
    bool run=true, z=true;
    while (run) {
        run=false;
        int lb=max<int>(ldq.size()-n+1, 0);
        int rb=min<int>(ldq.size()-1, ldq.size()+rdq.size()-n);
        for (int i=z? lb: rb; lb<=i && i<=rb; z? i++: i--) if (match(i)) {
            auto it=rdq.begin()+(i+n-ldq.size());
            ldq.erase(ldq.begin()+i, ldq.end());
            rdq.erase(rdq.begin(), it);
            run=true;
            break;
        }
        z^=1;
    }
    for (auto &c: ldq) cout << c;
    for (auto &c: rdq) cout << c;
    cout << '\n';
}