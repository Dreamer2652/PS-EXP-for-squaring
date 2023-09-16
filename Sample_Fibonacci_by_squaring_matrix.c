// #11444 : 피보나치 수 6
#include <stdio.h>

// Fibonacci coeff F_n+2 = F_n+1 + F_n
long long n, result[2][2] = {1,0,0,1}, coeff[2][2] = {1,1,1,0};

void MatMul(long long matrix[][2])
{
  long long temp[5][5]={0,};
  int mod = 1e9+7, i, j, k;
  
  // O((행렬 크기)³)
  for(i = 0; i < 2; i++)
    for(j = 0; j < 2; j++)
      for(k = 0; k < 2; k++)
        temp[i][j] = (temp[i][j] + matrix[i][k] * coeff[k][j]) % mod;  // (result or coeff) × coeff
  
  for(i = 0; i < 2; i++)
    for(j = 0; j < 2; j++)
      matrix[i][j] = temp[i][j];  // temp 행렬을 원래 행렬에 복사
}

int main()
{
  for(scanf("%lld",&n); n; n>>=1)
  {
    if(n & 1)
      MatMul(result);  // result <= result × coeff 
    MatMul(coeff);    // coeff <= coeff × coeff
  }
  printf("%lld", result[1][0]);
  return 0;
}
