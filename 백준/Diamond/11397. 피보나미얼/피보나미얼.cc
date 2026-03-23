#include <bits/stdc++.h>
using namespace std;
using lint=int64_t;
constexpr int N=1001;

lint factorize(lint n, int p) {
    lint r=0;
    while (n) r+=(n/=p);
    return r;
}

int rank_prime(int p) {
    int a=0, b=1;
    for (int i=1;; i++) {
        int c=(a+b)%p;
        a=b, b=c;
        if (a==0) return i;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    lint n;
    int p;
    vector<int> prime;
    bitset<N> sieve;
    sieve.set();
    sieve[0]=sieve[1]=0;
    for (int i=2; i<N; i++) if (sieve[i]) {
        prime.push_back(i);
        for (int j=i*i; j<N; j+=i) sieve[j]=0;
    }

    cin >> n >> p;
    vector<lint> v_p(N);
    for (int q: prime)
        if (q==2) {
            lint m=n/3, e=m/2;
            v_p[q]=m*2-(m&1)+factorize(e, 2);
        } else {
            lint m=n/rank_prime(q);
            v_p[q]=m+factorize(m, q);
        }
    for (int k=2; k<=p; k++) {
        lint x=k, r=numeric_limits<lint>::max();
        for (int q: prime) {
            if (x<q*q) break;
            if (x%q) continue;
            int e=0;
            while (x%q==0) x/=q, e++;
            r=min(r, v_p[q]/e);
        }
        if (x>1) r=min(r, v_p[x]);
        cout << r << ' ';
    }
}