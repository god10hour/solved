#include <stdio.h>
long long arr[10];
void calc(long long n, long long k) {
    while(n)
        arr[n%10]+=k,
        n/=10;
}
int main() {
    long long p=1,q,k=1;
    scanf("%lld",&q);
    while (p<=q) {
        while (p%10 && p<=q)
            calc(p,k),
            p++;
        if (p>q)
            break;
        while (q%10<9 && p<=q)
            calc(q,k),
            q--;
        long long c=(q/10-p/10+1);
        for (int i=0; i<=9; i++)
            arr[i]+=c*k;
        p/=10,q/=10;
        k*=10LL;
    }
    for (int i=0; i<10; i++)
        printf("%lld ",arr[i]);
}