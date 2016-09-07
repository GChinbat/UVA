#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

const int nmax = 2505;
int n;
vector<int> graph[nmax], parent;
bool visited[nmax];
int farnode, deep, depth;
int uncox, uncoy, addx, addy;

void dfs(int u) {
    visited[u] = true;
    for(int i = 0; i < graph[u].size(); i ++ ) {
        int v = graph[u][i];
        if((uncoy == u && uncox == v) || (uncox == u && uncoy == v)) continue;
        if(!visited[v]) {
            deep ++;
            parent[v] = u;
            dfs(v);
            if(depth < deep) {
                farnode = v;
                depth = deep;
            }
            deep --;
        }
    }
    if(u == addx) {
        if(visited[addy] == false) {
            deep ++;
            parent[addy] = addx;
            dfs(addy);
            if(depth < deep) {
                farnode = addy;
                depth = deep;
            }
            deep --;
        }
    }
    if(u == addy) {
        if(visited[addx] == false) {
            deep ++;
            parent[addx] = addy;
            dfs(addx);
            if(depth < deep) {
                farnode = addx;
                depth = deep;
            }
            deep --;
        }
    }
    return ;
}

vector<int > D;

void getPath(int v ) {
    if(v == -1) return ;
    D.pb(v);
    getPath(parent[v]);
}    

vector<int > getDiametr(int root) {

    deep = depth = 0;
    farnode = root;
    parent.assign(nmax, -1);
    memset(visited, 0, sizeof visited);
    dfs(root);

    deep = depth = 0;
    parent.assign(nmax, -1);
    memset(visited, 0, sizeof visited);
    dfs(farnode);
    D.clear();
    getPath(farnode);
    
    return D;
}

int calcDist(int sizea, int sizeb) {
    int sizec = (sizea + 1) / 2 + (sizeb + 1) / 2;
    return max(sizeb, max(sizea, sizec));
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    int T;
    cin >> T;
    while(T -- ) {
        cin >> n;
        for(int i = 1; i < n; i ++ ) {
            int u, v;
            cin >> u >> v;
            graph[u].pb(v);
            graph[v].pb(u);
        }
        uncox = uncoy = -1;
        addx = addy = -1;

        vector<int > diam = getDiametr(1);

        int ans = inf;
        int ansi = 0;
        int ansx = 0;
        int ansy = 0;
        for(int i = 1; i < diam.size(); i ++ ) {
            uncoy = diam[i];
            uncox = diam[i - 1];
            addx = -1;
            addy = -1;
            
            vector<int > diam1 = getDiametr(diam[i]);
            vector<int > diam2 = getDiametr(diam[i - 1]);

            addx = diam1[diam1.size() / 2];
            addy = diam2[diam2.size() / 2];
            
            vector<int > res = getDiametr(1);

            if(res.size() < ans) {
                ans = res.size();
                ansi = i;
                ansx = addx;
                ansy = addy;
            }
        }
        cout << ans - 1 << endl;
        cout << diam[ansi] << " " << diam[ansi - 1] << endl;
        cout << ansx << " " << ansy << endl;

        for(int i = 0; i <= n; i ++ ) graph[i].clear();
    }

    return 0;
}