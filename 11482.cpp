#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

vector< string > grid;
int n, m;

void slash(int x, int y, int fin) {
    if(x == fin - 1) return ;
    slash(x - 1, y + 1, fin);
    grid[x][y] = '/';
}

void backslash(int x, int y, int fin) {
    if(x == fin - 1) return ;
    backslash(x - 1, y - 1, fin);
    grid[x][y] = '\\';
}

void floors(int x, int y, int fin) {
     
     if(x == fin - 1) return ;
     floors(x - m, y + m, fin); 
     for(int i = y; i <= y + (m - 1) * 2 - 1; i ++ ){
        grid[x][i] = '_';
     }
}

// m = size
// n = level

int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif
    int test = 0;
    while(cin >> m >> n) {
        if(n == 0 && m == 0) break;
        string s = "";
        for(int i = 1; i <= m * 2 * n; i ++ ){
            s += " ";
            if(i > n * m) grid.pb(s);
        }

        for(int i = 0; i < n; i ++ ) {
            slash(n * m - 1, i * m * 2, i * m);
        }
        for(int i = 1; i <= n; i ++ ) {
            backslash(n * m - 1, i * m * 2 - 1, (n - i) * m);
        }

        for(int i = 0; i < n; i ++ ) {
            floors(n * m - 1, i * m * 2 + 1,  i * m);
        }

        cout << "Triangular Museum " << ++test << endl;
        for(int i = 0; i < grid.size(); i ++ ){
            cout << grid[i] << endl;
        }
        grid.resize(0);
        cout << endl;
    }
    return 0;
}