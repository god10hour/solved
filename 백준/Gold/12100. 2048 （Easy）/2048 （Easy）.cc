#include <bits/stdc++.h>
using namespace std;
int n;

vector<vector<int>> rotate(const vector<vector<int>> &A) {
    vector r(n, vector<int>(n));
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            r[i][j]=A[n-j-1][i];
    return r;
}

int run(vector<vector<int>> A, int k) {
    if (k==5) {
        int r=0;
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                r=max(r, A[i][j]);
        return r;
    }

    auto T=A;
    int r=0;
    for (int d=0; d<4; d++) {
        for (int j=0; j<n; j++) for (int i=0, top=-1; i<n; i++) {
            if (A[i][j]==0) continue;
            if (top+1==i) continue;
            if (A[top+1][j]==0) {
                A[top+1][j]=A[i][j];
                A[i][j]=0;
            } else if (A[top+1][j]==A[i][j]) {
                A[top+1][j]*=2;
                A[i][j]=0;
                top++;
            } else {
                A[top+2][j]=A[i][j];
                if (top+2!=i) A[i][j]=0;
                top++;
            }
        }
        int t=run(A, k+1);
        r=max(r, t);
        T=rotate(T), A=T;
    }
    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    vector A(n, vector<int>(n));
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            cin >> A[i][j];
    cout << run(A, 0) << '\n';
}
