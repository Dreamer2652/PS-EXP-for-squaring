// #15712 : 등비수열
#include <stdio.h>

int main()
{
  long long a, r, n, m, S = 0;
  
  for(scanf("%lld%lld%lld%lld", &a, &r, &n, &m); n; n >>= 1)
  {
    if(n & 1)
      S = (result*r+a)%m;  // 현재 S 값에 가중치 r을 곱하고 a ~ ar^(2^k)를 더함
    
    // 곱해지는 값 update
    a = (a*r+a)%m;        // a+ar+...+ar^(2^k)
    r = r*r%m;
  }
  
  printf("%lld", S);
  return 0;
}
