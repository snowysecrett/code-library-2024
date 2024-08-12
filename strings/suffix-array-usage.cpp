#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 10;
bool equivalence(pair<int,pair<int,int> > x, pair<int,pair<int,int> > y) {
  return x.second.second<y.second.second;
}
int pos[MAXN];
int newClasses[MAXN];
int ps[MAXN];
pair<int, pair<int, int> > v[MAXN], w[MAXN]; 
vector<int> suffix_array(string s) {
  int n = s.size();
  for(int i=0; i<n; i++) v[i] = {i, {0, s[i]}};
  sort(v, v + n, equivalence);
  int mm = max(128, n);
  for(int i=0; i<20; i++) {
    for(int j=0; j<n; j++) {
      v[j].second.first = v[j].second.second;
    }
    for(int j=0; j<n; j++) {
      pos[v[j].first] = j;
    }
    for(int j=0; j<mm; j++) ps[j] = 0;
    for(int j=0; j<n; j++) {
      int tar = v[j].first + (1 << i);
      tar %= n;
      v[j].second.second = v[pos[tar]].second.first;
      ps[v[j].second.second]++;
    }
    for(int j=1; j<mm; j++) ps[j] += ps[j-1];
    for(int j=n-1; j>=0; j--) {
      int ec = v[j].second.second;
      ps[ec]--;
      w[ps[ec]] = v[j];
    }
    for(int j=0; j<mm; j++) ps[j] = 0;
    for(int j=0; j<n; j++) ps[w[j].second.first]++;
    for(int j=1; j<mm; j++) ps[j] += ps[j-1];
    for(int j=n-1; j>=0; j--) {
      int ec = w[j].second.first;
      ps[ec]--;
      v[ps[ec]] = w[j];
    }
    newClasses[0] = 0;
    for(int j=1; j<n; j++) {
      if(v[j].second != v[j-1].second) newClasses[j] = newClasses[j-1] + 1;
      else newClasses[j] = newClasses[j-1];
    }
    for(int j=0; j<n; j++) {
      v[j].second.first = 0;
      v[j].second.second = newClasses[j];
    }
  }
  vector<int> w;
  for(int i=0; i<n; i++) w.push_back(v[i].first);
  return w;
}
void solve(int tc) {
  string s;
  int len = 500000;
  for(int i=0; i<len; i++) {
    s += (rand() % 2 ? 'a' + rand() % 26 : 'A' + rand() % 26);
  }
  //cin >> s;
  s = s + "$";
  vector<int> suf = suffix_array(s);

  int n = s.size();
  int pos[n];
  for(int i=0; i<n; i++) pos[suf[i]] = i;
  int lcp[n];
  for(int i=0; i<n; i++) lcp[i] = 0;
  int k = 0;
  for(int i=0; i<n-1; i++){
    while(s[i + k] == s[suf[pos[i] - 1] + k]) k++;
    lcp[pos[i]] = k;
    k = max(k-1, 0);
  }
  long long ans = 0;
  for(int i=0; i<suf.size(); i++) {
    if(s[suf[i]] < 'a' || s[suf[i]] > 'z') continue;
    ans += n - suf[i] - 1;
    if(i+1 < suf.size()) ans -= lcp[i+1];
  }
  cout << ans << '\n';
}
int32_t main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}
// g++ E.cpp -std=c++17 -O2 -o E
// ./E < input.txt
