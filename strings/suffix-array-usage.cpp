#include "bits/stdc++.h"
using namespace std;
const int MAXN = 1e6 + 10;
bool equivalence(pair<int,pair<int,int> > x, pair<int,pair<int,int> > y) {
  return x.second.second<y.second.second;
}
int pos[MAXN];
vector<pair<int,int> > wow[MAXN];
vector<int> suffix_array(string s) {
  int n = s.size();
  vector<pair<int, pair<int, int> > > v; 
  for(int i=0; i<n; i++) v.push_back({i, {0, s[i]}});
  sort(v.begin(),v.end(),equivalence);
  int mm = max(128, n);
  for(int i=0; i<20; i++) {
    for(int j=0; j<n; j++) {
      v[j].second.first = v[j].second.second;
    }
    for(int j=0; j<n; j++) {
      pos[v[j].first] = j;
    }
    for(int j=0; j<n; j++) {
      int tar = v[j].first + (1 << i);
      tar %= n;
      v[j].second.second = v[pos[tar]].second.first;
    }
    for(int j=0; j<mm; j++) wow[j].clear();
    for(int j=0; j<n; j++) wow[v[j].second.second].push_back({v[j].first,v[j].second.first});
    int ptr=0;
    for(int j=0; j<mm; j++) {
      for(pair<int,int> x: wow[j]) {
        v[ptr].first = x.first;
        v[ptr].second.first = x.second;
        v[ptr].second.second = j;
        ptr++;
      }
    }
    for(int j=0; j<mm; j++) wow[j].clear();
    for(int j=0; j<n; j++) wow[v[j].second.first].push_back({v[j].first,v[j].second.second});
    ptr=0;
    for(int j=0; j<mm; j++) {
      for(pair<int,int> x: wow[j]) {
        v[ptr].first = x.first;
        v[ptr].second.first = j;
        v[ptr].second.second = x.second;
        ptr++;
      }
    }
    vector<int> newClasses;
    newClasses.push_back(0);
    for(int j=1; j<n; j++) {
      if(v[j].second != v[j-1].second) newClasses.push_back(newClasses[j-1] + 1);
      else newClasses.push_back(newClasses[j-1]);
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
  cin >> s;
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
