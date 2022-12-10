string add(string x, string y) {
  if(x.size() > y.size()) swap(x, y);
  if(x.size() < y.size()) {
    string bruh;
    for(int i=0; i<y.size()-x.size(); i++) {
      bruh += "0";
    }
    x = bruh + x;
  }
  x = "0" + x;
  y = "0" + y;
  string res;
  int carryover = 0;
  for(int i=x.size()-1; i>=0; i--) {
    int bruh = x[i] - '0' + y[i] - '0' + carryover;
    res += char('0' + (bruh % 10));
    carryover = bruh / 10;
  }
  while(res.size() > 1 && res[res.size() - 1] == '0') res.pop_back();
  reverse(res.begin(), res.end());
  return res;
}
