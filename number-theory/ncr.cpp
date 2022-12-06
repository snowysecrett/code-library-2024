int bm(int b, int p) {
  if(p==0) return 1 % MOD;
  int r = bm(b, p >> 1);
  if(p&1) return (((r*r) % MOD) * b) % MOD;
  return (r*r) % MOD;
}
int inv(int b) { 
  return bm(b, MOD-2);
}
int fac[MAXN];
int nCr(int n, int r) { 
  if(n < 0 || r < 0 || n < r) return 0;
  int ans = fac[n]; ans *= inv(fac[r]); ans %= MOD;
  ans *= inv(fac[n-r]); ans %= MOD; return ans;
}
void precomp() { 
  for(int i=0; i<MAXN; i++) fac[i] = (i == 0 ? 1 % MOD : (fac[i-1] * i) % MOD); 
}
// Call precomp() before running test cases
