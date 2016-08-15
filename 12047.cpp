#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e9
#define nmax 10001


int n, m, s, t, p;
vector<pair<int, int> > graph[nmax], gg[nmax];
bool vis1[nmax], vis2[nmax];
int dist1[nmax], dist2[nmax];


void dijk1(int s) {

    priority_queue<pair<int, int> > Q;
    dist1[s] = 0;
    Q.push(mp(0, s));
    while(Q.size()) {
        pair<int, int> uu = Q.top();
                            Q.pop();
        int u = uu.second;
        int uw = -uu.first;
        vis1[u] = true;
        if(uw > dist1[u]) continue;
        for(int i = 0; i < graph[u].size(); i++ ) {
            pair<int, int> vv = graph[u][i];
            int v = vv.first;
            int vw = vv.second;
            if(vis1[v]) continue;

            if(dist1[v] > dist1[u] + vw) {
                dist1[v] = dist1[u] + vw;
                Q.push(mp(-dist1[v], v));
            }
        }
    }

}

void dijk2(int s) {

    priority_queue<pair<int, int> > Q;
    dist2[s] = 0;
    Q.push(mp(0, s));
    while(Q.size()) {
        pair<int, int> uu = Q.top();
                            Q.pop();
        int u = uu.second;
        int uw = -uu.first;
        vis2[u] = true;
        if(uw > dist2[u]) continue;
        for(int i = 0; i < gg[u].size(); i++ ) {
            pair<int, int> vv = gg[u][i];
            int v = vv.first;
            int vw = vv.second;
            if(vis2[v]) continue;

            if(dist2[v] > dist2[u] + vw) {
                dist2[v] = dist2[u] + vw;
                Q.push(mp(-dist2[v], v));
            }
        }
    }
    
}

int main() {

   // freopen("in", "r", stdin);

    int T;
    scanf("%d", &T);
    while(T -- ) {
        scanf("%d%d%d%d%d", &n, &m, &s, &t, &p);
        while(m -- ) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            graph[u].pb(mp(v, w));
            gg[v].pb(mp(u, w));
        }

        for(int i = 1; i <= n; i++) {
            dist2[i] = dist1[i] = inf;
            vis1[i] = vis2[i] = false;
        }

        dijk1(s);
        if(dist1[t] > p) {
            puts("-1");
        }else {
            dijk2(t);
            int ans = -inf;
            for(int u = 1; u <= n; u ++ ) {
                for(int i = 0 ; i  < graph[u].size(); i++) {
                    pair<int, int> vv = graph[u][i];
                    int v = vv.first;
                    int vw = vv.second;
                    if(dist1[u] + vw + dist2[v] <= p) {
                        ans = max(ans, vw);
                    }
                }
            }
            printf("%d\n", ans);
        }
        for(int i = 1; i <= n; i++) {
            graph[i].clear();
            gg[i].clear();     
        }
    }

    return 0;
}