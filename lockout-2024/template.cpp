#include "bits/stdc++.h"
using namespace std;
#define int long long
#define double long double
const int MAXN = 2e5 + 10, MOD = 1e9 + 7;
int fac[MAXN], invfac[MAXN];
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) { return uniform_int_distribution<int>(x, y)(rng); }
int bm(int b, int p) {
  if(p==0) return 1 % MOD;
  int r = bm(b, p >> 1);
  if(p&1) return (((r*r) % MOD) * b) % MOD;
  return (r*r) % MOD;
}
int inv(int b) { return bm(b, MOD-2); }
vector<int> prefix_function(vector<int> t) {
  int n = t.size(); vector<int> lps(n, 0);
  for(int i=1; i<n; i++) {
    int j = lps[i-1]; while(j > 0 && t[i] != t[j]) j = lps[j-1];
    lps[i] = (t[i] == t[j] ? j+1 : 0); 
  } return lps;
}
int nCr(int n, int r) {
  return (((fac[n] * invfac[r]) % MOD) * invfac[n-r]) % MOD;
}
void precomp() {
  for(int i=1; i<MAXN; i++) fac[i] = (i ? (fac[i-1] * i) % MOD : 1);
  invfac[MAXN - 1] = inv(fac[MAXN - 1]);
  for(int i=MAXN-2; i>=0; i--) invfac[i] = (invfac[i+1] * (i+1)) % MOD;
}
void solve(int tc) {
}
int32_t main() {
  precomp();
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}
// g++ A.cpp -std=c++17 -O2 -o A
// ./A < input.txt
