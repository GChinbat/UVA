#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long
#define inf (int)1e5

const int nmax = 5005;
const int emax = 60006;

struct Edge {
    int u, v, w, nxt;
    void init(int u, int v, int w, int nxt) {
        this -> u = u;
        this -> v = v;
        this -> w = w;
        this -> nxt = nxt;
    }
} edge[emax];
int head[nmax], cnt;

void add(int u, int v, int w) {
    edge[cnt].init(u, v, w, head[u]);
    head[u] = cnt ++;
    edge[cnt].init(v, u, 0, head[v]);
    head[v] = cnt ++;
}

int n, m, p, s, t, flow;
vector<int > parent, dist;
string ss[40];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int a[40][40];
    
int in(int x, int y) {
    return a[x][y];
}
int out(int x, int y) {
    return a[x][y] + a[n - 1][m - 1];
}

bool bfs() {

    queue<int > Q;
    parent.assign(t + 1, - 1);
    dist.assign(t + 1, - 1);
    Q.push(s);
    dist[s] = 0;

    while(Q.size()) {
        int u = Q.front(); Q.pop();
        if(u == t) break;
        for(int i = head[u]; i != -1; i = edge[i].nxt) {
            int v = edge[i].v;
            if(dist[v] == -1 && edge[i].w > 0) {
                dist[v] = dist[u] + 1;
                parent[v] = i;
                Q.push(v);
            }
        }
    }

    return dist[t] != -1;
}

void augment_path(int u, int cost) {
    if(u == s) flow = cost;
    else {
        int i = parent[u];
        augment_path(edge[i].u, min(edge[i].w, cost));
        edge[i].w -= flow;
        edge[i ^ 1].w += flow;
    }
}

int solve() {

    int mxflow = 0;
    while(bfs()) {

        for(int i = head[t]; i != -1; i = edge[i].nxt) {
            int j = i ^ 1;
            if(edge[j].w > 0 && dist[t] == dist[edge[j].u] + 1) {
                flow = 0;
                augment_path(edge[j].u, edge[j].w);
                edge[j].w -= flow;
                edge[i].w += flow;
                mxflow += flow;
            }  
        }
    }
    return mxflow;
}

int main() {

    #ifndef ONLINE_JUDGE
        freopen("in", "r", stdin);
    #endif
    ios_base :: sync_with_stdio(false);
    cin.tie(0); cout.tie(0); 
    
    while(cin >> n >> m >> p) {
        
        memset(head, -1, sizeof head);
        cnt = 0;


        for(int i = 0; i < n; i ++ ) {
            cin >> ss[i];
        }
        
        int too = 0;
        for(int i = 0; i < n ; i ++ ) {
            for(int j = 0; j < m; j ++ ) {
                a[i][j] = ++ too;
            }
        }

        s = 0; t = too + too + 1;
        for(int i = 0; i < n ; i ++ ) {
            for(int j = 0; j < m; j ++ ) {
                int x = i; int y = j;
                if(ss[x][y] == '~') continue;
                for(int k = 0; k < 4; k ++ ) {
                    int xx = x + dx[k];
                    int yy = y + dy[k];
                    if(xx < 0 || yy < 0 || xx >= n || yy >= m) continue;
                    if(ss[xx][yy] == '~') continue;
                    add(out(x, y), in(xx, yy), inf);
                }

                if(ss[x][y] == '.') add(in(x, y), out(x, y), 1);
                if(ss[x][y] == '@') add(in(x, y), out(x, y), inf);
                if(ss[x][y] == '#') add(in(x, y), out(x, y), inf), add(out(x, y), t, p);
                if(ss[x][y] == '*') add(in(x, y), out(x, y), 1), add(s, in(x, y), 1); 
            }
        }
        
        int res = solve();
        cout << res << endl;
        
    }

    return 0;
}