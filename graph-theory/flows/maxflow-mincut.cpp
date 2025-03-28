struct maxflow_graph { //2025.03.28
  int n, s, t;
  vector<vector<pair<int, int> > > adj;
  vector<vector<int> > comp;
  vector<int> dist;
  const int maxedgeflow = 3e9; // max flow for a single edge
  map<pair<int,int>, int> exist;
  vector<pair<pair<int,int>, int>> inits;
  void init(int n_, int s_, int t_) {
    n = n_, s = s_, t = t_; // node count, source node, sink node
    adj.resize(n + 5);
    dist.resize(n + 5);
    comp.resize(n + 5);
  }
  void addedge(int u, int v, int f) {
    inits.push_back({{u, v}, f});
    // adding a single direction edge u->v with flow f
    int us = adj[u].size(), vs = adj[v].size();
    if(exist.count({u, v})) {
      int uid = exist[{u, v}];
      adj[u][uid].second += f;
    }
    else {
      exist[{u, v}] = us;
      adj[u].push_back({v, f});
      comp[u].push_back(vs);
    }
    if(!exist.count({v, u})) {
      exist[{v, u}] = vs;
      adj[v].push_back({u, 0});
      comp[v].push_back(us);
    }
  }
  int dfs(int node, int flow) {
    if(node == t || flow <= 0) return max(0ll, flow);
    int bruh = 0;
    for(int i=0; i<adj[node].size(); i++) {
      if(dist[adj[node][i].first] == dist[node] + 1 && adj[node][i].second > 0) {
        int dd = dfs(adj[node][i].first, min(flow, adj[node][i].second));
        if(dd > 0) {
          flow -= dd;
          bruh += dd;
          adj[node][i].second -= dd;
          adj[adj[node][i].first][comp[node][i]].second += dd;
          if(flow <= 0) return bruh;
        }
      }
    }
    return bruh;
  }
  bool called = 0;
  int maxflow() {
    called = 1;
    bool vis[n+1];
    for(int i=0; i<=n; i++) vis[i] = 0;
    for(int i=0; i<=n; i++) dist[i] = 1e9;
    dist[s] = 0;
    queue<int> lv;
    lv.push(s);
    while(lv.size()) {
      int f = lv.front(); lv.pop();
      if(!vis[f]) {
        vis[f] = 1;
        for(pair<int, int> x: adj[f]) {
          if(!vis[x.first] && dist[x.first] > dist[f] + 1 && x.second > 0) {
            dist[x.first] = dist[f] + 1;
            lv.push(x.first);
          }
        }
      }
    }
    if(dist[t] == 1e9) return 0;
    int answer = 0;
    while(1) {
      int d = dfs(s, maxedgeflow);
      if(!d) break;
      answer += d;
    }
    if(answer == 0) return 0;
    return answer + maxflow();
  }
  vector<pair<pair<int, int>,int>> mincut() {
    if(!called) maxflow();
    vector<pair<pair<int, int>,int>> mincut_edges;
    bool vis[n+1];
    for(int i=1; i<=n; i++) vis[i] = 0;
    queue<int> q;
    q.push(s);
    while(q.size()) {
      int f = q.front();
      q.pop();
      if(!vis[f]) {
        vis[f] = 1;
        for(pair<int, int> x: adj[f]) {
          if(x.second > 0) q.push(x.first);
          else {
            pair<pair<int, int>, int> tar = {{f, x.first}, x.second};
            for(auto x: inits) {
              if(x == tar) {
                mincut_edges.push_back(tar);
              }
            }
          }
        }
      }
    }
    return mincut_edges;
  }
};
