#include <bits/stdc++.h>
using namespace std;

int main() {
    double x;
    cin >> x;
    double r=x<=1.0? 100.0*x: 100.0*(x+2.0)/3.0;
    cout << fixed << setprecision(10) << r;
    return 0;
}
