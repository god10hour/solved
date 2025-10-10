#include <bits/stdc++.h>
using namespace std;
string a, b, lps;

void LCS(int s1, int e1, int s2, int e2) {
    if (s1==e1) {
        for (int i=s2; i<=e2; i++)
            if (a[s1]==b[i]) {
                lps+=b[i];
                break;
            }
        return;
    }

    int mid=(s1+e1)/2;
    int len=e2-s2+1;
    vector<int> upper(len+2), lower(len+2);
    vector<int> temp(len+2);

    for (int i=s1; i<=mid; i++) {
        for (int j=s2; j<=e2; j++)
            if (a[i]==b[j])
                upper[j-s2+1]=temp[j-s2]+1;
            else
                upper[j-s2+1]=max(temp[j-s2+1], upper[j-s2]);
        temp=upper;
    }
    fill(temp.begin(), temp.end(), 0);
    for (int i=e1; i>=mid+1; i--) {
        for (int j=e2; j>=s2; j--)
            if (a[i]==b[j])
                lower[j-s2+1]=temp[j-s2+2]+1;
            else
                lower[j-s2+1]=max(temp[j-s2+1], lower[j-s2+2]);
        temp=lower;
    }
    int mxm=0, idx=0;
    for (int i=s2-1; i<=e2; i++)
        if (mxm<=upper[i-s2+1]+lower[i-s2+2])
            mxm=upper[i-s2+1]+lower[i-s2+2],
            idx=i;
    LCS(s1, mid, s2, idx);
    LCS(mid+1, e1, idx+1, e2);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> a;
    b=string(a.rbegin(), a.rend());
    LCS(0, a.length()-1, 0, b.length()-1);
    int n=a.length();
    int i=0, j=n-1, k=0, l=lps.length()-1;
    string lft, rgh;
    while (k<=l) {
        while (i<=j && a[i]!=lps[k])
            lft+=a[i], rgh+=a[i], i++;
        while (i<=j && a[j]!=lps[l])
            lft+=a[j], rgh+=a[j], j--;
        if (k>l || i>j) break;
        if (k<l)
            lft+=a[i], rgh+=a[j];
        else lft+=lps[k];
        i++, j--, k++, l--;
    }
    while (i<=j)
        lft+=a[i], rgh+=a[i], i++;
    lps=lft;
    reverse(rgh.begin(), rgh.end());
    lps+=rgh;
    cout << lps.length()-n << '\n' << lps;
}