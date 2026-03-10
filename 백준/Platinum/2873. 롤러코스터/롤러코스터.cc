#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int r, c;
    string s;
    cin >> r >> c;

    if (r%2) {
        bool z=true;
        int k=0;
        while (k<r) {
            for (int i=0; i<c-1; i++) s+=z? 'R': 'L';
            if (k<r-1) s+='D';
            k++;
            z=!z;
        }
        return !(cout << s << '\n');
    }
    if (c%2) {
        bool z=true;
        int k=0;
        while (k<c) {
            for (int i=0; i<r-1; i++) s+=z? 'D': 'U';
            if (k<c-1) s+='R';
            k++;
            z=!z;
        }
        return !(cout << s << '\n');
    }

    int mr=-1, mc=-1, mv=998244353;
    vector v(r, vector<int>(c));
    for (int i=0; i<r; i++)
        for (int j=0; j<c; j++)
            cin >> v[i][j];
    for (int i=0; i<r; i++)
        for (int j=1-i%2; j<c; j+=2) if (v[i][j]<mv)
            mv=v[i][j], mr=i, mc=j;
    int i=0, j=0;
    while (i<r) if (mr==i || mr==i+1) {
        bool u=true;
        while (i!=(mr|1) || j!=c-1) {
            if (u) {
                if ((i^1)==mr && j==mc) {
                    s+='R';
                    j++;
                    continue;
                }
                s+=i&1? 'U': 'D';
                i^=1;
            } else {
                s+='R';
                j++;
            }
            u=!u;
        }
        if (i++<r-1) s+='D';
    } else {
        for (int k=0; k<c-1; k++) s+=j? 'L': 'R';
        s+='D';
        for (int k=0; k<c-1; k++) s+=j? 'R': 'L';
        i+=2;
        if (i<r-1) s+='D';
    }
    cout << s << '\n';
}