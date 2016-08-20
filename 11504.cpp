#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9
const int nmax = (int)1e5 + 10;
int n, m;
vector<vector<int> > graph, gg;
int visited[nmax];
vector<int > bag;
int indeg[nmax];

void dfs(int u ) {
    visited[u] = true;
    for(int i = 0; i < graph[u].size(); i++ ) {
        int v = graph[u][i];
        if(!visited[v]) {
            dfs(v);
        }
    }
    bag.pb(u);
}

bool ok;

void dfs1(int u, int flag) {
    visited[u] = flag;
    for(int i = 0; i < gg[u].size(); i ++ ) {
        int v = gg[u][i];
        if(visited[v] == 0) {
            dfs1(v, flag);
        }else if(visited[v] != flag) {
            ok = false;
        }
    }
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    int T;
    cin >> T;
    while(T -- ) {
        cin >> n >> m;
        graph.assign(n + 1, vector<int > ());
        gg.assign(n + 1, vector<int > ());
        memset(indeg, 0, sizeof indeg);

        while(m -- ) {
            int u, v;
            cin >> u >> v;
            graph[u].pb(v);
            indeg[v] ++;
            gg[v].pb(u);
        }   
        memset(visited, 0, sizeof visited);
        for(int u = 1; u <= n; u ++) { 
            if(!visited[u]) {
                dfs(u);
            }
        }
        int ans = 0;
        int tool = 0;
        memset(visited, 0, sizeof visited);
        while(bag.size()) {
            int u = bag.back();
                    bag.pop_back();
            if(!visited[u]) {
                ++tool;
                ok = true;
                dfs1(u, tool);
                ans += ok;
            }
        }
        cout << ans << endl;
    }

    return 0;
}