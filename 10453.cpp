#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int) 1e9

string s;
int dp[1010][1010];

int dfs(int beg, int fin) {

    if(beg >= fin) return 0;
    if(dp[beg][fin] != -1) return dp[beg][fin];
    int ans;
    if(s[beg] == s[fin]) ans = dfs(beg + 1, fin - 1);
    else {
        ans = 1 + min( dfs(beg + 1, fin), dfs(beg, fin - 1));
    }
    return dp[beg][fin] = ans;
} 

vector<vector<char > > pos;
int center;
void dfs1(int beg, int fin) {

    if(beg >= fin) { 
        if(beg == fin) {
            center = beg + 1;
            pos[beg + 1].pb(s[beg]);
        }
        return ;
    }
    if(s[beg] == s[fin]) {
        pos[beg + 1].pb(s[beg]);
        dfs1(beg + 1, fin - 1);
    } else {
        if(dp[beg][fin] == 1 + dfs(beg + 1, fin)) {
            pos[beg + 1].pb(s[beg]);
            dfs1(beg + 1, fin);
        }else {
            pos[beg].pb(s[fin]);
          dfs1(beg, fin - 1);
        }   
    }

}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif 
    ios_base :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while(cin >> s) {
        pos.assign(1002, vector<char > ());
        memset(dp, -1, sizeof dp);
        int way = dfs(0, s.size() - 1);
        dfs1(0, s.size() - 1);
        cout << way << " ";
        center = -1;
        string sbeg = "", sfin = "";
        int length = s.size() + way;
        for(int i = 0; i < s.size() + 2; i ++ ){
            for(int j = 0; j < pos[i].size(); j ++ ){
                sbeg += pos[i][j];
            } 
        }
        if(length % 2 == 1) {
            for(int i = 0; i < sbeg.size() - 1; i ++ ){
                sfin += sbeg[i];
            }
        }else sfin = sbeg;
        reverse(sfin.begin(), sfin.end());
        cout << sbeg << sfin << endl;
    }
    return 0;
}