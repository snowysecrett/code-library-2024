int csb(int l, int r, int k) { // count number of [l, r] such that i & 2^k > 0
  if(l > r) return 0;
  if(l == 0) {
    int s = r / (1ll << (k+1)); // number of complete cycles
    int t = r % (1ll << (k+1));
    int ans = s * (1ll << k);
    ans += (t >= (1ll << k) ? t - (1ll << k) + 1 : 0);
    return ans;
  }
  else return csb(0, r, k) - csb(0, l - 1, k);
}
