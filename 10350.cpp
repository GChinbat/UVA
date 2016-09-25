#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9


int n, m;
int node[200][20], dp[5005];
vector<pair<int, int > > graph[5005];
bool vis[5005];
void dfs(int u ) {
    vis[u] = true;
    if(graph[u].size() == 0) {dp[u] = 0; return ;}
    dp[u] = inf;
    for(int i = 0; i < graph[u].size(); i ++ ){
        pair<int, int> v = graph[u][i]; 
        if(!vis[v.first]) {
            dfs(v.first);
        }
        dp[u] = min(dp[u], dp[v.first] + v.second);
    }
}


int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    ios_base :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string name;
    while(cin >> name) {
        
        cin >> n >> m;
        int tt, cnt = 0;

        for(int k = 0; k <= n - 1; k ++ ){
            for(int i = 1; i <= m; i ++ ){
                node[k][i] = ++cnt;
                if(k == 0) graph[0].pb(mp(node[k][i], 0));
            }
        }

        for(int k = 0; k < n - 1; k ++ ){
            for(int i = 1; i <= m; i ++ ){
                for(int j = 1; j <= m; j ++ ){
                    cin >> tt;
                    graph[node[k][i]].pb(mp(node[k + 1][j], tt + 2));                    
                }
            }
        }

        memset(vis, 0, sizeof vis);
        dfs(0);
        cout << name << endl;
        cout << dp[0] << endl;
        for(int i = 0; i <= cnt; i ++ ) graph[i].resize(0);
    }
    return 0;
}