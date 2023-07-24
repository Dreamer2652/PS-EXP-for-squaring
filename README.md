# PS : EXP for squaring
Problem Solving (tags : Exponentiation by Squaring)
  - Introduction
  - 단순 정수 (Single variable)
  - 정사각행렬 (Square matrix)
  - 기타 적용 방법
  - Naive きたまさ法 (Vector)

***
## Introduction
어떤 정수의 거듭제곱을 구하는 코드를 작성한다면 N번 반복하는 하나의 반복문을 사용하는 방법을 먼저 떠올린다.
예를 들어, 아래는 입력받은 두 정수 a, n에 대해 a<sup>n</sup>을 구하는 코드이다.

```c
#include <stdio.h>

int main()
{
  long long n, a, x = 1;
  scanf("%lld%lld", &a, &n);

  for(int i = 1; i <= n; i++)
    x *= a;

  printf("%lld", x);
  return 0;
}
```


