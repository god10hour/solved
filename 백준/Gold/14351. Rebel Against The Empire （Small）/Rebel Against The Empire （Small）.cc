#include <bits/stdc++.h>
using namespace std;
constexpr int N=1000;

int n, s;
array<int, N> u[3], v[3];
array<array<double, N>, N> jump_s, jump_e;
array<double, N> stay_s, stay_e;

bool run(const double &D) {
    for (int i=0; i<n; i++) for (int j=0; j<n; j++) if (i!=j) {
        double a=0, b=0, c=0;
        for (int k=0; k<3; k++) {
            a+=(v[k][i]-v[k][j])*(v[k][i]-v[k][j]);
            b+=(u[k][i]-u[k][j])*(v[k][i]-v[k][j])*2;
            c+=(u[k][i]-u[k][j])*(u[k][i]-u[k][j]);
        }
        jump_s[i][j]=numeric_limits<double>::max();
        jump_e[i][j]=numeric_limits<double>::min();

        if (a==0) {
            if (c<=D) {
                jump_s[i][j]=0;
                jump_e[i][j]=numeric_limits<double>::max();
            }
        } else {
            double disc=b*b-4*a*(c-D);
            if (disc>=0) {
                jump_s[i][j]=(-b-sqrt(disc))/(2*a);
                jump_e[i][j]=(-b+sqrt(disc))/(2*a);
            }
        }
    }

    for (int i=1; i<n; i++) {
        stay_s[i]=numeric_limits<double>::max();
        stay_e[i]=numeric_limits<double>::min();
    }
    stay_s[0]=0;
    stay_e[0]=s;

    queue<int> q;
    q.emplace(0);
    while (!q.empty()) {
        auto i=q.front();
        q.pop();
        for (int j=0; j<n; j++) if (j!=i && jump_s[i][j]<jump_e[i][j]) {
            auto l=max(stay_s[i], jump_s[i][j]);
            auto r=min(stay_e[i], jump_e[i][j]);
            if (l<=r) {
                if (j==1) return true;
                r=jump_e[i][j];
                if (l<stay_s[j] || r+s>stay_e[j]) {
                    stay_s[j]=min(stay_s[j], l);
                    stay_e[j]=max(stay_e[j], r+s);
                    q.emplace(j);
                }
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(5);

    int T;
    cin >> T;
    for (int t=1; t<=T; t++) {
        cin >> n >> s;
        for (int i=0; i<n; i++) {
            cin >> u[0][i] >> u[1][i] >> u[2][i];
            cin >> v[0][i] >> v[1][i] >> v[2][i];
        }
        double l=0, r=3e6;
        for (int i=0; i<50; i++) {
            auto mid=(l+r)/2;
            (run(mid)? r: l)=mid;
        }
        cout << "Case #" << t << ": " << sqrt(r) << '\n';
    }
}