struct stbiao_basic {
  vector<vector<int> > st;
  bool is_min = false;
  bool is_max = false;
  vector<int> b;
  int n;
  int opr(int x, int y) {
    if(is_min) return (b[x] < b[y] ? x : y);
    if(is_max) return (b[x] > b[y] ? x : y);
    cout << "oh no 1: stbiao_basic operation not set correctly\n";
    return 1226;
  }
  public:
  int query_val(int l, int r) {
    int k = 32 - __builtin_clz(r-l+1) - 1;
    return b[opr(st[k][l], st[k][r-(1<<k)+1])];
  }
  int query_idx(int l, int r) {
    int k = 32 - __builtin_clz(r-l+1) - 1;
    return opr(st[k][l], st[k][r-(1<<k)+1]);
  }
  void build(vector<int> v) {
    b = v;
    n = v.size();
    st.resize(fastlog(n) +2);
    for(int i=0; i<fastlog(n)+2; i++) st[i].resize(n);

    for(int i=0; i<n; i++) st[0][i] = i;
    for(int i=1; i<=fastlog(n)+1; i++) {
      for(int j=0; j<n; j++) {
        if(j+(1<<i)-1 < n) st[i][j] = opr(st[i-1][j], st[i-1][j+(1<<(i-1))]);
      }
    }
  }
  void set_operation(string str) {
    is_min = is_max = false;
    if(str == "min") is_min = true;
    else if(str == "max") is_max = true;
    else cout << "oh no 1: stbiao_basic operation not set correctly\n"; // invalid operation
  }
};
