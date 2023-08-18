vector<int> suffix_array(string s) {
  int n = s.size();
  vector<pair<int, pair<int, int> > > v; 
  for(int i=0; i<n; i++) v.push_back({i, {0, s[i]}});
  sort(v.begin(),v.end(),equivalence);
  int mm = max(128ll, n);
  for(int i=0; i<19; i++) {
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
// lcp array code
// suf is the suffix array
// for 1 ≤ i < n, lcp[i] = LCP(s[suf[i-1]..-1], s[suf[i]..-1])
for(int i=0; i<n; i++) pos[suf[i]] = i;
int lcp[n];
int k = 0;
for(int i=0; i<n-1; i++){
  while(s[i + k] == s[suf[pos[i] - 1] + k]) k++;
  lcp[pos[i]] = k;
  k = max(k-1, 0);
}
