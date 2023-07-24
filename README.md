# PS : EXP for squaring
Problem Solving (tags : Exponentiation by Squaring)
  - Introduction
  - 단순 정수 (Single variable)
  - 정사각행렬 (Square matrix)
  - 기타 적용 방법
  - Naive きたまさ法 (Vector)

***
## Introduction
어떤 정수의 거듭제곱을 구하는 코드를 작성한다면 O(N)의 하나의 반복문을 사용하는 방법을 먼저 떠올린다.
예를 들어, 아래는 입력받은 두 정수 a, N에 대해 a<sup>N</sup>을 구하는 코드이다.

```c
#include <stdio.h>

int main()
{
  long long N, a, x = 1;
  scanf("%lld%lld", &a, &N);

  for(int i = 1; i <= N; i++)
    x *= a;

  printf("%lld", x);
  return 0;
}
```
여기서, 아무리 64-bit 자료형이라도 저장할 수 있는 최대 값은 unsigned 기준 2<sup>64</sup>-1 ≈ 1.8×10<sup>19</sup>이므로 overflow를 방지하기 위해 a<sup>n</sup>을 충분히 작은 수 m으로 나눈 나머지를 구하면 다음과 같다.

```c
#include <stdio.h>

int main()
{
  long long N, a, x = 1;
  scanf("%lld%lld", &a, &N);

  for(int i = 1; i <= N; i++)
    x = x * a % m;            // 단, a < m

  printf("%lld", x);
  return 0;
}
```
이는 수학적으로 정수 a, b에 대해 **(a × b) mod m = {(a mod m) × (b mod m)} mod m**가 성립하므로 가능하다.


위의 코드는 잠깐만 봐도 알 수 있듯이 시간 복잡도가 O(N)이다. N이 매우 큰 수라면 이 코드가 원활히 작동할 수 있을까?
***


