// #23819 : 묻고 더블로 마셔
#include <stdio.h>
typedef long long L;

int n, k, P, a[100], coeff[100], xn[100]={0,1,}, i, j;

void PolyMul(int poly[])
{
  L temp[200]={0,};

  // Naive한 다항식 곱셈 구현
  for(i = 0; i < k; i++)
    for(j = 0; j < k; j++)
      temp[i+j] = (temp[i+j]+(L)poly[i]*xn[j])%P;

  // Naive한 다항식 나눗셈 구현
  for(i = k+k-1; --i >= k;)
    for(j = i-1; j >= i-k; j--)
      temp[j] = (temp[j]+temp[i])%P;

  for(i = 0; i < k; i++)
    poly[i] = temp[i];  // temp 배열(다항식)을 poly에 복사
}

L Kitamasa()
{
  xn[0] = k<2;  // k가 1일 때 예외처리 동시에
  
  for(n -= k+1; n > 0; n >>= 1)  // 초항의 개수 + 1을 빼고 시작
  {
    if(n & 1)
      PolyMul(coeff);
    PolyMul(xn);
  }

  L s = 0;
  for(s = i = 0; i < k; i++)
    s = (s+(L)coeff[i]*a[i])%P;  // 점화식이 단순한 초항들의 합
  return s;  // 초항*계수들의 합을 return
}

int main()
{
  for(scanf("%d%d", &n, &k); i < k; coeff[i++] = 1)
    scanf("%d", a+i);
  scanf("%d", &P);
  
  printf("%lld", Kitamasa());
  return 0;
}
