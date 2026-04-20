#include <bits/stdc++.h>
using namespace std;

constexpr int   IT=800;
constexpr int    W=2;
constexpr double H=0.5;

constexpr double X_MIN=-10.0;
constexpr double X_MAX=+10.0;
constexpr double Y_MIN=-13.0;
constexpr double Y_MAX=+13.0;

constexpr int  LEN=(X_MAX-X_MIN)/H+1;
constexpr int  MID=(LEN-1)/2;
constexpr double M=(Y_MAX-Y_MIN)/(1.0*W*W*1600);
constexpr double EPS=1e-12;

double dose(const vector<double> &C, double x2, double y) {
    double s=0;
    for (double c: C) {
        double dy=y-c, d2=x2+dy*dy;
        if (d2<EPS) return numeric_limits<double>::infinity();
        s+=1.0/d2;
    }
    return s;
}

double seg_cost(const vector<double> &C, double x2, double y, double dy) {
    return (1.0+dose(C, x2, y))*hypot(H, dy);
}

double total_cost(const vector<double> &C, const array<double, LEN> &xsq, const array<double, LEN> &y) {
    double acc=0;
    for (int i=0; i<LEN-1; i++)
        acc+=seg_cost(C, xsq[i], y[i], y[i+1]-y[i]);
    return acc;
}

double bump(int i, int j, double m) {
    if (j==0 || j==LEN-1) return 0;
    return m*(W-abs(j-i));
}

double local_cost(const vector<double> &C, const array<double, LEN> &xsq, const array<double, LEN> &y, int i, double m) {
    int L=max(0, i-W);
    int U=min(LEN-1, i+W);

    double yy[2*W+1];
    for (int j=L; j<=U; j++)
        yy[j-L]=y[j]+bump(i, j, m);

    double acc=0;
    for (int j=L; j<U; j++) {
        double y0=yy[j-L];
        double y1=yy[j-L+1];
        acc+=seg_cost(C, xsq[j], y0, y1-y0);
    }
    return acc;
}

void apply(array<double, LEN> &y, int i, double m) {
    int L=max(0, i-W);
    int U=min(LEN-1, i+W);
    for (int j=L; j<=U; j++)
        y[j]+=bump(i, j, m);
}

double hillclimb(const vector<double> &C, const array<double, LEN> &xsq, array<double, LEN> &y) {
    for (int k=0; k<IT; k++) {
        bool any=false;
        for (int i=1; i<LEN-1; i++) {
            double up=local_cost(C, xsq, y, i, +M);
            double dn=local_cost(C, xsq, y, i, -M);
            if (up<dn) apply(y, i, +M), any=true;
            else if (dn<up) apply(y, i, -M), any=true;
        }
        if (!any) break;
    }
    return total_cost(C, xsq, y);
}

double islands() {
    int n;
    double a, b;
    cin >> n >> a >> b;

    vector<double> C(n), region;
    for (double &c: C) cin >> c;

    region.reserve(n+2);
    region.emplace_back(Y_MIN);
    region.emplace_back(Y_MAX);
    for (double c: C) region.emplace_back(c);

    ranges::sort(region);
    region.erase(unique(region.begin(), region.end()), region.end());

    array<double, LEN> xsq={};
    for (int j=0; j<LEN; j++) {
        double x=X_MIN+j*H;
        xsq[j]=x*x;
    }

    double r=numeric_limits<double>::infinity();

    for (int i=0; i+1<region.size(); i++) {
        double mid=(region[i]+region[i+1])/2.0;
        array<double, LEN> y;

        for (int j=0; j<MID; j++)
            y[j]=a+1.0*j/MID*(mid-a);
        for (int j=MID; j<LEN; j++)
            y[j]=mid+1.0*(j-MID)/(LEN-MID-1)*(b-mid);

        r=min(r, hillclimb(C, xsq, y));
    }

    return r;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cout << fixed << setprecision(10);
    int T;
    cin >> T;
    for (int t=1; t<=T; t++)
        cout << "Case #" << t << ": " << islands() << '\n';
}