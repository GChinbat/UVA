#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

string a;
int tree[5000005], lazy[5000005];

void build(int beg, int fin, int id) {

    if(beg == fin) {
        tree[id] = a[beg] - '0';
        lazy[id] = -1;
    } else {
        int mid = (beg + fin) / 2;
        build(beg, mid, id * 2);
        build(mid + 1, fin, id * 2 + 1);
        tree[id] = tree[id * 2] + tree[id * 2 + 1];
        lazy[id] = -1;
    }

}

void lazy2(int beg, int fin, int id) {

    if(lazy[id] != -1) {
        if(lazy[id] == 0) {
            tree[id] = 0;
            if(beg != fin) {
                lazy[id * 2] = 0;
                lazy[id * 2 + 1] = 0;
            }
        }
        if(lazy[id] == 1) {
            tree[id] = fin - beg + 1;
            if(beg != fin) {
                lazy[id * 2] = 1;
                lazy[id * 2 + 1] = 1;
            }   
        }
        if(lazy[id] == 2) {
            tree[id] = fin - beg - tree[id] + 1;
            if(beg != fin) {

                if(lazy[id * 2] == -1) lazy[id * 2] = 2;
                else if(lazy[id * 2] == 0) {lazy[id * 2] = 1;}
                else if(lazy[id * 2] == 1) {lazy[id * 2] = 0;}
                else if(lazy[id * 2] == 2) {lazy[id * 2] = -1;}
                
                if(lazy[id * 2 + 1] == -1) lazy[id * 2 + 1] = 2;
                else if(lazy[id * 2 + 1] == 0) {lazy[id * 2 + 1] = 1;}
                else if(lazy[id * 2 + 1] == 1) {lazy[id * 2 + 1] = 0;}
                else if(lazy[id * 2 + 1] == 2) {lazy[id * 2 + 1] = -1;}
                
            }

        }

        lazy[id] = -1;
    }

    return ;
}














void update_one(int beg, int fin, int lo, int hi, int id) {



    lazy2(beg, fin, id);

    if(hi < beg || fin < lo) return ;
    if(lo <= beg && fin <= hi) {
        tree[id] = fin - beg + 1;
        if(beg != fin) {
            lazy[id * 2] = 1;
            lazy[id * 2 + 1] = 1; 
        }
        return ;     
    }
    int mid = (beg + fin) / 2;
    update_one(beg, mid, lo, hi, id * 2);
    update_one(mid + 1, fin, lo, hi, id * 2 + 1);
    tree[id] = tree[id * 2] + tree[id * 2 + 1];

}

void update_zero(int beg, int fin, int lo, int hi, int id) {
    
    lazy2(beg, fin, id);

    if(hi < beg || fin < lo) return ;
    if(lo <= beg && fin <= hi) {
        tree[id] = 0;
        if(beg != fin) {
            lazy[id * 2] = 0;
            lazy[id * 2 + 1] = 0; 
        }    
        return ; 
    }
    int mid = (beg + fin) / 2;
    update_zero(beg, mid, lo, hi, id * 2);
    update_zero(mid + 1, fin, lo, hi, id * 2 + 1);
    tree[id] = tree[id * 2] + tree[id * 2 + 1];

}

void update_two(int beg, int fin, int lo, int hi, int id) {
    
    lazy2(beg, fin, id);

    if(hi < beg || fin < lo) return ;
    if(lo <= beg && fin <= hi) {
        tree[id] = fin - beg + 1 - tree[id];
        if(beg != fin) {
            if(lazy[id * 2] == -1){lazy[id * 2] = 2;}
            else if(lazy[id * 2] == 0) {lazy[id * 2] = 1;}
            else if(lazy[id * 2] == 1) {lazy[id * 2] = 0;}
            else if(lazy[id * 2] == 2) {lazy[id * 2] = -1;}
            
            if(lazy[id * 2 + 1] == -1) lazy[id * 2 + 1] = 2;
            else if(lazy[id * 2 + 1] == 0) {lazy[id * 2 + 1] = 1;}
            else if(lazy[id * 2 + 1] == 1) {lazy[id * 2 + 1] = 0;}
            else if(lazy[id * 2 + 1] == 2) {lazy[id * 2 + 1] = -1;}
            
        } 
        return ;    
    }
    int mid = (beg + fin) / 2;
    update_two(beg, mid, lo, hi, id * 2);
    update_two(mid + 1, fin, lo, hi, id * 2 + 1);
    tree[id] = tree[id * 2] + tree[id * 2 + 1];
    
}


int query(int beg, int fin, int lo, int hi, int id) {
    
    lazy2(beg, fin, id);
     
    if(hi < beg || fin < lo) return 0;
    if(lo <= beg && fin <= hi) {
        return tree[id];
    }

    int mid = (beg + fin) / 2;
    int ab = query(beg, mid, lo, hi, id * 2);
    int ba = query(mid + 1, fin, lo, hi, id * 2 + 1);

    return ab + ba;
}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    int T;
    cin >> T;
    for(int test = 1; test <= T; test ++ ) {
        int m;
        cin >> m;
        a = "";
        while(m -- ) {
            int t;
            string s;
            cin >> t >> s;
            while(t -- ) {
                a += s;
            }   
        }
        int n = a.size();
        build(0, n - 1, 1);
        int Q, too = 0;
        cin >> Q;
        cout << "Case " << test << ":" << endl;
        while(Q -- ) {
            string dir;
            int lo, hi;
            cin >> dir >> lo >> hi;
            if(dir == "F") {
                update_one(0, n - 1, lo, hi, 1);
            }
            if(dir == "I") {
                update_two(0, n - 1, lo, hi, 1);
            }
            if(dir == "E") {    
                update_zero(0, n - 1, lo, hi, 1);
            }
            if(dir == "S") {
               int res = query(0, n - 1, lo, hi, 1);
               cout << "Q" << ++too << ": ";
               cout << res << endl;
            }
         }

    }




    return 0;
}