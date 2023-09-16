// #13171 : A
#include <stdio.h>

int main()
{
  long long A, X, result = 1, mod = 1e9+7;
  scanf("%lld %lld", &A, &X);

  for(A %= mod; X; X >>= 1)  // A >= mod인 경우를 위해 예외처리 및 비트연산으로 반복문 진행
  {
    if(X & 1)  // X % 2 == 1
      result = result * A % mod;    // 지수를 shift하면서 홀수인 경우만 실제 연산
    A = A * A % mod;  // 곱해지는 값 update
  }

  printf("%lld", result);
  return 0;
}
