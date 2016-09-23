#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define ll long long 
#define inf (int)1e9

const int emax = 60006;
const int nmax = 5005;

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

int test, n, s, t, flow;
int x[110], y[110];
int peng[110], jump[110];
float D;
vector<int > parent, dist;

void add(int u, int v, int w) {
    edge[cnt].init(u, v, w, head[u]);
    head[u] = cnt ++;
    edge[cnt].init(v, u, 0, head[v]);
    head[v] = cnt ++;
}

float Dist(int i, int j) {
    return ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}

int in(int i ) {
    return i;
}
int out(int i ) {
    return i + n;
}

void buildGraph(int tt) {
    memset(head, -1, sizeof head);
    t = tt; cnt = 0;
    for(int i = 0; i < n; i ++ ) {  
        add(s, in(i), peng[i]);      
        if(i == t) continue;
       
        add(in(i), out(i), jump[i]);
        
        for(int j = 0; j < n; j ++ ) {
            if(i == j) continue;
            if(Dist(i, j) < D * D) {
                add(out(i), in(j), inf);
            }
        }
    }
}

bool bfs() {
    queue<int > Q;
    parent.assign(s + 2, -1);
    dist.assign(s + 2, -1);
    Q.push(s); dist[s] = 0;

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
    if(s == u) flow = cost;
    else {
        int i = parent[u];
        augment_path(edge[i].u, min(cost, edge[i].w));
        edge[i].w -= flow;
        edge[i ^ 1].w += flow;
    }
}


int solve() {
    int mxflow = 0;

    while(bfs()) {

        for(int i = head[t]; i != -1; i = edge[i].nxt) {
            int j = i ^ 1;
            if(edge[j].w > 0 && dist[edge[j].u] + 1 == dist[t]) {
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

    cin >> test;
    while(test -- ) {
        cin >> n >> D;
        s = n + n;
        int all = 0;
        for(int i = 0; i < n; i ++ ) {
            cin >> x[i] >> y[i] >> peng[i] >> jump[i];
            all += peng[i];
        }
        vector<int > ans;
        for(int i = 0; i < n; i ++) {
            buildGraph(i);
            int res = solve();
            if(res == all) ans.pb(i);
        }
        if(ans.size() == 0) cout << -1 << endl;
        else {
            for(int i = 0; i < ans.size() - 1; i ++) {
                cout << ans[i] << " ";
            } cout << ans.back() << endl;
        }
    }
    return 0;
}

/*

1
5 3.5
1 1 1 1
2 3 0 1
3 5 1 1
5 1 1 1
5 4 0 1

*/