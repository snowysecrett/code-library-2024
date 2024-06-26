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
