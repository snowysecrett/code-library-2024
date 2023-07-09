int manacher(string s){
  string t = "|";
  for(char c: s) {
    t += c;
    t += "|";
  }
  int d = 0; //max nr of characters that don't differ
  int c = 0; //count of characters on either side
  int ans = 0;
  for(int i=1; i<t.size(); i++) {
    d = max(d - 1, 0ll);
    c = min(c, d);
    while(1) {
      int l, r;
      if(i % 2 == 1) { // character
        l = i - 2 * (c+1);
        r = i + 2 * (c+1);
      }
      else { // delimiter
        l = i - 2 * (c+1) + 1;
        r = i + 2 * (c+1) - 1;
      }
      if(l<0 || r>=t.size()) break;
      if(t[l] == t[r]) {
        c++;
        if(t[l] == t[l+2]) d++;
      }
      else break;
    }
    ans = max(ans, 2 * c + (i % 2 == 1));
  }
  return ans;
}
