#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    int l, k, c;
    cin >> l >> k >> c;
    vector<int> v(k+1);
    for (int i=0; i<k; i++) cin >> v[i];
    v[k]=l;
    ranges::sort(v);
    v.erase(ranges::unique(v).begin(), v.end());

    int left=1, right=l, r=-1, pos=-1;
    while (left<=right) {
        int mid=(left+right)/2, pre=l, cnt=c;
        bool z=true;
        for (int i=k; i>=0; i--) if (pre-v[i]>mid) {
            if (v[i+1]-v[i]>mid) {
                z=false;
                break;
            }
            pre=v[i+1];
            if (--cnt==0) break;
        }
        if (cnt>0) pre=v[0];
        if (pre>mid) z=false;
        if (!z)
            left=mid+1;
        else {
            right=mid-1;
            r=mid, pos=pre;
        }
    }
    cout << r << ' ' << pos << '\n';
}