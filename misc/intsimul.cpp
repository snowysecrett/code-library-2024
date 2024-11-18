variant<bool, pair<int, int>> intsimul(int a, int b, int c, int d, int e, int f) {
  int det = a * e - b * d;
  if (det == 0) {
    if(a == 0 && b == 0 && c != 0) return false;
    if(d == 0 && e == 0 && f != 0) return false;
    if (a * f != c * d || b * f != c * e) return false;
    return true;
  }
  if((c * e - b * f) % det) return false;
  int x = (c * e - b * f) / det;
  if((a * f - c * d) % det) return false;
  int y = (a * f - c * d) / det;
  return make_pair(x, y);
}
