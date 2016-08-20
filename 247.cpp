#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9

int n, m, N;
map<string, int> has;
map<int, string> res;
vector<int > graph[30], gg[30], bag;
bool visited[30];


void dfs(int u ) {
    visited[u] = true;
    for(int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i];
        if(!visited[v]) {
            dfs(v);
        }
    }
    bag.pb(u);
}

vector<vector<int > > ans;

void dfs1(int u ) {
    visited[u] = true;
    ans.back().pb(u);
    for(int i = 0; i < gg[u].size(); i++) {
        int v = gg[u][i];
        if(!visited[v]) {
            dfs1(v);
        }
    }
}

int main() {

    #ifndef ONLINE_JUDGE 
        freopen("in", "r", stdin);
    #endif 

    int test = 0;
    while(cin >> n >> m) {
        
        if(n == 0 && m == 0) break;
        N = 0;
        has.clear();
        res.clear();

        while(m -- ) {
            string su, sv;
            cin >> su >> sv;
            if(has[su] == 0) has[su] = ++ N, res[N] = su;
            if(has[sv] == 0) has[sv] = ++ N, res[N] = sv;
            graph[has[su]].pb(has[sv]);
            gg[has[sv]].pb(has[su]);
        }

        memset(visited, 0, sizeof visited);
        for(int i = 1; i <= n; i++) {
            if(!visited[i]) {
                dfs(i);
            }
        }
        memset(visited, 0, sizeof visited);
        while(bag.size()) {
            int u = bag.back();
                    bag.pop_back();
            if(!visited[u]) {
                ans.pb(vector<int>());
                dfs1(u);
            }
        }
        if(test != 0) printf("\n");
        printf("Calling circles for data set %d:\n", ++ test);

        for(int i = 0; i < ans.size(); i++ ) {
            for(int j = 0; j < ans[i].size() - 1; j ++ ) {
                cout << res[ans[i][j]] << ", ";
            } cout <<res[ans[i].back()]<< endl;
        }

        ans.clear();
        for(int i = 1; i <= n;  i++) {
            graph[i].clear();
            gg[i].clear();
            bag.clear();
        }

    }

    return 0;
}