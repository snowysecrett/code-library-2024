struct dsu {
  vector<int> dsu;
  public:
  void resize(int n) {
    dsu.resize(n + 5);
    for(int i=0; i<n+5; i++) dsu[i] = i;
  }
  int set_of(int u) {
    if(dsu[u] == u) return u;
    return dsu[u] = set_of(dsu[u]);
  }
  void union_(int u, int v) {
    dsu[set_of(u)] = set_of(v);
  }
};
