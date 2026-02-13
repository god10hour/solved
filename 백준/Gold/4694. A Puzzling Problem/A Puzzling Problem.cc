#include <bits/stdc++.h>
using namespace std;
using u16=uint16_t;

struct Plc {
    u16 m;
    array<int, 16> pos;
    int k;
    explicit Plc(u16 m=0): m(m), pos{}, k(0) {}
};
struct Pie {
    int idx, area;
    vector<Plc> plc;
    explicit Pie(int idx=0): idx(idx), area(0){}
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n) {
        if (n==0) break;
        vector<Pie> p;
        p.reserve(n);
        int tot=0;
        for (int i=1; i<=n; i++) {
            int r, c;
            cin >> r >> c;
            vector<pair<int, int>> t, cells;
            cells.reserve(16);
            for (int y=0; y<r; y++) {
                string g;
                cin >> g;
                for (int x=0; x<c; x++) if (g[x]=='1')
                    cells.emplace_back(x,y);
            }
            int xmin=4, ymin=4, xmax=-1, ymax=-1;
            for (auto [x,y]: cells) {
                xmin=min(xmin,x);
                ymin=min(ymin,y);
                xmax=max(xmax,x);
                ymax=max(ymax,y);
            }
            t.reserve(cells.size());
            for (auto [x,y]: cells) t.emplace_back(x-xmin, y-ymin);

            Pie one(i);
            one.area=t.size();
            tot+=one.area;
            for (int oy=0; oy<=4-(ymax-ymin+1); oy++)
                for (int ox=0; ox<=4-(xmax-xmin+1); ox++) {
                    Plc plc;
                    u16 m=0;
                    for (auto [x, y]: t) {
                        int bp=(y+oy)*4+x+ox;
                        m|=u16(1u<<bp);
                        plc.pos[plc.k++]=bp;
                    }
                    plc.m=m;
                    one.plc.push_back(plc);
                }
            ranges::sort(one.plc, [&](const Plc &a, const Plc &b) {
                return a.m<b.m;
            });
            one.plc.erase(
                ranges::unique(one.plc, [&](const Plc &a, const Plc &b) {
                    return a.m==b.m;
                }).begin(),one.plc.end()
            );
            p.push_back(move(one));
        }
        if (tot!=16) {
            cout << "No solution possible\n\n";
            continue;
        }

        vector<int> ord(n);
        iota(ord.begin(), ord.end(), 0);
        ranges::stable_sort(ord, [&](int a, int b){
            if (p[a].plc.size()!=p[b].plc.size())
                return p[a].plc.size()<p[b].plc.size();
            return p[a].area>p[b].area;
        });
        array<char, 16> board;
        board.fill('0');

        bool z=false;

        function<void(int,u16)> dfs=[&](int d, u16 used) {
            if (z) return;
            if (d==n) {
                if (used==u16(0xFFFFu)) z=true;
                return;
            }

            int pi=ord[d];
            char c=char('0'+p[pi].idx);
            for (const auto &pl: p[pi].plc) {
                if (used&pl.m) continue;
                for (int i=0; i<pl.k; i++)
                    board[pl.pos[i]]=c;
                dfs(d+1, u16(used|pl.m));
                if (z) return;
                for (int i=0; i<pl.k; i++)
                    board[pl.pos[i]]='0';
            }
        };
        dfs(0, u16(0));

        if (!z) {
            cout << "No solution possible\n\n";
            continue;
        }
        for (int r=0; r<4; r++, cout << '\n')
            for (int c=0; c<4; c++)
                cout << board[r*4+c];
        cout << '\n';
    }
}