#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

int n, energy[110];
vector<int > graph[110];

bool visited[110];
void dfs(int u) {
    visited[u] = true;
    for(int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if(!visited[v]) dfs(v);
    }
}


bool solve() {

    vector<int > dist(n + 1, -inf);
    dist[1] = 100;

    for(int it = 1; it < n; it ++) {
        for(int u = 1; u <=n; u++) {
            for(int i = 0; i < graph[u].size(); i ++) {
                int v= graph[u][i];
                if(dist[u] > 0 && dist[u] + energy[v] > 0 && dist[u] + energy[v] > dist[v]) {
                    dist[v] = dist[u] + energy[v];
                }
            }
        }
    }
    //cout << dist[n] << endl;
    if(dist[n] > 0) return true;

    for(int u = 1; u <=n; u++) {
        for(int i = 0; i < graph[u].size(); i ++) {
            int v= graph[u][i];
            if(dist[u] != -inf && dist[u] + energy[v] > 0 && dist[u] + energy[v] > dist[v]) {
                memset(visited, 0, sizeof visited);
                dfs(v);
                if(visited[n]) return true; 
            }
        }
    }
    return false;
}

string ans[2] = {"hopeless", "winnable"};

int main() {

    #ifndef ONLINE_JUDGE 
        freopen("in", "r", stdin);
    #endif

    while(1) {
        cin >> n;
        if(n == -1) break;
        for(int u = 1; u <=n ; u ++) {
            cin >> energy[u];
            int m, v;
            cin >> m;
            while(m -- ) {
                cin >> v;
                graph[u].pb(v);
               // graph[v].pb(u);
            }
        }

        bool res = solve();
        cout << ans[res] << endl;
        for(int i = 0; i <=n ; i++) graph[i].clear();
    }




    return 0;
}