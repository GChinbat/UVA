#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

vector<int > a, dp, f, parent;

int bin_search(int lo, int hi, int val) {

    while(lo < hi) {
        int mid = (lo + hi) / 2;
        if(val == dp[mid]) return -1;
        if(val < dp[mid]) {
            hi = mid;
        } else {
            lo = mid + 1;
        }  
    }

    return lo;
}

void path(int id) {
    if(id == -1) return ;
    path(parent[id]);
    cout << a[id] << endl;
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    int num;
    while(cin >> num) {
        a.pb(num);
    }
    
    parent.assign(a.size(), -1);   
    dp.pb(a[0]);
    f.pb(0);

    for(int i = 1; i < a.size(); i ++ ) {

        int id = bin_search(0, dp.size(), a[i]);
        if(id == -1) continue;
        if(id == dp.size()) { parent[i] = f[dp.size() - 1]; dp.pb(a[i]); f.pb(i);}
        else {
            parent[i] = id - 1 >= 0 ? f[id - 1] : -1;
            dp[id] = a[i];
            f[id] = i;
        }

    }

    cout << dp.size() << "\n-\n";
    path(f.back());
    return 0;
}