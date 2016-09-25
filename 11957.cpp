#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9
#define mod 1000007

int dp[110][110];
int n;

int solve() {

    for(int row = n - 1; row >= 1; row -- ){
        for(int col = 1; col <= n; col ++ ){
            if(dp[row][col] == -1) continue;
            if(dp[row + 1][col - 1] != -1) {
                dp[row][col] += dp[row + 1][col - 1];
                dp[row][col] %= mod;
            }else if(dp[row + 2][col - 2] != -1) {
                dp[row][col] += dp[row + 2][col - 2];
                dp[row][col] %= mod;
            }
            if(dp[row + 1][col + 1] != -1) {
                dp[row][col] += dp[row + 1][col + 1];
                dp[row][col] %= mod;
            }else if(dp[row + 2][col + 2] != -1) {
                dp[row][col] += dp[row + 2][col + 2];
                dp[row][col] %= mod;
            }
        
        }
    }
    int ans = 0;
    for(int col = 1; col <= n; col ++ ){
        if(dp[1][col] > 0) {
            ans += dp[1][col];
            ans %= mod;
        }
    }
    return ans;
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    ios_base :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T;
    string s;
    cin >> T;
    for(int test = 1; test <= T; test ++ ) { 
        cin >> n;
        memset(dp, 0, sizeof dp);
        for(int i = 0; i < n; i ++ ) {
            cin >> s;
            for(int j = 0; j < n; j ++ ){ 
                if(s[j] == '.') dp[i + 1][j + 1] = 0;
                if(s[j] == 'B') dp[i + 1][j + 1] = -1;
                if(s[j] == 'W') dp[i + 1][j + 1] = 1;
            }
        }
        int res = solve();

        cout << "Case " << test << ": " << res << endl;

    }
    
    return 0;
}