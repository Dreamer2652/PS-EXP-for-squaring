// #10830 : 행렬 제곱
#include <stdio.h>

int N, result[5][5], A[5][5], i, j, k;

void MatMul(int matrix[][5]);
int main()
{
  long long B;
  scanf("%d%lld", &N, &B);

  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
    {
      scanf("%d", A[i]+j);      // scanf("%d", &A[i][j]);
      result[i][j] = (i==j);    // 정수에서의 초기값 : 1 → 행렬에서의 초기값 : 단위 행렬
    }

  for(; B; B >>= 1)
  {
    if(B & 1)
      MatMul(result);  // result <= result × A
    MatMul(A);    // A <= A × A
  }

  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
      printf("%d ", result[i][j]);
    puts("");
  }

  return 0;
}

void MatMul(int matrix[][5])
{
  int temp[5][5]={0,}, mod = 1e3;

  // O((행렬 크기)³)
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      for(k = 0; k < N; k++)
        temp[i][j] = (temp[i][j] + matrix[i][k] * A[k][j]) % mod;  // matrix × A
  
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      matrix[i][j] = temp[i][j];  // temp 행렬을 원래 행렬에 복사
}
