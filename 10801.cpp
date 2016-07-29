#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = (int)a; i <= (int)b; i ++)
#define repd(i, a, b) for(int i = (int)a; i >= (int)b; i --)
#define inf (int)1e9

int n, k;
int T[6];

bool graph[6][111];
int dist[6][111];
bool used[6][111];

int abso(int x) {
    if(x < 0) return -x;
    return x;
}

void solve() {

    memset(dist, -1, sizeof dist);
    memset(used, false, sizeof used);
    
    priority_queue<pair<int, pair<int, int> > > Q;
    rep(s, 0, n - 1) {
        if(graph[s][0]) {
            dist[s][0] = 0;
            Q.push(make_pair(0, make_pair(s, 0)));
        }
    }

    while(Q.size()) {

        pair<int, pair<int, int> > u = Q.top();
                                       Q.pop();

        used[u.second.first][u.second.second] = true;

        if(-u.first > dist[u.second.first][u.second.second]) continue;

        for(int i = 0; i<100; i++) {
            if(i == u.second.second) continue;
            if(!graph[u.second.first][i]) continue;
            if(used[u.second.first][i]) continue;
            if(dist[u.second.first][i] == -1) {
                dist[u.second.first][i] = -u.first + abso(i - u.second.second) * T[u.second.first];
                Q.push(make_pair(-dist[u.second.first][i],make_pair(u.second.first, i)));
            }else if(dist[u.second.first][i] > -u.first + abso(i - u.second.second) * T[u.second.first]) {
                dist[u.second.first][i] = -u.first + abso(i - u.second.second) * T[u.second.first];
                Q.push(make_pair(-dist[u.second.first][i],make_pair(u.second.first, i)));
            }
        }
        
        for(int i = 0; i < n; i++) {
            if(!graph[i][u.second.second]) continue;
            if(u.second.first == i) continue;
            if(used[i][u.second.second]) continue;
            if(dist[i][u.second.second] == -1 || dist[i][u.second.second] > -u.first + 60) {
                  dist[i][u.second.second] = -u.first + 60;   
                  Q.push(make_pair(-dist[i][u.second.second], make_pair(i, u.second.second)));   
            }
        }    
    }
    return ;
}



int main() {


    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif 


    while(cin >> n >> k) {

        rep(i, 0, n - 1) cin >> T[i];
        memset(graph, false, sizeof graph);

        rep(i, 0, n - 1) {
            int u;
            char ch;
            rep(k, 0 , 100) {
                scanf("%d%c", &u, &ch);
                graph[i][u] = true;
                if(ch == '\n') break;
            }
        }
/*
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= k; j++) {
                cout << graph[i][j] << " " ;
            } cout << endl;
        }
*/

        solve();
        int ans = inf;
        rep(i, 0, n - 1) {
            if(dist[i][k] == -1) continue;
            ans = min(dist[i][k], ans); 
        }
        if(ans == inf) cout << "IMPOSSIBLE" << endl;
        else cout << ans << endl;
    

    }

    return 0;
}