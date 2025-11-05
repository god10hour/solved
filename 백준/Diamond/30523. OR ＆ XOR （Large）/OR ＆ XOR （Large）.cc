#include <bits/stdc++.h>
using namespace std;
constexpr int U=17;
constexpr int M=1<<U;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, p;
    cin >> n >> p;
    vector<int> A(n), B(n);
    vector<int64_t> CA(M, 0), CB(M, 0);
    for (int i=0; i<n; i++) cin >> A[i], CA[A[i]]++;
    for (int i=0; i<n; i++) cin >> B[i], CB[B[i]]++;

    int64_t xors=0;
    for (int k=0; k<U; k++) {
        int64_t a=0, b=0;
        for (int x: A) a+=x>>k&1;
        for (int y: B) b+=y>>k&1;
        int64_t pairs=a*(n-b)+b*(n-a);
        xors+=pairs*(1LL<<k);
    }

    auto S=[&](vector<int64_t> &v) {
        for (int k=0; k<U; k++)
            for (int i=0; i<M; i++)
                if ((i&1<<k)==0)
                    v[i]+=v[i|1<<k];
    };
    S(CA);
    S(CB);

    vector<int64_t> count(M, 0);
    for (int i=0; i<M; i++)
        count[i]=CA[i]*CB[i];
    for (int k=0; k<U; k++)
        for (int i=0; i<M; i++)
            if ((i&1<<k)==0)
                count[i]-=count[i|1<<k];

    int64_t inc=0, need=p;
    for (int v=M-1; v>=0 && need>0; v--) {
        int64_t take=min(count[v], need);
        inc+=take*v;
        need-=take;
    }

    cout << (xors+inc);
}
