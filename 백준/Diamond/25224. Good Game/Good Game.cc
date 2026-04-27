#include <bits/stdc++.h>
using namespace std;
constexpr int N=1e6+1;

int n, m;
array<int, N> a, prv, nxt;
string s;
vector<pair<int, int>> out;

bool valid(int l, int r) {
    int len=r-l+1, mid=(l+r)/2;
    if ((len&1)==0) return false;
    if (a[mid]>1) return true;
    if (len==1) return false;
    int k=nxt[mid]-prv[mid]-1;
    return k*2+1<len;
}

void erase(int l, int r) {
    while (r-l+1>3) out.emplace_back(r-1, 2), r-=2;
    out.emplace_back(l, r-l+1);
}

void emit(int l, int r) {
    int mid=(l+r)/2, d=0;
    for (int i=1; i<l; i++) d+=a[i];
    if (a[mid]>1) {
        int x=d;
        for (int i=l; i<mid; i++) x+=a[i];
        erase(x+1, x+a[mid]);
        for (int i=mid-1; i>=l; i--) {
            x-=a[i];
            erase(x+1, x+a[i]+a[2*mid-i]);
        }
        return;
    }

    int p=prv[mid], q=nxt[mid], x=d;
    for (int i=l; i<q; i++) x+=a[i];
    erase(x+1, x+a[q]);
    for (int i=mid-1; i>p; i--) {
        int k=mid-i;
        x-=a[q-k];
        erase(x+1, x+a[q-k]+a[q+k]);
    }

    int k=mid-p;
    a[q-k]+=a[q+k];
    for (int i=q-k+1, j=q+k+1; j<=r; i++, j++) a[i]=a[j];
    x=d;
    for (int i=l; i<p; i++) x+=a[i];
    erase(x+1, x+a[p]);
    for (int i=p-1; i>=l; i--) {
        x-=a[i];
        erase(x+1, x+a[i]+a[p*2-i]);
    }
}

int print() {
    cout << out.size() << '\n';
    for (auto [i, j]: out) cout << i << ' ' << j << '\n';
    return 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> n >> s;
    s=' '+s;
    for (int l=1, r; l<=n; l=r+1) {
        r=l;
        while (r<n && s[r+1]==s[l]) r++;
        a[++m]=r-l+1;
    }
    prv[0]=0, nxt[m+1]=m+1;
    for (int i=1; i<=m; i++) prv[i]=a[i]>1? i: prv[i-1];
    for (int i=m; i>=1; i--) nxt[i]=a[i]>1? i: nxt[i+1];

    if (m&1) {
        if (!valid(1, m)) return !(cout << -1 << '\n');
        emit(1, m);
        return print();
    }
    for (int i=1; i<m; i+=2) {
        if (!valid(1, i) || !valid(i+1, m)) continue;
        emit(i+1, m);
        emit(1, i);
        return print();
    }
    cout << -1 << '\n';
}