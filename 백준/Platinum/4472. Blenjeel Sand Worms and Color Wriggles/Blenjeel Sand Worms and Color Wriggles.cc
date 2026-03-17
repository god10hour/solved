#include <bits/stdc++.h>
using namespace std;
using sint=uint16_t;
using lint=uint64_t;
using state=array<sint, 6>;
constexpr int dr[4]={-1, 1, 0, 0};
constexpr int dc[4]={0, 0, -1, 1};

lint encode(const state &s, int n) {
    lint key=0;
    for (int i=0; i<n; i++)
        key|=lint(s[i])<<(i*9);
    return key;
}

bool goal(const state &s, int n, int m) {
    for (int i=0; i<n; i++)
        if (s[i]%m!=m-1) return false;
    return true;
}

bool valid_head(
    const state &cur, int n,
    const vector<int> &color, int nx
) {
    for (int i=1; i<n; i++)
        if (cur[i]==nx) return false;
    for (int i=1; i<n; i++)
        if (color[cur[i]]==color[nx]) return false;
    return true;
}

bool valid_tail(
    const state &cur, int n,
    const vector<int> &color, int nx
) {
    for (int i=0; i<n-1; i++)
        if (cur[i]==nx) return false;

    int c=color[nx];
    for (int i=0; i<n-1; i++)
        if (color[cur[i]]==c) return false;
    return true;
}

int run(const vector<string> &g) {
    int n=g.size(), m=g[0].size();
    vector<int> color(n*m);
    for (int r=0; r<n; r++)
        for (int c=0; c<m; c++)
            color[r*m+c]=g[r][c]-'0';
    state s;
    for (int i=0; i<n; i++)
        s[i]=sint(i*m);
    queue<state> q;
    unordered_map<lint, int> dist;
    dist.reserve(1<<20);
    lint skey=encode(s, n);
    dist[skey]=0;
    q.push(s);

    while (!q.empty()) {
        state cur=q.front();
        q.pop();
        lint ckey=encode(cur, n);
        int cd=dist[ckey];
        if (goal(cur, n, m)) return cd;
        int head=cur[n-1];
        int hr=head/m, hc=head%m;
        for (int d=0; d<4; d++) {
            int nr=hr+dr[d], nc=hc+dc[d];
            if (nr<0 || nr>=n || nc<0 || nc>=m) continue;
            int nx=nr*m+nc;
            if (!valid_head(cur, n, color, nx)) continue;
            state nxt;
            for (int i=0; i<n-1; i++)
                nxt[i]=cur[i+1];
            nxt[n-1]=sint(nx);
            lint nkey=encode(nxt,n);
            if (dist.count(nkey)) continue;
            dist[nkey]=cd+1;
            q.push(nxt);
        }

        int tail=cur[0];
        int tr=tail/m, tc=tail%m;
        for (int d=0; d<4; d++) {
            int nr=tr+dr[d], nc=tc+dc[d], nx=nr*m+nc;
            if (nr<0 || nr>=n || nc<0 || nc>=m) continue;
            if (!valid_tail(cur, n, color, nx)) continue;

            state nxt;
            nxt[0]=sint(nx);
            for (int i=1; i<n; i++)
                nxt[i]=cur[i-1];
            lint nkey=encode(nxt,n);
            if (dist.count(nkey)) continue;
            dist[nkey]=cd+1;
            q.push(nxt);
        }
    }
    return -1;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    string s;
    vector<string> board;
    while (getline(cin,s)) {
        if (s=="end") break;
        if (s.empty()) continue;
        board.clear();
        board.push_back(s);
        while (getline(cin, s)) {
            if (s.empty()) break;
            board.push_back(s);
        }
        cout << run(board) << '\n';
    }
}