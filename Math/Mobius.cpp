mobius[1] = 1;
for(int i=1;i<N;i++)
{
  for(int j=2*i;j<N;j+=i)mobius[j]-=mobius[i];
}
/*
Let, d | n
1)summation of meu(d) = [n==1]
2)summation of phi(d) = n
3)summation of meu(d)*(n/d) = phi(n) 
4)When finding [gcd(i, j]==1], use 1
5)When finding gcd(i, j), use 2
6)Number of coprime pairs = summation of meu(d)*cnt(d))
7)All pair summation of gcd = summation of phi(d)*cnt(d)
Here, cnt(d) can be nc2, nc3, n*n, etc. It means, count for multiples of d. 
*/
