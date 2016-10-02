#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9


int n, k, tree[505005];
int a[100010];

void build(int beg, int fin, int id) {

    if(beg == fin) {
        int val = 0;
        if(a[beg] < 0) val = -1;
        else if(a[beg] > 0) val = 1; 
        tree[id] = val;
        return ;
    }

    int mid = (beg + fin) / 2;

    build(beg, mid, id * 2);
    build(mid + 1, fin , id * 2 + 1);

    tree[id] = tree[id * 2] * tree[id * 2 + 1];
    return ;
}

int query(int beg, int fin, int lo, int hi, int id) {

    if(hi < beg || fin < lo) return 1; 

    if(lo <= beg && fin <= hi) {
        return tree[id];
    }

    int mid = (beg + fin) / 2;
    int va = query(beg, mid, lo, hi, id * 2);
    int vb = query(mid + 1, fin, lo, hi, id * 2 + 1);

    return va * vb;
}


void update(int beg, int fin, int pos, int id) {

    if(pos < beg || fin < pos) return ; 

    if(pos <= beg && fin <= pos) {
        
        int val = 0;
        if(a[pos] > 0) val = 1;
        else if(a[pos] < 0) val = -1;
        tree[id] = val;
        return ;
    }

    int mid = (beg + fin) / 2;
    update(beg, mid, pos, id * 2);
    update(mid + 1, fin, pos, id * 2 + 1);
    tree[id] = tree[id * 2] * tree[id * 2 + 1];
    return ;
}



int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif 


    while(cin >> n >> k) {
        for(int i = 0; i < n; i ++ ) {
            cin >> a[i];
        }
        build(0, n - 1, 1);
        string s;
        int lo, hi, pos, val;
        string ans = "";
        while(k -- ) {
            cin >> s;
            if(s == "P") {
                cin >> lo >> hi;
                lo --; hi --;
                int res = query(0, n - 1, lo, hi, 1);
                if(res > 0) ans += "+";
                if(res < 0) ans += "-";
                if(res == 0) ans += "0";
            }else {
                cin >> pos >> val;
                pos -- ;
                a[pos] = val;
                update(0, n - 1, pos, 1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}