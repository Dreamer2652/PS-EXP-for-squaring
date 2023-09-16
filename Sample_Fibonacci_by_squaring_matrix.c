// #11444 : 피보나치 수 6
#include <stdio.h>

long long n, result[2][2] = {1,0,0,1}, coeff[2][2] = {1,1,1,0}, mod = 1e9+7, i, j, k;

void MatMul(long long matrix[][2])
{
  long long temp[5][5]={0,};
  
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
      MatMul(result);  // 1 : result <= result × coeff / 1 : coeff <= coeff × coeff
    MatMul(coeff);
  }
  printf("%lld", result[1][0]);
  return 0;
}
