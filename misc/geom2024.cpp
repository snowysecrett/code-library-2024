struct LatticePoint {
  int x, y;
  LatticePoint(int x = 0, int y = 0) : x(x), y(y) {}
  int cross(const LatticePoint &other) const { return x * other.y - y * other.x; }
  int dot(const LatticePoint &other) const { return x * other.x + y * other.y; }
  LatticePoint operator+(const LatticePoint &other) const { return LatticePoint(x + other.x, y + other.y); }
  LatticePoint operator-(const LatticePoint &other) const { return LatticePoint(x - other.x, y - other.y); }
  bool operator==(const LatticePoint &other) const { return x == other.x && y == other.y; }
  bool operator<(const LatticePoint &other) const { return make_pair(x, y) < make_pair(other.x, other.y); }
  int distsq(const LatticePoint &other) const { return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y); }
  double dist(const LatticePoint &other) const { return sqrt((x - other.x) * (x - other.x) * 1. + (y - other.y) * (y - other.y) * 1.); }
  int man(const LatticePoint &other) const { return abs(x - other.x) + abs(y - other.y); }
  double bearing() { 
    const double PI = acos(-1);
    if(x == 0) {
      if(y > 0) return 0;
      else return 180;
    }
    if(y == 0) {
      if(x > 0) return 90;
      else return 270;
    }
    if(x > 0 && y > 0) {
      double bruh = atan(x * 1.0 / y);
      bruh /= (PI * 0.5);
      bruh *= 90;
      return bruh;
    }
    if(x > 0) {
      double bruh = atan(-y * 1.0 / x);
      bruh /= (PI * 0.5);
      bruh *= 90;
      bruh += 90;
      return bruh;
    }
    if(y < 0) {
      double bruh = atan(x * 1.0 / y);
      bruh /= (PI * 0.5);
      bruh *= 90;
      bruh += 180;
      return bruh;
    }
    double bruh = atan(-y * 1.0 / x);
    bruh /= (PI * 0.5);
    bruh *= 90;
    bruh += 270;
    return bruh;
  }
  friend ostream &operator<<(ostream &os, const LatticePoint &p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};
struct Line {
  LatticePoint a, b;
  Line() : a(LatticePoint(0, 0)), b(LatticePoint(0, 0)) {}
  Line(const LatticePoint &a, const LatticePoint &b) : a(a), b(b) {}
  bool onLine(const LatticePoint &p) const {
    return (b - a).cross(p - a) == 0;
  }
  friend ostream &operator<<(ostream &os, const Line &l) {
    return os << "Line: " << l.a << " to " << l.b;
  }
  variant<bool, pair<pair<int,int>, pair<int,int>>> fracsimul(int a, int b, int c, int d, int e, int f) const {
    int det = a * e - b * d;
    if (det == 0) {
      if(a == 0 && b == 0 && c != 0) return false;
      if(d == 0 && e == 0 && f != 0) return false;
      if (a * f != c * d || b * f != c * e) return false;
      return true;
    }
    int g = gcd(c * e - b * f, det);
    pair<int, int> x = {(c * e - b * f) / g, det / g};
    g = gcd(a * f - c * d, det);
    pair<int, int> y = {(a * f - c * d) / g, det / g};
    return make_pair(x, y);
  }
  variant<bool, LatticePoint> lineIntersect(const Line &other) const {
    variant<bool, pair<pair<int,int>, pair<int,int>>> res = fracsimul(b.x - a.x, other.a.x - other.b.x, other.a.x - a.x, b.y - a.y, other.a.y - other.b.y, other.a.y - a.y);
    if(holds_alternative<bool>(res)) return get<bool>(res);
    else {
      pair<pair<int,int>, pair<int,int>> gl = get<pair<pair<int,int>, pair<int,int>>>(res);
      if(gl.first.first * (b.x - a.x) % gl.first.second) return false;
      if(gl.first.first * (b.y - a.y) % gl.first.second) return false;
      return LatticePoint(
        a.x + gl.first.first * (b.x - a.x) / gl.first.second, 
        a.y + gl.first.first * (b.y - a.y) / gl.first.second
      );
    }
  }

};
struct Segment : Line {
  Segment() : Line(LatticePoint(0, 0), LatticePoint(0, 0)) {} 
  Segment(const LatticePoint &a, const LatticePoint &b) : Line(a, b) {}
  bool onSegment(const LatticePoint &other) const {
    return onLine(other) 
    && min(a.x, b.x) <= other.x && other.x <= max(a.x, b.x)
    && min(a.y, b.y) <= other.y && other.y <= max(a.y, b.y);
  }
  variant<bool, LatticePoint> segmentIntersect(const Segment &other) const {
    variant<bool, LatticePoint> res = lineIntersect(other);
    if(holds_alternative<bool>(res)) return get<bool>(res);
    LatticePoint pt = get<LatticePoint>(res);
    if(!onSegment(pt) || !other.onSegment(pt)) return false;
    return pt;
  }
  int countLP() {
    if(a.x == b.x && a.y == b.y) return 1;
    return 1 + gcd(abs(a.x - b.x), abs(a.y - b.y));
  }
};
