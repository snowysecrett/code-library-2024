struct Fraction {
  int p, q;
  Fraction() : p(0), q(1) {}
  Fraction(int num, int den) {
    assert(den != 0 && "Denominator cannot be zero");
    int g = gcd(num, den);
    p = num / g;
    q = den / g;
    if (q < 0) {
      p = -p;
      q = -q;
    }
  }
  Fraction operator+(Fraction other) const {
    int l = q * other.q / gcd(q, other.q); 
    int num = p * l/q + other.p * l/other.q;
    return Fraction(num, l);
  }
  Fraction operator-(Fraction other) const {
    int l = q * other.q / gcd(q, other.q); 
    int num = p * l/q - other.p * l/other.q;
    return Fraction(num, l);
  }
  Fraction operator*(Fraction other) const {
    return Fraction(p * other.p, q * other.q);
  }
  Fraction operator/(Fraction other) const {
    return Fraction(p * other.q, q * other.p);
  }
};
Fraction frac(int p, int q) {
  return {p, q};
}
