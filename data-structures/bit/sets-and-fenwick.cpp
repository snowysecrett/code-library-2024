// https://oj.uz/submission/985999
// 1066 ms on n, m ≤ 10^5 with HLD

struct sets_and_fenwick {
  int n, m; // n = ARRAY SIZE, m = MAX ELEMENT
  vector<int> bit;
  set< pair<pair<int,int>,int> > st;
  const int base = 1;
  const int oob = -1;
  void add(int x, int v) {
    x++;
    for(;x<m+5;x+=x&-x) bit[x] += v;
  }
  int sum(int x) {
    x++;
    int s = 0;
    for(;x;x-=x&-x) s+=bit[x];
    return s;
  }
  void resize(int n_, int m_) {
    m = m_;
    n = n_;
    bit.resize(m + 5);
    st.insert({{base, n - 1 + base}, 0});
    st.insert({{n + base, n + base}, oob});
    add(0, n);
  }
  void reset() {
    for(int i=0; i<=m; i++) bit[i] = 0;
    st.clear();
    st.insert({{base, n - 1 + base}, 0});
    st.insert({{n + base, n + base}, oob});
    add(0, n);
  }
  
  void update_range(int l, int r, int v) {
    vector<pair<pair<int,int>,int> > rem,ins;
    ins.push_back({{l, r}, v});
    auto it = st.lower_bound({{l, 0}, 0});
    while(1) {
      int lb = (*it).first.first;
      int rb = (*it).first.second;
      int val = (*it).second;
      if(lb == n+base) break;
      if(lb <= r) {
        if(rb <= r) {
          rem.push_back(*it);
          it++;
          continue;
        }
        rem.push_back(*it);
        ins.push_back({{r + 1, rb}, val});
        break;
      }
      else break;
    }
    it = st.lower_bound({{l, 0}, 0});
    if((*it).first.first > base) {
      it--;
      int lb = (*it).first.first;
      int rb = (*it).first.second;
      int val = (*it).second;
      if(rb >= l) {
        if(rb > r) {
          rem.push_back(*it);
          ins.push_back({{lb, l - 1}, val});
          ins.push_back({{r + 1, rb}, val});
        }
        else {
          rem.push_back(*it);
          ins.push_back({{lb, l - 1}, val});
        }
      }
    }
    for(auto x: rem) {
      st.erase(x);
      add(x.second, -(x.first.second - x.first.first + 1));
    }
    for(auto x: ins) {
      st.insert(x);
      add(x.second, x.first.second - x.first.first + 1);
    }
  }
  int query_ranges() { // Number of disjoint ranges 
    return st.size(); 
  }
  int query_count(int l, int r) { // Number of elements having value in [l, r]
    return sum(r) - sum(l - 1);
  }
};
