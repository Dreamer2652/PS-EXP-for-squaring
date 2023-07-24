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

예를 들어, 아래는 입력받은 두 정수 a, N에 대해 <b>a<sup>N</sup></b>을 구하는 코드이다.

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
64-bit 자료형이라도 저장할 수 있는 최대 값은 unsigned 기준 2<sup>64</sup>-1 ≈ <b>1.8×10<sup>19</sup></b>이므로  
overflow를 방지하기 위해 <b>a<sup>n</sup>를 M으로 나눈 나머지</b>를 구하면 다음과 같다.

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

그런데, 위의 코드는 잠깐만 봐도 알 수 있듯이 시간 복잡도가 <b>O(N)</b>이다. N이 매우 큰 수라면 이 코드가 원활히 작동할 수 있을까?

***
## 임의의 정수에 대한 분할 정복을 이용한 거듭제곱
음이 아닌 두 정수 A, N가 있을 때 Α<sup>N</sup>를 구하는 방법을 생각해보자.  
단, 이 수는 매우 클 수 있으므로 M으로 나눈 나머지 <b>Α<sup>N</sup> mod M</b>를 구할 것이다.  

모든 정수는 서로 다른 2의 거듭제곱의 합 형태로 표현 가능하다는 성질을 이용하면,  
예를 들어 N이 11일 때, N = 11 = 1 + 2 + 8이므로 <b>Α<sup>11</sup> = Α<sup>(1 + 2 + 8)</sup> = Α<sup>1</sup> × Α<sup>2</sup> × Α<sup>8</sup></b>이 된다.  

그런데, 각 A의 거듭제곱수는 이전에 계산한 값을 제곱하여 계산할 수 있다. 단순히 A를 각 횟수만큼 곱하는 것이 아닌  
<div align="center"><b>
Α<sup>2</sup> = (A)<sup>2</sup> = A × A,<br>
Α<sup>4</sup> = (Α<sup>2</sup>)<sup>2</sup> = Α<sup>2</sup> × Α<sup>2</sup>,<br>
...,<br>
Α<sup>2k</sup> = (Α<sup>k</sup>)<sup>2</sup> = Α<sup>k</sup> × Α<sup>k</sup><br>
</b></div><br>
를 이용하는 것이다.<br><br>

즉, 차례대로 A만을 곱해 나간다면 O(N)의 시간 복잡도를 가지지만, 위 방법을 이용하면 lg N 수준으로 2의 거듭제곱끼리의 곱셈 및 나머지 연산만 진행하므로 <b>O(lg N)</b>의 시간 복잡도를 가지게 된다.
[백준 13171번 문제](https://acmicpc.net/problem/13171) 설명에 위 내용이 잘 정리되어있으니 참고하면 좋다.

***
## 정사각행렬에 대한 분할 정복을 이용한 거듭제곱
앞에서 배운 정수의 거듭제곱을 바탕으로, 좀 더 확장하여 행렬에 적용시켜보자.

행렬이라고 크게 다를 것 없이 앞에서 사용한 A의 종류를 정수가 아닌 정사각행렬로 바꿔주면 된다.  
즉, 행렬 A를 11번 거듭제곱하면 아래와 같이 표현된다. 수학적인 표기로는 위의 정수 부분과 동일하다.  
<div align="center">
<b>Α<sup>11</sup> = Α<sup>(1 + 2 + 8)</sup> = Α<sup>1</sup> × Α<sup>2</sup> × Α<sup>8</sup></b>
</div><br/>

따라서, 행렬에서도 **곱셈 분할**에는 <b>O(lg N)</b>의 시간 복잡도를 가지게 된다.  

그러나 행렬곱은 특수한 형태로(아래 사진과 같이 곱들의 합을 하나의 요소로) 진행하기 때문에 행렬의 크기 또한 전체 프로그램의 시간 복잡도에 영향을 미친다. 즉, K×K 정사각행렬을 N번 거듭제곱할 때의 시간복잡도는 다음과 같다.  
<div align="center"><b>
O((행렬 곱 시간) × (곱셈 분할)) = O(K<sup>3</sup>lg N)
</b></div><br>

***
## 분할 정복을 이용한 거듭제곱을 사용하여 풀 수 있는 문제들
위의 내용을 적용하여 문제를 풀 수 있는 유형을 정리하면 대표적으로 아래와 같은 것들이 있다.

#### 1. 피보나치 수열의 n번째 수 구하기
피보나치 수열은 다음과 같이 각 항이 바로 앞의 두 항의 합으로 이루어진 수열로 다음과 같이 정의된다.
<div align="center"><b>
F<sub>0</sub> = 0, F<sub>1</sub> = 1, F<sub>n+2</sub> = F<sub>n+1</sub> + F<sub>n</sub>
</b></div><br>

초기값은 무시하고 아래의 점화식을 생각해보자.  
<div align="center"><b>
F<sub>n+2</sub> = F<sub>n+1</sub> + F<sub>n</sub> = 1 × F<sub>n+1</sub> + 1 × F<sub>n</sub><br>
F<sub>n+1</sub> = 1 × F<sub>n+1</sub>
</b></div><br>

따라서, 이를 다음과 같이 행렬 형태로 표현할 수 있다.  
```math
\begin{pmatrix} F_{n+2} \\ F_{n+1} \end{pmatrix} =
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}
\begin{pmatrix} F_{n+1} \\ F_{n} \end{pmatrix}
```
이 과정을 반복해서 진행하면,  
```math
\begin{pmatrix} F_{n+2} \\ F_{n+1} \end{pmatrix} =
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} \begin{pmatrix} F_{n+1} \\ F_{n} \end{pmatrix} = 
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} * \left ( \begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} \begin{pmatrix} F_{n} \\ F_{n-1} \end{pmatrix}\right ) =
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^{2} \begin{pmatrix} F_{n} \\ F_{n-1} \end{pmatrix} = \ldots = 
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^{n+1} \begin{pmatrix} F_{1} \\ F_{0} \end{pmatrix} =
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^{n+1} \begin{pmatrix} 1 \\ 0 \end{pmatrix}
```

따라서, 임의의 피보나치 수는 **2×2 행렬**을 이용해 구할 수 있다.  

즉, 앞 문단에서 K=2의 상수값으로 고정되므로 전체 시간 복잡도는 <b>O(lg N)</b>이 된다.
