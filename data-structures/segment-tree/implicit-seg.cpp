// Solution to https://atcoder.jp/contests/abc403/tasks/abc403_g
// Implicit segment tree
// Maintaining odd rank sum and even rank sum, doing flips if needed

struct implicit_seg {
  struct node {
    int l, r;
    int lc = -1, rc = -1;
    int odd_sum = 0, even_sum = 0;
    bool lazytag = 0;
  };
  node emptynode;
  vector<node> st;
  void init() {
    st.resize(1);
    st[0].l = 1, st[0].r = 1e9;
  }
  void debug(int idx) {
   // cout << "node " << idx << ": " << st[idx].odd_sum << " " << st[idx].even_sum << " " << st[0].odd_sum << "\n";
  }
  void push_down(int idx) {
    if (!st[idx].lazytag) return;
    st[idx].lazytag = 0;
    if (st[idx].lc != -1) {
      swap(st[st[idx].lc].odd_sum, st[st[idx].lc].even_sum);
      st[st[idx].lc].lazytag ^= 1;
    }
    if (st[idx].rc != -1) {
      swap(st[st[idx].rc].odd_sum, st[st[idx].rc].even_sum);
      st[st[idx].rc].lazytag ^= 1;
    }
  }
  void u(int idx, int tar, bool parity) {
    push_down(idx);
    if(st[idx].l == st[idx].r) {
      if(parity) st[idx].odd_sum += tar;
      else st[idx].even_sum += tar;
      debug(idx);
      return;
    }
    int mid = (st[idx].l + st[idx].r) >> 1;
    if (tar <= mid) {
      if (st[idx].lc == -1) {
        int nxt = st.size();
        st.push_back(emptynode);
        st[idx].lc = nxt;
        st[nxt].l = st[idx].l;
        st[nxt].r = mid;
      }
      u(st[idx].lc, tar, parity);
    }
    else {
      if (st[idx].rc == -1) {
        int nxt = st.size();
        st.push_back(emptynode);
        st[idx].rc = nxt;
        st[nxt].l = mid + 1;
        st[nxt].r = st[idx].r;
      }
      u(st[idx].rc, tar, parity);
    }
    st[idx].odd_sum = 0;
    if (st[idx].lc != -1) st[idx].odd_sum += st[st[idx].lc].odd_sum;
    if (st[idx].rc != -1) st[idx].odd_sum += st[st[idx].rc].odd_sum;
    st[idx].even_sum = 0;
    if (st[idx].lc != -1) st[idx].even_sum += st[st[idx].lc].even_sum;
    if (st[idx].rc != -1) st[idx].even_sum += st[st[idx].rc].even_sum;
    debug(idx);
  }
  void tog(int idx, int l, int r) {
    push_down(idx);
    int constl = st[idx].l, constr = st[idx].r;
    if (l <= constl && constr <= r) {
      swap(st[idx].odd_sum, st[idx].even_sum);
      st[idx].lazytag = 1;
      return;
    }
    int mid = (constl + constr) >> 1;
    if (mid < l || r < constl) {
      if (st[idx].rc != -1) tog(st[idx].rc, l, r);
    }
    else if (constr < l || r < mid + 1) {
      if (st[idx].lc != -1) tog(st[idx].lc, l, r);
    }
    else {
      if (st[idx].lc != -1) tog(st[idx].lc, l, r);
      if (st[idx].rc != -1) tog(st[idx].rc, l, r);
    }
    st[idx].odd_sum = 0;
    if (st[idx].lc != -1) st[idx].odd_sum += st[st[idx].lc].odd_sum;
    if (st[idx].rc != -1) st[idx].odd_sum += st[st[idx].rc].odd_sum;
    st[idx].even_sum = 0;
    if (st[idx].lc != -1) st[idx].even_sum += st[st[idx].lc].even_sum;
    if (st[idx].rc != -1) st[idx].even_sum += st[st[idx].rc].even_sum;
  }
  void update(int i, bool parity) {
    u(0, i, parity);
  }
  void toggle_range(int l, int r) {
    tog(0, l, r);
  }
  int query_odd() {
    return st[0].odd_sum;
  }
};
