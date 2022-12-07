struct bit {
  vector<int> bit;
  int n_;
  void resize(int n) {
    bit.resize(n + 5);
    n_ = n + 5;
  }
  void add(int x, int v) {
    for(;x<n_;x+=x&-x) bit[x] += v;
  }
  int sum(int x) {
    int s=0;
    for(;x;x-=x&-x) s += bit[x];
    return s;
  }
};
