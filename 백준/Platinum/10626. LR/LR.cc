#include <bits/stdc++.h>
using namespace std;

bool better(const string &a, const string &b) {
    if (b.empty()) return true;
    if (a.empty()) return false;
    if (a.size()!=b.size()) return a.size()>b.size();
    return a>b;
}

string local(const string &s, int l, int r) {
    int n=r-l;
    if (n<=0) return "";
    for (int i=l; i<r; i++)
        if (!('0'<=s[i] && s[i]<='9') && s[i]!='?')
            return "";
    string t;
    t.reserve(n);
    if (n==1) {
        t.push_back(s[l]=='?'? '9': s[l]);
        return t;
    }

    char fir=s[l];
    if (fir=='0') return "";
    if (fir=='?') t.push_back('9');
    else {
        if (fir<'1' || fir>'9') return "";
        t.push_back(fir);
    }

    for (int i=l+1; i<r; i++)
        t.push_back(s[i]=='?'? '9': s[i]);
    return t;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    vector dp(n+1, vector<string>(n+1, ""));

    for (int k=1; k<=n; k++) for (int l=0; l+k<=n; l++) {
        int r=l+k;
        string loc, cand=local(s, l, r);
        if (better(cand, loc)) loc=cand;

        if (k>=5) {
            char fx=s[l], op=s[l+1], cl=s[r-1];
            if ((fx=='L' || fx=='R' || fx=='?') && (op=='(' || op=='?') && (cl==')' || cl=='?'))
                for (int m=l+2; m<=r-3; m++) {
                    char mid=s[m];
                    if (!(mid==',' || mid=='?')) continue;

                    string left=dp[l+2][m];
                    string right=dp[m+1][r-1];
                    if (left.empty() || right.empty()) continue;

                    if (fx=='L') {
                        if (better(left, loc)) loc=left;
                    } else if (fx=='R') {
                        if (better(right, loc)) loc=right;
                    } else { // '?'
                        string cand=better(left, right)? left: right;
                        if (better(cand, loc)) loc=cand;
                    }
                }
        }
        dp[l][r]=loc;
    }

    if (dp[0][n].empty())
        cout << "invalid\n";
    else cout << dp[0][n] << '\n';
}