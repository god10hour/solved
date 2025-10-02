#include <bits/stdc++.h>
using namespace std;

int main() {
    //cin.tie(0)->sync_with_stdio(0);
    int n, m, d;
    scanf("%d:%d", &n, &m);
    d=gcd(n, m);
    printf("%d:%d", n/d, m/d);
}