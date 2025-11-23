#include <bits/stdc++.h>
using namespace std;

class Mo {
public:
    struct Query {
        int l, r, idx;
        Query(int l, int r, int idx): l(l), r(r), idx(idx) {}
    };

    explicit Mo(int n): n(n) {
        block=max<int>(1, sqrt(n));
    }

    void push(int l, int r, int idx) {
        qs.emplace_back(l, r, idx);
    }

    // AL/AR/RL/RR: void(int pos)
    // OUT: void(int q_idx)
    template<class AL, class AR, class RL, class RR, class OUT>
    void process(AL ladd, AR radd, RL lsub, RR rsub, OUT output) {
        order();
        int curL=0, curR=0;

        for (auto &q: qs) {
            int L=q.l, R=q.r;
            while (curL>L) ladd(--curL);
            while (curR<R) radd(curR++);
            while (curL<L) lsub(curL++);
            while (curR>R) rsub(--curR);
            output(q.idx);
        }
    }

private:
    int n;
    int block;
    vector<Query> qs;

    void order() {
        ranges::sort(
            qs, [&](const Query &a, const Query &b) {
                int ab=a.l/block, bb=b.l/block;
                if (ab!=bb) return ab<bb;
                return ab&1? a.r>b.r: a.r<b.r;
            }
        );
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, q;
    cin >> n >> q;
    Mo mo(n);
    vector<int> v(n), rs(q);
    for (int i=0; i<n; i++) cin >> v[i];
    for (int i=0; i<q; i++) {
        int l, r;
        cin >> l >> r;
        mo.push(l-1, r, i);
    }

    int cur=0;
    auto add=[&](int i) { cur+=v[i]; };
    auto sub=[&](int i) { cur-=v[i]; };
    auto out=[&](int i) { rs[i]=cur; };

    mo.process(
        [&](int i) { add(i); },
        [&](int i) { add(i); },
        [&](int i) { sub(i); },
        [&](int i) { sub(i); },
        out
    );

    for (int i=0; i<q; i++)
        cout << rs[i] << '\n';
}