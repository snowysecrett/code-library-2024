int random_prime(int l, int r) {
  while(1) {
    int x = rnd(l, r);
    int c = 0;
    for(int i=1; i*i<=x; i++) {
      if(x%i == 0) {
        c+=2;
        if(i*i == x) c--;
      }
    }
    if(c==2) return x;
  }
  return 1226;
}
