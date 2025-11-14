/*Notes:
  phi(a*b) = phi(a)*phi(b)*(d/phi(d)), here, d = gcd(a, b)
  phi(n) = n*(1-1/p1)*(1-1/p2)*....*(1-1/pk)
  summation of phi(d) = n, [d | n]
  a^phi(m) congruent to 1 (mod m), when a and m are relatively prime
  a^n is congruent to a^(n mod phi(m)) mod m
*/
int phi[N];
void totient() {
  for (int i = 1; i < N; i++) phi[i] = i;
  for (int i = 2; i < N; i++) {
    if (phi[i] == i) {
      for (int j = i; j < N; j += i) phi[j] -= phi[j] / i;
    }
  }
}
