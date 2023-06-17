struct dsu {
  vector<int> dsu,sizes;
  public:
  void resize(int n) {
    sizes.resize(n + 5);
    dsu.resize(n + 5);
    for(int i=0; i<n+5; i++) dsu[i] = i, sizes[i] = 1;
  }
  int set_of(int u) {
    if(dsu[u] == u) return u;
    return dsu[u] = set_of(dsu[u]);
  }
  void union_(int u, int v) {
    int su = set_of(u), sv = set_of(v);
    if(su == sv) return;
    int ss = sizes[su] + sizes[sv];
    dsu[set_of(u)] = set_of(v);
    sizes[set_of(u)] = ss;
  }
  void merge(int u, int v) {
    union_(u, v);
  }
  int size_of(int u) {
    return sizes[set_of(u)];
  }
};
