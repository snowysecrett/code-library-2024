struct linear_basis {
  static const int d = 31;
  bitset<d> basis[d] = {};
  bool have[d] = {};
  int wow = 0;
  int count() { // number of ways to represent each element
    return bm(2, wow);
  }
  void init() {
    for(int i=0; i<d; i++) {
      have[i] = 0;
      basis[i] = 0;
      wow = 0;
    }
  }
  void insert(bitset<d> bs) {
    for(int i=d-1; i>=0; i--) {
      if(bs[i]) {
        if(have[i]) bs ^= basis[i];
        else {
          have[i] = 1;
          basis[i] = bs;
          return;
        }
      }
    }
    wow++;
  }
  bool check(bitset<d> bs) {
    for(int i=d-1; i>=0; i--) {
      if(bs[i]) {
        if(have[i]) bs ^= basis[i];
        else {
          return 0;
        }
      }
    }
    return 1;
  }
  bitset<d> max(char op) {
    bitset<d> ans(0);
    for(int i=d-1; i>=0; i--) {
      if(have[i] && ans[i] == 0) ans ^= basis[i];
    }
    return ans;
  }
  void insert(unsigned long long x) {
    bitset<d> bs(x);
    insert(bs);
  }
  bool check(unsigned long long x) {
    bitset<d> bs(x);
    return check(bs);
  }
  unsigned long long max() {
    bitset<d> bruh = max('!');
    return bruh.to_ullong();
  }
};
