#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    vector<int> sa(n), rnk(n), tmp(n), lcp(n), pos(n);
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

    int k=0;
    for (int i=0; i<n; i++) {
        if (pos[i]==0) continue;
        int j=sa[pos[i]-1];
        while (i+k<n && j+k<n && s[i+k]==s[j+k]) k++;
        lcp[pos[i]]=k;
        if (k) k--;
    }
    for (int i=0; i<n; i++) cout << sa[i]+1 << ' ';
    cout << "\nx ";
    for (int i=1; i<n; i++) cout << lcp[i] << ' ';
}