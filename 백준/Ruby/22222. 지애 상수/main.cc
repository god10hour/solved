#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace std;
using namespace chrono;
using boost::multiprecision::number;
using boost::multiprecision::cpp_dec_float;

constexpr int N=1000;
constexpr int DIGITS=266;
constexpr bool USE_CACHE=true;
constexpr bool SHOW_PROGRESS=true;
constexpr size_t UPDATE_TICK=1000;

using Dec=number<cpp_dec_float<DIGITS>>;
const string EV_CACHE   ="ev_N_"+to_string(N)+"_D_"+to_string(DIGITS)+".tsv";
const string OUTPUT_FILE="evaluated"+to_string(N)+".out";

struct Complex {
    Dec r, i;
    Complex(): r(0), i(0) {}
    explicit Complex(Dec r, Dec i): r(move(r)), i(move(i)) {}

    Complex operator+(const Complex &o) const {
        return Complex(r+o.r, i+o.i);
    }
    Complex operator-(const Complex &o) const {
        return Complex(r-o.r, i-o.i);
    }
    Complex operator*(const Complex &o) const {
        return Complex(r*o.r - i*o.i, r*o.i + i*o.r);
    }
    Complex operator/(const Complex &o) const {
        const Dec d=o.r*o.r + o.i*o.i;
        return Complex((r*o.r + i*o.i)/d, (i*o.r - r*o.i)/d);
    }

    [[nodiscard]] Complex conj() const {
        return Complex(r, -i);
    }
    [[nodiscard]] Complex cabs() const {
        return Complex(sqrt(r*r + i*i), Dec(0));
    }
};

struct Progress {
    const size_t total;
    size_t cur=0, tick=0;
    string title;
    steady_clock::time_point t0=steady_clock::now();

    explicit Progress(const size_t total, string title="")
        : total(total), title(move(title)) {
    }

    void update(const size_t inc=1) {
        if constexpr (!SHOW_PROGRESS) return;
        cur+=inc;
        if (cur>total) cur=total;
        if (++tick%UPDATE_TICK) return;

        const auto now=steady_clock::now();
        const double el=duration<double>(now-t0).count();
        const double rate=cur>0 && el>0? cur/el: 0.0;
        const double eta=rate>0? (total-cur)/rate: 0.0;

        constexpr int width=30;
        double ratio=total? double(cur)/double(total): 1.0;
        int filled=floor(ratio*width);

        ostringstream oss;
        if (!title.empty()) oss << "[" << title << "] ";

        oss << setw(3) << setfill(' ') << int(ratio*100) << "% [";
        for (int i=0; i<width; i++) oss << (i<filled ? '=' : ' ');
        oss << "]  " << cur << "/" << total;

        oss << " | elap: " << fixed << setprecision(1) << el << 's';
        oss << " | ETA: "  << fixed << setprecision(1) << max(0.0, eta) << 's';

        cout << '\r' << oss.str();
        cout.flush();
        if (cur==total) cout << '\n';
    }
};

static vector<vector<Dec>> CB;
static vector<vector<Dec>> EV;
static vector<vector<Dec>> DP;
static vector<Dec> coeff;

namespace init {
    void binom(const int n) {
        CB.assign(n+1, vector<Dec>(n+1, Dec(0)));
        Progress bar((n+1)*(n+1), "binom");

        for (int i=0; i<=n; i++) {
            CB[i][0]=CB[i][i]=Dec(1);
            bar.update(2);
            for (int j=1; j<i; j++) {
                CB[i][j]=CB[i-1][j-1]+CB[i-1][j];
                bar.update();
            }
            for (int j=i+1; j<=n; j++) bar.update();
        }
    }

    void EVDP(const int n) {
        EV.assign(n+1, vector<Dec>(n+1, Dec(0)));
        DP.assign(n+1, vector<Dec>(n+1, Dec(0)));
        Progress bar((n+1)*(n+1)*2, "EV/DP");

        EV[0][0]=DP[0][0]=Dec(1);
        bar.update(2);

        for (int i=0; i<=n; i++)
            for (int j=0; j<=n; j++) if (i || j) {
                if ((i-j)%6==0) {
                    Dec acc=0;
                    for (int k=0; k<i; k++)
                        acc+=CB[i][k]*DP[k][j];
                    for (int k=0; k<j; k++) if ((i-k)%6==0)
                        acc+=CB[j][k]*EV[i][k];
                    Dec den=Dec(3)*(pow(Dec(2), i+j)-Dec(1));
                    EV[i][j]=acc*Dec(2)/den;
                } bar.update();

                Dec acc=0;
                for (int k=0; k<=j; k++)
                    acc+=CB[j][k]*EV[i][k];
                DP[i][j]=acc;
                bar.update();
            }
    }

    void coeffs(const int n) {
        coeff.assign(n+1, Dec(0));
        Progress bar((n+1), "coeff");
        vector<Dec> fact(n+1, Dec(1));
        for (int i=1; i<=n; i++) fact[i]=Dec(i)*fact[i-1];
        coeff[0]=Dec(1);
        bar.update();

        for (int i=1; i<=n; i++) {
            Dec odd=1; // (2m-3)!!
            for (int j=i*2-3; j>0; j-=2) odd*=Dec(j);

            Dec num=i%2? odd: -odd;
            Dec den=pow(Dec(2), i)*fact[i];
            coeff[i]=num/den;
            bar.update();
        }
    }

    bool save_EV(const vector<vector<Dec>> &EV) {
        if constexpr (!USE_CACHE) return false;
        ofstream fout(EV_CACHE);

        fout << "EV_CACHE\nMAXN " << N << "\tDIGITS " << DIGITS << '\n';
        fout << fixed << setprecision(260);
        for (int i=0; i<=N; i++)
            for (int j=0; j<=i; j++)
                if ((i-j)%6==0)
                    fout << i << '\t' << j << '\t' << EV[i][j] << '\n';
        return true;
    }
    bool load_EV(vector<vector<Dec>> &EV) {
        if constexpr (!USE_CACHE) return false;
        ifstream fin(EV_CACHE);
        string tag, key1, key2;
        int n, d;
        if (!(fin >> tag >> key1 >> n >> key2 >> d)) return false;
        if (tag!="EV_CACHE_V1" || key1!="MAXN" || key2!="DIGITS") return false;
        if (n!=N || d!=DIGITS) return false;

        EV.assign(n+1, vector<Dec>(n+1, Dec(0)));
        int p, q;
        string val;
        while (fin >> p >> q >> val) {
            EV[p][q]=Dec(val);
            if (p!=q) EV[q][p]=EV[p][q];
        }
        return true;
    }

    void re_DP() {
        DP.assign(N+1, vector<Dec>(N+1, Dec(0)));
        for (int i=0; i<=N; i++)
            for (int j=0; j<=N; j++) {
                Dec acc=0;
                for (int k=0; k<=j; k++)
                    acc+=CB[j][k]*EV[i][k];
                DP[i][j]=acc;
            }
    }
}

Dec eval(const Complex &U) {
    static vector<Complex> Up(N+1), Uc(N+1);
    Up[0]=Uc[0]=Complex(1, 0);
    Progress bar(N*2, "U_pows");
    for (int i=1; i<=N; i++) {
        Up[i]=Up[i-1]*U;
        bar.update();
    }
    Complex Ustar=U.conj();
    for (int i=1; i<=N; i++) {
        Uc[i]=Uc[i-1]*Ustar;
        bar.update();
    }

    Dec s=0;
    Progress bar2((N+1)*(N+1), "double_sum");
    for (int i=0; i<=N; i++)
        for (int j=0; j<=N; j++) {
            const Complex &a=Up[i], &b=Uc[j];
            Dec rea=a.r*b.r - a.i*b.i;
            s+=rea*coeff[i]*coeff[j]*EV[i][j];
            bar2.update();
        }
    return s;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    init::binom(N);
    if (init::load_EV(EV))
        init::re_DP();
    else {
        init::EVDP(N);
        init::save_EV(EV);
    }
    init::coeffs(N);

    const auto z=Complex(Dec(1)/Dec(2), sqrt(Dec(3))/Dec(2) );
    array<Complex, 6> P6;
    P6[0]=Complex(1, 0);
    for (int i=1; i<6; i++) P6[i]=P6[i-1]*z;

    vector<pair<Complex, Dec>> xs;
    xs.emplace_back(Complex(), Dec(1)/Dec(3));
    for (int i=0; i<6; i++) if (i!=3)
        xs.emplace_back(P6[i], Dec(1)/Dec(9));

    Dec s=0;
    Progress outer(xs.size(), "outer_sum");
    const auto half=Complex(Dec(1)/Dec(2), Dec(0));
    const auto one=Complex(1, 0);
    for (auto &x: xs) {
        const auto &[a, b]=x;
        Complex plus=one+half*a;
        Complex U=half/plus;
        Dec scale=plus.cabs().r;
        s+=b*scale*eval(U);
        outer.update();
    }

    ofstream fout(OUTPUT_FILE);
    Dec r=Dec(36)/Dec(85)*s;
    cout << '\n';
    cout << fixed << setprecision(222) << r << '\n';
    fout << fixed << setprecision(222) << r << '\n';
}
