const double PI = 3.141592653589793;
double bearing(pair<int,int> v) { // bearing of point (v.first,v.second)
  if(v.first == 0) {
    if(v.second > 0) return 0;
    else return 180;
  }
  if(v.second == 0) {
    if(v.first > 0) return 90;
    else return 270;
  }
  if(v.first > 0 && v.second > 0) {
    double bruh = atan(v.first * 1.0 / v.second);
    bruh /= (PI * 0.5);
    bruh *= 90;
    return bruh;
  }
  if(v.first > 0) {
    double bruh = atan(-v.second * 1.0 / v.first);
    bruh /= (PI * 0.5);
    bruh *= 90;
    bruh += 90;
    return bruh;
  }
  if(v.second < 0) {
    double bruh = atan(v.first * 1.0 / v.second);
    bruh /= (PI * 0.5);
    bruh *= 90;
    bruh += 180;
    return bruh;
  }
  double bruh = atan(-v.second * 1.0 / v.first);
  bruh /= (PI * 0.5);
  bruh *= 90;
  bruh += 270;
  return bruh;
}
