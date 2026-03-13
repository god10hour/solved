#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int n;
    string s;
    cin >> n >> s;
    vector<int> sa(n), rnk(n), tmp(n), pos(n);
    for (int i=0; i<n; i++) {
        sa[i]=i;
        rnk[i]=s[i];
    }
    for (int k=1; k<n; k<<=1) {
        auto cmp=[&](int a, int b) {
            if (rnk[a]!=rnk[b]) return rnk[a]<rnk[b];
            int ra=a+k<n? rnk[a+k]: -1;
            int rb=b+k<n? rnk[b+k]: -1;
            return ra<rb;
        };
        ranges::sort(sa, cmp);
        tmp[sa[0]]=0;
        for (int i=1; i<n; i++)
            tmp[sa[i]]=tmp[sa[i-1]]+cmp(sa[i-1], sa[i]);
        for (int i=0; i<n; i++) rnk[i]=tmp[i];
        if (rnk[sa[n-1]]==n-1) break;
    }
    for (int i=0; i<n; i++) pos[sa[i]]=i;

    int r=0, k=0;
    for (int i=0; i<n; i++) {
        if (pos[i]==0) continue;
        int j=sa[pos[i]-1];
        while (i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        r=max(r, k);
        if (k) k--;
    }
    cout << r << '\n';
}