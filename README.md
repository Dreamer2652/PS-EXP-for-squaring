PS : EXP by squaring
====================
> Problem Solving (tags : Exponentiation by Squaring)
- Introduction
- 단순 정수 (Single variable)
- 정사각행렬 (Square matrix)
- 기타 적용 방법
- Naive きたまさ法 (Polynomial / Vector)
***
## Introduction
어떤 정수의 거듭제곱을 구하는 코드를 작성한다면 O(N)의 하나의 반복문을 사용하는 방법을 먼저 떠올린다.  

예를 들어, 아래는 입력받은 두 정수 a, N에 대해 a<sup>N</sup>을 구하는 코드이다.

```c
// N번 진행하는 반복문 사용
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
여기서, 아무리 64-bit 자료형이라도 저장할 수 있는 최대 값은 unsigned 기준 2<sup>64</sup>-1 ≈ 1.8×10<sup>19</sup>이므로  
overflow를 방지하기 위해 a<sup>n</sup>를 M으로 나눈 나머지를 구하면 다음과 같다.

```c
// N번 진행하는 반복문 사용 + 나머지 구하기
#include <stdio.h>

int main()
{
  long long N, M, a, x = 1;
  scanf("%lld%lld%lld", &a, &N, &M);

  for(int i = 1; i <= N; i++)
    x = x * a % M;            // 단, M > a를 만족한다고 가정

  printf("%lld", x);
  return 0;
}
```
이는 수학적으로 정수 a, b에 대해 다음의 식을 만족하므로 위와 같이 코드를 작성할 수 있다.

<div align="center">
<b>(a × b) mod M = {(a mod M) × (b mod M)} mod M</b>
</div><br>

그런데, 위의 코드는 잠깐만 봐도 알 수 있듯이 시간 복잡도가 O(N)이다. N이 매우 큰 수라면 이 코드가 원활히 작동할 수 있을까?

***
## 임의의 정수에 대한 분할정복을 이용한 거듭제곱
음이 아닌 두 정수 A, N가 있을 때 Α<sup>N</sup>를 구하는 방법을 생각해보자.  
단, 이 수는 매우 클 수 있으므로 M으로 나눈 나머지 Α<sup>N</sup> mod M를 구할 것이다.  

모든 정수는 서로 다른 2의 거듭제곱의 합 형태로 표현 가능하다는 성질을 이용하면,  
예를 들어 N이 11일 때, N = 11 = 1 + 2 + 8이므로 <b>Α<sup>11</sup> = Α<sup>(1 + 2 + 8)</sup> = Α<sup>1</sup> × Α<sup>2</sup> × Α<sup>8</sup></b>가 된다.  

그런데, A의 거듭제곱수는 이전에 계산한 값을 제곱하여 계산할 수 있다. 단순히 A를 각 횟수만큼 곱하는 것이 아닌  
<div align="center">
<b>Α<sup>2</sup> = (A)<sup>2</sup>, Α<sup>4</sup> = (Α<sup>2</sup>)<sup>2</sup>, ..., Α<sup>2k</sup> = (Α<sup>k</sup>)<sup>2</sup></b>
</div><br/>
를 이용하는 것이다.<br><br>

즉, 차례대로 A만을 곱해 나간다면 O(N)의 시간 복잡도를 가지지만, 위 방법을 이용하면 O(lg N)의 시간 복잡도를 가지게 된다. 
[백준 13171번 문제](https://www.acmicpc.net/problem/13171)설명에 위 내용이 잘 정리되어있으니 참고하면 좋다.


