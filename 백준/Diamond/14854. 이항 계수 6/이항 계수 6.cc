#include <bits/stdc++.h>
#define int int64_t
using namespace std;

// Util
int POW(int n, int k, int M) {
    int r=1;
    while (k) {
        if (k&1)
            r=r*n%M;
        n=n*n%M;
        k/=2;
    }
    return r;
}
int EGCD(int a, int b, int &x, int &y) {
    if (b==0) {
        x=a>=0?1:-1;
        y=0;
        return llabs(a);
    }
    int x1, y1;
    int d=EGCD(b, a%b, x1, y1);
    x=y1, y=x1-(a/b)*y1;
    return d;
}
int INV(int n, int M) {
    int x, y;
    int d=EGCD(n, M, x, y);
    x%=M;
    if (x<0) x+=M;
    return x;
}
inline int norm(int n, int M) {
    n%=M;
    if (n<0) n+=M;
    return n;
}

// Lucas
struct Prime {
    int p;
    vector<int> fac, ifac;
};
Prime L11, L13, L37;

Prime buildL(int P) {
    Prime L;
    L.p=P;
    L.fac.assign(P, 1);
    L.ifac.assign(P, 1);
    for (int i=1; i<P; i++)
        L.fac[i]=i*L.fac[i-1]%P;
    L.ifac[P-1]=POW(L.fac[P-1], P-2, P);
    for (int i=P-2; i>=0; i--)
        L.ifac[i]=(i+1)*L.ifac[i+1]%P;
    return L;
}
int comS(int n, int k, const Prime &L) {
    if (k<0 || k>n)
        return 0;
    return L.fac[n]*L.ifac[k]*L.ifac[n-k]%L.p;
}
int comL(int n, int k, const Prime &L) {
    if (k<0 || k>n)
        return 0;
    int P=L.p, r=1;
    while (n>0 || k>0) {
        int ni=n%P, ki=k%P;
        if (ki>ni)
            return 0;
        r=r*comS(ni, ki, L)%P;
        n/=P, k/=P;
    }
    return r;
}

// PrmExp
struct Power {
    int p, a, e;
    vector<int> pref;
    int cycle;
};
Power P27;

Power buildP(int P, int a) {
    Power PP;
    PP.p=P, PP.a=a, PP.e=1;
    for (int i=0; i<a; i++)
        PP.e*=P;
    PP.pref.assign(PP.e+1, 1);
    for (int i=1; i<PP.e+1; i++) {
        PP.pref[i]=PP.pref[i-1];
        if (i%P)
            PP.pref[i]=i*PP.pref[i]%PP.e;
    }
    PP.cycle=PP.pref[PP.e];
    return PP;
}
int vp(int n, int P) {
    int s=0;
    while (n)
        n/=P, s+=n;
    return s;
}
int facE(int n, const Power &PP) {
    if (n==0)
        return 1;
    int r=POW(PP.cycle, n/PP.e, PP.e);
    r=r*PP.pref[n%PP.e]%PP.e;
    return r*facE(n/PP.p, PP)%PP.e;
}
int comP(int n, int k, const Power &PP) {
    if (k<0 || k>n)
        return 0;
    k=min(k, n-k);
    int P=PP.p, a=PP.a, e=PP.e;
    int E=vp(n, P)-vp(k, P)-vp(n-k, P);
    if (E>=a)
        return 0;
    int N=facE(n, PP), K=facE(k, PP), NK=facE(n-k, PP);
    int inv=INV(K*NK%e, e);
    int r=N*inv%e;
    r=r*POW(P, E, e)%e;
    return r;
}

// ETC
pair<int, int> CRT(pair<int, int> A, pair<int, int> B) {
    int a=A.first, b=B.first;
    int m=A.second, n=B.second;
    int k=(__int128)norm(b-a, n)*INV(m%n, n)%n;
    int x=a+(__int128)m*k;
    x=norm(x, m*n);
    return {x, m*n};
}
int COM(int n, int k) {
    int r[4], p[4]={11, 13, 37, 27};
    r[0]=comL(n, k, L11);
    r[1]=comL(n, k, L13);
    r[2]=comL(n, k, L37);
    r[3]=comP(n, k, P27);
    pair<int, int> acc={r[0], p[0]};
    for (int i=1; i<4; i++)
        acc=CRT(acc, {r[i], p[i]});
    return acc.first;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    
    L11=buildL(11);
    L13=buildL(13);
    L37=buildL(37);
    P27=buildP(3, 3);
    while (t--) {
        int n, k;
        cin >> n >> k;
        cout << COM(n, k) << '\n';
    }
}