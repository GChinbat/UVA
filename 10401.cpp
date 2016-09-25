#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9


vector<int > add(vector<int > a, vector<int > b) {

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int > c;

    int sansan = 0;
    for(int i = 0; i < min(a.size(), b.size()); i ++ ){
        int num = a[i] + b[i] + sansan;
        c.pb(num % 10);
        sansan = num / 10;
    }
    if(a.size() > b.size()) {
        for(int i = b.size(); i < a.size(); i ++ ){
            int num = a[i] + sansan;
            c.pb(num % 10);
            sansan = num / 10;
        }
    }else {
        for(int i = a.size(); i < b.size(); i ++ ){
            int num = b[i] + sansan;
            c.pb(num % 10);
            sansan = num / 10;
        }
    }
    if(sansan == 1) {
        c.pb(1);
    }
    reverse(c.begin(), c.end());

    return c;
}

int has[20];
int n;
bool convert(string s) {
    n = s.size();
    memset(has, 0, sizeof has);

    for(int i = 0; i < s.size(); i ++ ){
        if(s[i] != '?') {
            
            if(s[i] >= 'A') {
                has[i + 1] = s[i] - 'A' + 10;
            }  else {
                has[i + 1] = s[i] - '0'; 
            }
        }
    }

    for(int i = 2; i <= n; i ++ ){
        if(has[i - 1] == 0) continue;
        if(has[i] == 0) continue;
       int dif =  abs(has[i] - has[i - 1]);
       if(dif < 2) return false;
    }
    return true;
}

vector<int > dp[20][20];

void solve() {
    
    for(int i = 0; i < 20; i ++ ){
        for(int j = 0; j < 20; j ++ ){
            dp[i][j].resize(0);
            dp[i][j].pb(0);
        }
    }

    if(has[1] == 0) {
        for(int row = 1; row <= n; row ++ ) {
            dp[row][1].resize(0);
            dp[row][1].pb(1);
        }
    }else {
        dp[has[1]][1].resize(0);
        dp[has[1]][1].pb(1);
    }

    for(int col = 2; col <= n; col ++ ){

        if(has[col] == 0) {
            for(int row = 1; row <= n; row ++ ){
                for(int r = 1; r <= n; r ++ ){
                    if(r == row || r == row + 1 || row -1 == r) continue;
                    dp[row][col] = add(dp[row][col], dp[r][col - 1]);      
                }
            }
        } else {
            int row = has[col];
            for(int r = 1; r <= n; r ++ ){
                    if(r == row || r == row + 1 || row -1 == r) continue;
                    dp[row][col] = add(dp[row][col], dp[r][col - 1]); 
            }
        }
    }

    vector<int > ans;
    ans.pb(0);
    for(int row = 1; row <= n; row ++ ){
        ans = add(ans, dp[row][n]);
    }

    for(int i = 0; i < ans.size(); i ++ ){
        cout << ans[i];
    } cout << endl;
}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif
    ios_base :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string s;
    while(cin >> s) {
        bool ok = convert(s);
        if(ok) solve();
        else {
            cout << "0" << endl;
        }
    }

    return 0;
}


