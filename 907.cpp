#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

int n, k, a[606];

int dp[303][606];

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    ios_base :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    while(cin >> n >> k) {
        n ++ ;
        for(int i = 1; i <= n; i ++ ){
            cin >> a[i];
        }
        memset(dp, 0, sizeof dp);
        for(int ni = 1; ni <= n; ni ++ ) {
            dp[0][ni] = dp[0][ni - 1] + a[ni];
        }
        for(int ki = 1; ki <= k; ki ++ ){
            for(int ni = 1; ni <= n; ni ++ ){
                dp[ki][ni] = inf;
                for(int i = 1; i <= ni; i ++ ){
                    dp[ki][ni] = min(dp[ki][ni], max(dp[ki - 1][i], dp[0][ni] - dp[0][i]));
                }
            }
        }
        cout << dp[k][n] << endl;
    }


    return 0;
}