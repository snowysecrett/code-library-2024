#include "bits/stdc++.h"
using namespace std;
#define int long long
#define double long double
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}
int bm(int b, int p) {
  if(p==0) return 1 % MOD;
  int r = bm(b, p >> 1);
  if(p&1) return (((r*r) % MOD) * b) % MOD;
  return (r*r) % MOD;
}
int inv(int b) { 
  return bm(b, MOD-2);
}
int fastlog(int x) {
  return (x == 0 ? -1 : 64 - __builtin_clzll(x) - 1);
}
void printcase(int i) { cout << "Case #" << i << ": "; }
struct maxcost_maxflow {
  // Best algorithm is SPFA
  struct edge {
    int to, cost, flow, revid; // reverse edge id in adjacency list
  };
  vector<vector<edge> > adj, adj2;
  bool computed = 0;
  int mc, mf;
  int n, s, t;
  public:
  void init(int n_, int s_, int t_) {
    n = n_;
    s = s_;
    t = t_;
    adj.resize(n + 10);
  }
  void addedge(int u, int v, int cost, int flow) {
    int au = adj[u].size();
    int av = adj[v].size();
    adj[u].push_back({v, cost, flow, av});
    adj[v].push_back({u, -cost, 0, au});
  }
  void eval() {
    computed = 1;
    mc = mf = 0;
    while(1) {
      int dist[n+1];
      pair<int, int> pre[n+1];
      bool vis[n+1];
      queue<int> q;
      for(int i=1; i<=n; i++) {
        dist[i] = -1e15;
        vis[i] = 0;
      }
      dist[s] = 0;
      vis[s] = 1;
      q.push(s);
      while(q.size()) {
        int f = q.front();
        q.pop();
        vis[f] = 0;
        int idx = 0;
        for(edge x: adj[f]) {
          if(x.flow > 0 && dist[x.to] < dist[f] + x.cost) {
            dist[x.to] = dist[f] + x.cost;
            pre[x.to] = {f, idx};
            if(!vis[x.to]) {
              q.push(x.to);
              vis[x.to] = 1;
            }
          }
          idx++;
        }
      }
      if(dist[t] <= -5e14) break;

      int e = 1e15; // amount of flow
      int cur = t;
      while(cur != s) {
        int pv = pre[cur].first;
        int bc = pre[cur].second; // pv -> cur
        int lo = adj[pv][bc].revid; // cur -> pv
        e = min(e, adj[pv][bc].flow);
        cur = pv;
      }
      cur = t;
      while(cur != s) {
        int pv = pre[cur].first;
        int bc = pre[cur].second; // pv -> cur
        int lo = adj[pv][bc].revid; // cur -> pv
        adj[pv][bc].flow -= e;
        adj[cur][lo].flow += e;
        cur = pv;
      }
      mc += dist[t] * e;
      mf += e;
    }
  }
  int maxcost() {
    if(!computed) eval();
    return mc;
  }
  int maxflow() {
    if(!computed) eval();
    return mf;
  }
};
void solve(int tc) {
  int a, b;
  cin >> a >> b;
  int p, q;
  cin >> p >> q;
  maxcost_maxflow f;
  f.init((p+1) * (q+1) + 2, (p+1) * (q+1) + 1, (p+1) * (q+1) + 2);
  for(int i=0; i<=p; i++) {
    for(int j=0; j<q; j++) {
      int v;
      cin >> v;
      f.addedge(i*(q+1)+j+1, i*(q+1)+j+2, v, 1);
      f.addedge(i*(q+1)+j+1, i*(q+1)+j+2, 0, MOD);
    }
  }
  for(int i=0; i<=q; i++) {
    for(int j=0; j<p; j++) {
      int v;
      cin >> v;
      f.addedge(j*(q+1)+i+1, (j+1)*(q+1)+i+1, v, 1);
      f.addedge(j*(q+1)+i+1, (j+1)*(q+1)+i+1, 0, MOD);
    }
  }
  for(int i=0; i<a; i++) {
    int k, y, x;
    cin >> k >> x >> y;
    f.addedge((p+1) * (q+1) + 1, x*(q+1)+y+1, 0, k);
  }
  for(int i=0; i<b; i++) {
    int k, y, x;
    cin >> k >> x >> y;
    f.addedge(x*(q+1)+y+1, (p+1) * (q+1) + 2, 0, k);
  }
  cout << f.maxcost() << '\n';
}
int32_t main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}
/*
g++ A.cpp -std=c++17 -O2 -o A
./A < input.txt

*/
