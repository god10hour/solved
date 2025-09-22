#include <bits/stdc++.h>
using namespace std;
vector<bool> sieve(2001, 1);
int arr[1001], brr[1001];
bool visited[1001];
int d;
int L, R;
vector<int> l, r;

bool dfs(int n) {
    if (visited[n])
        return 0;
    visited[n]=1;
    for (int i=0; i<R; i++)
        if (i!=d && sieve[l[n]+r[i]])
            if (brr[i]==-1 || dfs(brr[i])) {
                brr[i]=n;
                return 1;
            }
    return 0;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    sieve[0]=sieve[1]=0;
    for (int i=2; i*i<2001; i++)
        if (sieve[i])
            for (int j=i*i; j<2001; j+=i)
                sieve[j]=0;
    int n, s;
    cin >> n;
    for (int i=0; i<n; i++)
        cin >> arr[i];
    s=arr[0];
    if (s&1)
        for (int i=0; i<n; i++)
            if (arr[i]&1)
                l.push_back(arr[i]);
            else
                r.push_back(arr[i]);
    else
        for (int i=0; i<n; i++)
            if (arr[i]&1)
                r.push_back(arr[i]);
            else
                l.push_back(arr[i]);
    L=l.size(), R=r.size();
    if (L!=R) {
        cout << -1;
        return 0;
    }
    sort(r.begin(), r.end());
    bool x=0;
    for (int i=0; i<R; i++)
        if (sieve[l[0]+r[i]]) {
            fill(brr, brr+1001, -1);
            d=i;
            brr[i]=0;
            int k=1;
            for (int j=1; j<L; j++) {
                fill(visited, visited+1001, 0);
                if (dfs(j))
                    k+=1;
            }
            if (k==L)
                x=1, cout << r[i] << ' ';
        }
    if (!x)
        cout << -1;
}