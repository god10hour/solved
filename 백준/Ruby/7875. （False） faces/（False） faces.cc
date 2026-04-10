#include <bits/stdc++.h>
using namespace std;
constexpr int N=300;
int n;

int det_mod2(vector<bitset<N>> a, int m) {
    int rank=0;
    for (int c=0; c<m; c++) {
        int piv=-1;
        for (int r=rank; r<m; r++)
            if (a[r][c]) {
                piv=r;
                break;
            }
        if (piv==-1) continue;
        swap(a[rank], a[piv]);
        for (int r=rank+1; r<m; r++) if (a[r][c]) a[r]^=a[rank];
        rank++;
    }
    return m==rank;
}

bool kernel_basis(const vector<bitset<N>> &rows, bitset<N> &x, bitset<N> &y) {
    vector<bitset<N>> a=rows;
    vector<int> pivot_c, free_c;
    vector<bool> is_piv(n);
    int m=rows.size(), rank=0;

    for (int c=0; c<n; c++) {
        int piv=-1;
        for (int r=rank; r<m; r++)
            if (a[r][c]) {
                piv=r;
                break;
            }
        if (piv==-1) continue;

        swap(a[rank], a[piv]);
        pivot_c.push_back(c);
        for (int r=0; r<m; r++) if (r!=rank && a[r][c]) a[r]^=a[rank];
        rank++;
        if (rank==m) break;
    }
    if (rank<m) return false;

    for (int c: pivot_c) is_piv[c]=true;
    for (int c=0; c<n; c++) if (!is_piv[c]) free_c.push_back(c);
    x.reset(), y.reset();
    x.set(free_c[0]), y.set(free_c[1]);

    for (int i=0; i<m; i++) {
        if (a[i][free_c[0]]) x.flip(pivot_c[i]);
        if (a[i][free_c[1]]) y.flip(pivot_c[i]);
    }
    return true;
}

int duplicate_term(const vector<bitset<N>> &org, int idx) {
    vector<bitset<N>> rows;
    bitset<N> u=org[idx], x, y, z;

    for (int i=1; i<n; i++) if (i!=idx) rows.push_back(org[i]);
    if (!kernel_basis(rows, x, y)) return 0;

    z=x&y;
    int a=(u&x).count()&1;
    int b=(u&y).count()&1;
    int c=(u&z).count()&1;
    return (a&b^c)<<1;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<bitset<N>> org(n);
        for (int i=0; i<n; i++) {
            string s;
            cin >> s;
            for (int j=0; j<n; j++) if (s[j]=='1') org[i].set(j);
        }
        if (det_mod2(org, n)) {
            cout << "NO\n";
            continue;
        }

        vector<bitset<N>> a=org, ops(n);
        for (int i=0; i<n; i++) ops[i].set(i);
        int rank=0;
        for (int c=0; c<n; c++) {
            int piv=-1;
            for (int r=rank; r<n; r++)
                if (a[r][c]) {
                    piv=r;
                    break;
                }
            if (piv==-1) continue;

            swap(a[rank], a[piv]);
            swap(ops[rank], ops[piv]);
            for (int r=0; r<n; r++)
                if (r!=rank && a[r][c]) {
                    a[r]^=a[rank];
                    ops[r]^=ops[rank];
                }
            rank++;
        }

        bitset<N> dep;
        for (int r=rank; r<n; r++)
            if (a[r].none()) {
                dep=ops[r];
                break;
            }
        int p=0;
        while (!dep[p]) p++;
        if (p!=0) {
            swap(org[0], org[p]);
            bool z=dep[0];
            dep[0]=dep[p], dep[p]=z;
        }
        bitset<N> half;
        vector<int> cnt(n);
        for (int i=0; i<n; i++) if (dep[i])
            for (int j=0; j<n; j++) if (org[i][j]) cnt[j]++;
        for (int j=0; j<n; j++) if (cnt[j]>>1&1) half.set(j);

        a=org, a[0]=half;
        int k=det_mod2(a, n)<<1;
        for (int i=1; i<n; i++) if (dep[i]) k=k+duplicate_term(org, i)&3;
        cout << (k==0? "YES": "NO") << '\n';
    }
}