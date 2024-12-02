struct Fraction {
  __int128 gcdd(__int128 x, __int128 y) {
    if(x == 0) return y;
    if(y == 0) return x;
    if(x < y) return gcdd(x, y % x);
    return gcdd(y, x % y);
  }
  int p, q;
  Fraction operator*(Fraction other) {
    __int128 num = p, den = q;
    num *= other.p, den *= other.q;
    __int128 g = gcdd(num, den);
    num /= g, den /= g;
    int n1 = num, n2 = den;
    Fraction product = {n1, n2};
    return product;
  }
  Fraction operator+(Fraction other) {
    __int128 l = q * other.q / gcd(q, other.q); 
    __int128 num = p * l/q + other.p * l/other.q;
    __int128 g = gcdd(l, num);
    l /= g, num /= g;
    int n1 = num, n2 = l;
    Fraction sum = {n1, n2};
    return sum;
  }
};
Fraction make_frac(int p, int q) {
  return {p, q};
}
