#include <bits/stdc++.h>
using namespace std;
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int64_t n, w, no=0, r=0;
    cin >> n;
    deque<int64_t> que;
    for (int i=0; i<n; i++) {
        cin >> w;
        que.push_back(w);
    }
 
    for (int i=0; i<n; i++) {
        if (que.front()) break;
        que.push_back(que.front());
        que.pop_front();
    }
 
    bool z=1;
    for (int i=0; i<n; i++) {
        w=que[i];
        if (w==0) {
            no++;
            continue;
        }
        z=0;
        r+=(no+1)/2+w;
        no=0;
    }
    if (z)
        r+=no/2;
    else r+=(no+1)/2;
    cout << r;
}