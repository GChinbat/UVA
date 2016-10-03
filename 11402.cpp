#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

string a;
int tree[5000005], lazy[5000005], n;

void build(int beg, int fin, int id) {

    if(beg == fin) {
        tree[id] = a[beg] - '0';
        lazy[id] = -1;
        return ;
    }

    int mid = (beg + fin) / 2;
    build(beg, mid, id * 2);
    build(mid + 1, fin, id * 2 + 1);
    tree[id] = tree[id * 2] + tree[id * 2 + 1]; 
    lazy[id] = -1;

    return ;
}
    
void update(int beg, int fin, int lo, int hi, int id, int kee) {

    if(lazy[id] != -1) {
        if(lazy[id] == 0) {
            tree[id] = 0;
            if(beg < fin) {
                lazy[id * 2 + 1] = lazy[id * 2] = 0;
            }
        }
        if(lazy[id] == 1) {
            tree[id] = fin - beg + 1;
            if(beg < fin) {
                lazy[id * 2+ 1] = lazy[id * 2] = 1;
            }
        }
        if(lazy[id] == 2) {
            tree[id] = fin - beg - tree[id] + 1;
            if(beg < fin) {
                if(lazy[id * 2] == -1) lazy[id * 2] = 2;
                else if(lazy[id * 2] == 0)   lazy[id * 2] = 1;
                else if(lazy[id * 2] == 1)   lazy[id * 2] = 0;
                else if(lazy[id * 2] == 2)   lazy[id * 2] = -1;

                if(lazy[id * 2 + 1] == -1) lazy[id * 2 + 1] = 2;
                else if(lazy[id * 2 + 1] == 0)   lazy[id * 2 + 1] = 1;
                else if(lazy[id * 2 + 1] == 1)   lazy[id * 2 + 1] = 0;
                else if(lazy[id * 2 + 1] == 2)   lazy[id * 2 + 1] = -1;
            }
        }
        lazy[id] = -1;
    }

    if(hi < beg || fin < lo) return ;
    
    if(lo <= beg && fin <= hi) {
         if(kee == 0) {
            tree[id] = 0;
            if(beg < fin) {
                lazy[id * 2] = lazy[id * 2 + 1] = 0;
            }
         }
         if(kee == 1) {
            tree[id] = fin - beg + 1;
            if(beg < fin) {
                lazy[id * 2] = lazy[id * 2 + 1] = 1;
            }
         }
         if(kee == 2) {
            tree[id] = fin - beg - tree[id] + 1;
            if(beg < fin) {
                if(lazy[id * 2] == -1) lazy[id * 2] = 2;
                else if(lazy[id * 2] == 0) lazy[id * 2] = 1;
                else if(lazy[id * 2] == 1) lazy[id * 2] = 0;
                else if(lazy[id * 2] == 2) lazy[id * 2] = -1;
                if(lazy[id * 2 + 1] == -1) lazy[id * 2 + 1] = 2;
                else if(lazy[id * 2 + 1] == 0) lazy[id * 2 + 1] = 1;
                else if(lazy[id * 2 + 1] == 1) lazy[id * 2 + 1] = 0;
                else if(lazy[id * 2 + 1] == 2) lazy[id * 2 + 1] = -1;
            }
         }
         return ;
    }

    
    int mid = (beg + fin) / 2;
    update(beg, mid, lo, hi, id * 2, kee);
    update(mid + 1, fin, lo, hi, id * 2 + 1, kee);
    tree[id] = tree[id * 2] + tree[id * 2 + 1];
    return ;
}

int query(int beg, int fin, int lo, int hi, int id) {

   if(lazy[id] != -1) {
        if(lazy[id] == 0) {
            tree[id] = 0;
            if(beg < fin) {
                lazy[id * 2 + 1] = lazy[id * 2] = 0;
            }
        }
        if(lazy[id] == 1) {
            tree[id] = fin - beg + 1;
            if(beg < fin) {
                lazy[id * 2 + 1] = lazy[id * 2] = 1;
            }
        }
        if(lazy[id] == 2) {
            tree[id] = fin - beg - tree[id] + 1;
            if(beg < fin) {
                if(lazy[id * 2] == -1) lazy[id * 2] = 2;
                else if(lazy[id * 2] == 0)   lazy[id * 2] = 1;
                else if(lazy[id * 2] == 1)   lazy[id * 2] = 0;
                else if(lazy[id * 2] == 2)   lazy[id * 2] = -1;

                if(lazy[id * 2 + 1] == -1) lazy[id * 2 + 1] = 2;
                else if(lazy[id * 2 + 1] == 0)   lazy[id * 2 + 1] = 1;
                else if(lazy[id * 2 + 1] == 1)   lazy[id * 2 + 1] = 0;
                else if(lazy[id * 2 + 1] == 2)   lazy[id * 2 + 1] = -1;
            }
        }
        lazy[id] = -1;
    }

    if(beg > hi || fin < lo) return 0;
    if(lo <= beg && fin <= hi) return tree[id];
    int mid = (beg + fin) / 2;

    int aq = query(beg, mid, lo, hi, id * 2);
    int bq = query(mid + 1, fin, lo, hi, id * 2 + 1);

    return aq + bq;
}


int main() {


    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    int T;
    cin >> T;
    for(int test = 1; test <= T; test ++ ) {
        cout << "Case " << test << ":" << endl;
        a = "";
        int m;
        cin >> m;
        for(int k = 0; k < m; k ++ ) {
            int t; string s;
            cin >> t >> s;
            for(int j = 0; j < t; j ++ ) {
                a += s;
            }
        } 
        n = a.size();
        build(0, n - 1, 1);

        int Q, god = 0;
        cin >> Q;

        while(Q -- ) {
            string s;
            int u, v;
            cin >> s >> u >> v;

            if(s == "E") update(0, n - 1, u, v, 1, 0);
            if(s == "F") update(0, n - 1, u, v, 1, 1);
            if(s == "I") update(0, n - 1, u, v, 1, 2);
            if(s == "S") {
                int res = query(0, n - 1, u, v, 1);
                cout << "Q" << ++god << ": " << res << endl;
            }

        }
    }

    return 0;
}