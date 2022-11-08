#include "bits/stdc++.h"
#include "mushrooms.h"
using namespace std;

int count_mushrooms(int n);

int use_machine(std::vector<int> x);

mt19937_64 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng);
  return u;
}

int count_mushrooms(int n) {

  if(n <= 226) {
    int ans = 1;
    for(int i=1; i<n; i++) ans += 1 - use_machine({0, i});
    return ans;
  }

  int ans = 0;
  int type[n];
  for(int i=0; i<n; i++) type[i] = -1;
  type[0] = 0;
  vector<int> list[2];
  list[0].push_back(0);

  
  for(int i=1; i<=2; i++) {
    type[i] = use_machine({0, i});
    list[type[i]].push_back(i);
  }

  vector<int> ind;
  if(list[0].size() > 1) ind = {list[0][0], list[0][1]};
  else ind = {list[1][0], list[1][1]};
  int id;
  if(list[0].size() > list[1].size()) id = 0;
  else id = 1;

  int sigh = use_machine({ind[0], 3, ind[1], 4});
  if(sigh >= 2) type[3] = 1-id;
  else type[3] = id;
  if(sigh % 2 == 1) type[4] = 1-id;
  else type[4] = id;

  list[type[3]].push_back(3);
  list[type[4]].push_back(4);

  ind.clear();
  if(list[0].size() > 2) ind = {list[0][0], list[0][1], list[0][2]};
  else ind = {list[1][0], list[1][1], list[1][2]};
  if(list[0].size() > list[1].size()) id = 0;
  else id = 1;

  int reference = 199;
  for(int i=5; i<=reference-5; i+=5) {
    int res = use_machine({ind[0], i, ind[1], i+1, ind[2], i+2});
    if(res & 1) type[i+2] = 1-id;
    else type[i+2] = id;
    if(res / 2 == 0) {
      type[i] = type[i+1] = id;
      for(int j=i; j<i+3; j++) list[type[j]].push_back(j);
      i -= 2;
      continue;
    }
    else if(res / 2 == 2) {
      type[i] = type[i+1] = 1-id;
      for(int j=i; j<i+3; j++) list[type[j]].push_back(j);
      i -= 2;
      continue;
    }
    else {
      if(list[1-id].size() < 2) {
        
        for(int j=i; j<=i+3; j+=3) {
          res = use_machine({ind[0], j, ind[1], j+1});
          if(res & 1) type[j+1] = 1-id;
          else type[j+1] = id;
          if(res >= 2) type[j] = 1-id;
          else type[j] = id;
        }
        for(int j=i; j<i+5; j++) list[type[j]].push_back(j);
        continue;
      }
      res = use_machine({list[1-id][0], i, list[1-id][1], ind[0], i+1, ind[1], i+3, ind[2], i+4}) - 1;
      if(res & 1) type[i+4] = 1-id;
      else type[i+4] = id;

      
      res -= res%2;
      if(res % 4 == 2) type[i+3] = 1-id;
      else type[i+3] = id;
      
      if(res / 4 == 1) type[i] = id, type[i+1] = 1-id;
      else type[i] = 1-id, type[i+1] = id;
      
    }
    for(int j=i; j<i+5; j++) if(type[j] >= 0) list[type[j]].push_back(j);
  }
  queue<int> qq;
  for(int i=0; i<reference; i++) {
    if(type[i] == -1) {
      qq.push(i);
    }
  }
  while(qq.size() > 1) {
    int f1 = qq.front();qq.pop();
    int f2 = qq.front();qq.pop();
    int res=  use_machine({ind[0], f1, ind[1], f2});
    if(res >= 2) type[f1] = 1-id;
    else type[f1] = id;
    if(res & 1) type[f2] = 1-id;
    else type[f2] = id;
    list[type[f1]].push_back(f1);
    list[type[f2]].push_back(f2);
  }
  if(qq.size() == 1) {
    int f = qq.front();
    type[f] = use_machine({0, f});
    list[type[f]].push_back(f);
  }
  ans = list[0].size(); 
  queue<int> q;
  
  for(int i=reference; i<n; i++) q.push(i);
  while(q.size()) {
    int maa = max(list[0].size(), list[1].size());
    int idx;
    if(list[0].size() > list[1].size()) idx = 0;
    else idx = 1;
    vector<int> toask;
    maa = min(maa, (int) q.size());
    for(int i=0; i<maa; i++) {
      toask.push_back(list[idx][i]);
      toask.push_back(q.front());
      q.pop();
    }
    int res = use_machine(toask);
    if(res & 1) {
      if(idx == 0) {
        list[1].push_back(toask.back());
      }
      else {
        list[0].push_back(toask.back());
      }
    }
    else {
      if(idx == 0) {
        list[0].push_back(toask.back());
      }
      else {
        list[1].push_back(toask.back());
      }
    }
    if(idx == 0) res = maa - (res+1)/2;
    else res = (res+1)/2;
    ans += res;
  }
  
  
  return ans;

}


