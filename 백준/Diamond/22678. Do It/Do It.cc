#include <bits/stdc++.h>
using namespace std;

using rea=long double;
using cpx=complex<rea>;
constexpr rea pi=acosl(-1.0L);
constexpr int M=1600;
constexpr int S=M*2+1;

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, r;
    cout << fixed << setprecision(15);

    while (cin >> n >> r, n||r) {
        vector<cpx> dp(S), ndp(S);
        dp[M]=1;

        for (int i=0; i<n; i++) {
            int a, w, phi;
            cin >> a >> w >> phi;
            rea ang=rea(phi)*pi/180.0L;
            cpx e=polar(a/2.0L, ang);
            cpx u=e*cpx(0, -1), v=conj(e)*cpx(0, 1);

            ranges::fill(ndp, cpx(0, 0));
            for (int f=-M; f<=M; f++) {
                cpx cur=dp[f+M];
                if (abs(cur)==0) continue;
                if (f+w<=M) ndp[f+w+M]+=cur*u;
                if (f-w>=-M) ndp[f-w+M]+=cur*v;
            }
            dp.swap(ndp);
        }

        cpx s=cpx(0, 0);
        for (int k=-M; k<=M; k++) {
            cpx c=dp[k+M];
            if (abs(c)==0) continue;
            s+=k==0? c*rea(r): c*(exp(cpx(0, k*r))-cpx(1, 0))/cpx(0, k);
        }
        cout << s.real() << '\n';
    }
}