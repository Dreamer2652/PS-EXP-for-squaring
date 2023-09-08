PS : EXP by squaring
====================
> Problem Solving (tags : exponentiation by squaring)  
>
> '분할 정복을 이용한 거듭제곱' 태그가 달린 문제들을 풀어보면서 공부했던 과정을 체감 난이도 순으로 정리하여 작성하였습니다.
- Introduction
- 단순 정수 (Single variable)
- 정사각행렬 (Square matrix)
- 기타 적용 방법
- Naive きたまさ法 (Polynomial / Vector)
***
## Introduction
어떤 정수의 거듭제곱을 구하는 코드를 작성한다면 O(*N*)의 하나의 반복문을 사용하는 방법을 먼저 떠올린다.  

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

그런데, 위의 코드는 잠깐만 봐도 알 수 있듯이 시간 복잡도가 <b>O(*N*)</b>이다. N이 매우 큰 수라면 이 코드가 원활히 작동할 수 있을까?

***
## 임의의 정수에 대한 분할 정복을 이용한 거듭제곱
음이 아닌 두 정수 A, N이 있을 때 Α<sup>N</sup>를 구하는 방법을 생각해보자.  
단, 이 수는 매우 클 수 있으므로 M으로 나눈 나머지 <b>Α<sup>N</sup> mod M</b>를 구할 것이다.  

모든 정수는 서로 다른 2의 거듭제곱의 합 형태로 표현 가능하다는 성질을 이용하면,  
예를 들어 N이 11일 때, N = 11 = 1 + 2 + 8이므로 <b>Α<sup>11</sup> = Α<sup>(1 + 2 + 8)</sup> = Α<sup>1</sup> × Α<sup>2</sup> × Α<sup>8</sup></b>이 된다.  

그런데, 각 A의 거듭제곱수는 **이전에 계산한 값을 제곱**하여 계산할 수 있다. 단순히 A를 각 횟수만큼 곱하는 것이 아닌  
<div align="center"><b>
Α<sup>2</sup> = (A)<sup>2</sup> = A × A,<br>
Α<sup>4</sup> = (Α<sup>2</sup>)<sup>2</sup> = Α<sup>2</sup> × Α<sup>2</sup>,<br>
...,<br>
Α<sup>2k</sup> = (Α<sup>k</sup>)<sup>2</sup> = Α<sup>k</sup> × Α<sup>k</sup><br>
</b></div><br>
를 이용하는 것이다.<br><br>

즉, 차례대로 A만을 곱해 나간다면 O(*N*)의 시간 복잡도를 가지지만, 위 방법을 이용하면 log N 수준으로 2의 거듭제곱끼리의 곱셈 및 나머지 연산만 진행하므로 <b>O(log *N*)</b>의 시간 복잡도를 가지게 된다.
[백준 13171번 문제](https://acmicpc.net/problem/13171) 설명에 위 내용이 잘 정리되어있으니 참고하면 좋다.

***
## 정사각행렬에 대한 분할 정복을 이용한 거듭제곱
앞에서 배운 정수의 거듭제곱을 바탕으로, 좀 더 확장하여 **행렬**에 적용시켜보자.

행렬이라고 크게 다를 것 없이 앞에서 사용한 A의 종류를 정수가 아닌 정사각행렬로 바꿔주면 된다. 즉, 행렬 A를 11번 거듭제곱하면 아래와 같이 표현된다. 수학적인 표기로는 위의 정수 부분과 동일하다.  
<div align="center">
<b>Α<sup>11</sup> = Α<sup>(1 + 2 + 8)</sup> = Α<sup>1</sup> × Α<sup>2</sup> × Α<sup>8</sup></b>
</div><br/>

따라서, 행렬에서도 **곱셈 분할**에는 <b>O(log *N*)</b>의 시간 복잡도를 가지게 된다.

<p align="center"><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/e/eb/Matrix_multiplication_diagram_2.svg/330px-Matrix_multiplication_diagram_2.svg.png"></img></p>

그러나 행렬곱은 특수한 형태로(위 사진과 같이 곱들의 합을 하나의 요소로) 진행하기 때문에 행렬의 크기 또한 전체 프로그램의 시간 복잡도에 영향을 미친다. 즉, K×K 정사각행렬을 N번 거듭제곱할 때의 시간복잡도는 다음과 같다.

<div align="center"><b>
O((행렬 곱 시간) × (곱셈 분할)) = O(<i>K</i><sup>3</sup> log <i>N</i>)
</b></div>

***
## 분할 정복을 이용한 거듭제곱을 사용하여 풀 수 있는 문제들
위의 내용을 적용하여 문제를 풀 수 있는 유형을 정리하면 대표적으로 아래와 같은 것들이 있다.

#### 1. 피보나치 수열의 n번째 수 구하기 ([백준 11444번 문제 - 피보나치 수 6](https://www.acmicpc.net/problem/11444))
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
\begin{align*}
\begin{pmatrix} F_{n+2} \\ F_{n+1} \end{pmatrix} &=
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} \begin{pmatrix} F_{n+1} \\ F_{n} \end{pmatrix} \\&= 
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} * \left ( \begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} \begin{pmatrix} F_{n} \\ F_{n-1} \end{pmatrix}\right ) \\&=
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^{2} \begin{pmatrix} F_{n} \\ F_{n-1} \end{pmatrix} \\&= \ldots \\&= 
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^{n+1} \begin{pmatrix} F_{1} \\ F_{0} \end{pmatrix} \\&=
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}^{n+1} \begin{pmatrix} 1 \\ 0 \end{pmatrix}
\end{align*}
```

따라서, 임의의 피보나치 수는 아래의 **2×2 행렬**을 이용해 구할 수 있다.  
```math
\begin{pmatrix} F_{n} \\ F_{n-1} \end{pmatrix} =
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix} ^ {n-1}
\begin{pmatrix} 1 \\ 0 \end{pmatrix}
```

즉, 행렬의 크기가 고정되므로 <b>O(log *N*)</b>으로 N번째 피보나치 수를(정확히는 특정 수로 나눈 나머지를, 이후 예제도 동일) 구할 수 있다.

***
#### 2. 등비수열의 합 ([백준 15712번 문제 - 등비수열](https://www.acmicpc.net/problem/15712))
음이 아닌 정수를 밑과 지수로 하는 등비수열의 합과 같은 경우에도 O(*N*)의 반복문을 사용하여 값을 구할 수 있다. 그러나 이번에도 N이 크다면 어떻게 풀 수 있을까?  
가장 먼저 고려해볼 수 있는 방법으로는 **등비수열의 합 공식**을 사용하는 것이다. 초항이 a, 등비가 r인 등비수열의 첫째항부터 n항까지의 합 S는 다음과 같다.  

$$S=\frac{a(r^{n}-1)}{r-1}$$  

즉, r의 거듭제곱을 앞에서 했던 방법으로 O(log *N*)의 시간 복잡도로 계산하면 나머지는 단순 사칙연산이므로 O(log *N*)으로 계산할 수 있을 것이다.  

하지만, 등비수열의 합 또한 결과값이 빠른 속도로 커지므로 실제 문제로는 등비수열의 합 S를 특정 수로 나눈 나머지를 계산하는 문제가 많다. 그렇다면 거듭제곱 계산 과정의 수 또한 나머지 연산을 취하게 될텐데 **곱셈에서는 성립하던 식이 나눗셈에서는 성립하지 않는 문제점**이 있다.  

```math
(A~/~B)~{\rm mod~M} ≠ \{(A~{\rm mod~M})~/~(B~{\rm mod~M})\}~{\rm mod~M}
```

```math
\Rightarrow \frac{a\{(r^{n}~{\rm mod~M})-1\}}{r-1} {\rm mod~M} ≠ \frac{a(r^{n}-1)}{r-1} {\rm mod~M}
```

그러므로, 우리가 알고있는 **등비급수의 합 공식은 사용할 수 없으므로** 다른 방법을 사용해야 한다. 등비수열은 어떤 점화식으로 표현할 수 있을까? 이번에도 N = 11일 때 생각하여 앞에서 풀어봤던 방법과 비슷하게 접근해보자.  
즉, n을 2진수로 표현했을 때 **LSB가 1일 때만 특정 연산을 진행**하고, 0이면 아무런 연산을 진행하지 않는 형태의 반복문을 단계별로 진행해보면 다음과 같은 결과가 나온다.

|단계|값|설명|수식|
|:--:|:--:|:---------------:|:--------:|
|0|11(1011<sub>2</sub>)|첫 S의 값을 0으로 초기화|$S=0$|
|1|11(101**1**<sub>2</sub>)|n의 LSB가 1<br>→ S+=a<br>(현재 확인한 n은 0+1=1)|$S_{new}=S+a=a$|
|2|5(10**1**<sub>2</sub>)|n의 LSB가 1<br>→ S+=ar+ar<sup>2</sup><br>(현재 확인한 n은 1+2=3)|$S_{new}=S+ar+ar^{2}$<br>$=a+ar+ar^{2}$|
|3|2(1**0**<sub>2</sub>)|n의 LSB가 0<br>→ 기존 값 유지|$S=a+ar+ar^{2}$|
|4|1(**1**<sub>2</sub>)|n의 LSB가 1<br>→ S+=ar<sup>3</sup>~ar<sup>10</sup><br>(현재 확인한 n은 3+8=11)|$S_{new}=S+ar^{3}+...+ar^{10}$<br>$=a+ar+...+ar^{9}+ar^{10}$|
|5|0|n이 0이므로 반복 종료<br>→ 최종 답은 4번째의 S|$S=a+...+ar^{10}$|

위의 표처럼 정리한 결과, 더해지는 값의 규칙성을 찾기 어려워보이지만 앞에서의 분할 정복 거듭제곱 방식에서 보았던 형태를 **그대로 사용**할 수 있는 것을 볼 수 있다. 이는 곧, <b>'앞에서 제시한 코드 형태로 등비수열의 합 또한 구현할 수 있다.'</b>는 것을 의미한다. 그렇다면 각각의 상황에서 어떤 연산을 진행해야 위와 같은 결과를 얻을 수 있을까?  

표의 설명 부분을 유심히 읽어보면 추가로 더해주는 **항의 개수**는 모두 **2의 거듭제곱수**인 것을 확인할 수 있다. 더 자세히 얘기하면 비트값 자체가 항의 개수를 의미하는 것이다.  
따라서, 더해지는 항들(위 예시의 a, ar+ar<sup>2</sup>, ar<sup>3</sup>~ar<sup>10</sup>)을 빠르게 계산할 수 있다면 중간 과정에서는 **덧셈과 곱셈으로만 이루어져 있으므로** 나머지 연산을 마음편히 사용할 수 있을 것이다.  

그렇지만 위 방법을 그대로 계산하게 되면 어중간한 부분부터 덧셈이 시작되기 때문에 계산하기 번거롭다. 어떻게 해야 덧셈을 더욱 편하게 할 수 있을까? 2의 거듭제곱수의 개수라는 것을 잘 활용하려면 더하는 값들을 앞으로 당겨서 a부터 ar<sup>2<sup>n</sup>-1</sup>까지로 하면 편하지 않을까? 이걸 구현하려면... 원래있던 값들을 밀어내면 된...다?  

|단계|값|설명|수식|
|:--:|:--:|:---------------:|:--------:|
|0|11(1011<sub>2</sub>)|첫 S의 값을 0으로 초기화|$S=0$|
|1|11(101**1**<sub>2</sub>)|n의 LSB가 1<br>→ S+=a<br>(현재 확인한 n은 1)|$S_{new}=S+a=a$|
|2|5(10**1**<sub>2</sub>)|n의 LSB가 1<br>→ S=S*r<sup>2</sup>+a+ar<sup>2</sup><br>(현재 확인한 n은 3)|$S_{new}=Sr^{2}+a+ar$<br>$=(a)r^{2}+a+ar$<br>$=a+ar+ar^{2}$|
|3|2(1**0**<sub>2</sub>)|n의 LSB가 0<br>→ 기존 값 유지|$S=a+ar+ar^{2}$|
|4|1(**1**<sub>2</sub>)|n의 LSB가 1<br>→ S=S*r<sup>8</sup>+a~ar<sup>7</sup><br>(현재 확인한 n은 11)|$S_{new}=Sr^{8}+a+...+ar^{7}$<br>$=(a+ar+ar^{2})r^{8}+a+...+ar^{7}$<br>$=a+ar+...+ar^{9}+ar^{10}$|
|5|0|n이 0이므로 반복 종료<br>→ 최종 답은 4번째의 S|$S=a+...+ar^{10}$|

변형한 방법으로 더욱 편리하게 올바른 등비수열의 합을 구할 수 있는 것을 확인했다. 이제 a부터 ar<sup>2<sup>n</sup>-1</sup>까지의 합만 빠르게 계산할 수 있으면 문제가 해결된다.  

더하는 항의 개수가 2의 거듭제곱수이므로 분할 정복을 이용한 거듭제곱 형태로 표현할 수 있으며, 이 역시 앞의 방법을 그대로 적용하면 만들어 낼 수 있다. a부터 ar<sup>2<sup>n</sup>-1</sup>의 합을 S<sub>n</sub>라고 하면 아래의 식이 유도된다.  

$$S_{0}=a$$

$$S_{1}=a+ar=S_{0}+(S_{0}×r)$$

$$S_{2}=a+ar+ar^{2}+ar^{3}=S_{1}+(S_{1}×r^{2})$$

$$S_{3}=a+ar+ar^{2}+ar^{3}+ar^{4}+ar^{5}+ar^{6}+ar^{7}=S_{2}+(S_{2}×r^{4})$$

$$...$$

$$S_{k}=a+ar+...+ar^{2^{k}-1}=S_{k-1}+(S_{k-1}×r^{2^{k-1}})=S_{k-1}×(1+r^{2^{k-1}})$$

이를 코드로 작성하는 것은 또다른 문제일 것처럼 보이지만 매우 간단한 형태로 구현할 수 있다. 기존 형태에서 분기 조건(LSB가 1)을 만족하면 지금까지 계산한 가중치 r<sup>k</sup>를 곱한 후 등비급수의 합을 더해주면 되고, 반복문이 종료되기 전에 S<sub>k</sub>와 가중치를 업데이트 하는 것으로 바꿔주면 해결된다.  

지금까지의 말이 와닿지 않거나 코드 작성이 어렵게 느껴진다면, 행렬의 거듭제곱 방식을 그대로 사용하여도 무방하다. 등비수열의 합은 다음의 행렬을 사용해 구할 수 있다.  

```math
\begin{pmatrix}
r & 0 \\
a & 1 
\end{pmatrix}
```

이를 거듭제곱하면 1열의 두 값이 매우 익숙한 형태로 만들어 지는 것을 볼 수 있다.

```math
\begin{pmatrix}
r & 0 \\
a & 1 
\end{pmatrix} ^ {2} =
\begin{pmatrix}
r^{2} & 0 \\
a(r+1) & 1 
\end{pmatrix}
```
```math
\begin{pmatrix}
r & 0 \\
a & 1 
\end{pmatrix} ^ {3} =
\begin{pmatrix}
r^{3} & 0 \\
a(r^{2}+r+1) & 1 
\end{pmatrix}
```
$$...$$
```math
\begin{pmatrix}
r & 0 \\
a & 1 
\end{pmatrix} ^ {k} =
\begin{pmatrix}
r^{k} & 0 \\
a(r^{k}+r^{k-1}+...+r+1) & 1 
\end{pmatrix}
```

앞에서 설명한 내용 또한 위의 식을 각 요소마다 풀어서 설명한 것이며 궁극적으로 동일하다.

***
#### 3. 그래프에서 출발지-도착지 경로의 “경우의 수” 구하기 ([백준 12850번 문제 - 본대 산책2](https://www.acmicpc.net/problem/12850))
![image](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/12850/1.png)<br/>  
위와 같은 그래프가 주어진다고 하자. 즉, 각각의 정점은 아래와 같이 연결 되어 있다.

    학생회관 : 진리관, 형남공학관
    형남공학관 : 학생회관, 한경직기념관
    진리관 : 학생회관, 한경직기념관, 신양관
    한경직기념관 : 형남공학관, 진리관, 신양관, 미래관
    …

위 그래프에서 1분에 한 간선씩 움직일 수 있을 때, 8곳 중 임의의 출발지와 도착지 사이에서 **T분의 시간으로 만들 수 있는 경로의 경우의 수**는 얼마나 될까? 단, 그 수가 너무 커질 수 있으므로 특정 값으로 나눈 나머지를 구해보자.  

먼저 움직이지 않은 상황(T=0)에서는 경우의 수는 직관적으로 **출발지와 도착지가 같은 정점이라면 1, 아니라면 0**이라는 것을 알 수 있다. 그렇다면 T가 0보다 크다면 어떻게 될까? T를 증가시키면서 생각해보자.  

1분이 지난 시점(T=1)에서도 역시 직관적으로 1분에 한 간선을 움직일 수 있으므로 **출발지와 도착지가 서로 연결된 정점이라면 1, 아니라면 0**이다. 그렇지만 2분이 지난 시점부터는 상황이 복잡해지는게, 서로다른 간선을 건너갈 수도 있고, 동일한 간선을 통해 출발지로 되돌아올 수도 있다.  

직관으로는 해결하기 어려우니 1분 시점에서 값이 변한 이유가 무엇인지 생각해보자. 

이것을 반복해서 생각하면 **visited를 고려하지 않은 BFS(너비 우선 탐색)** 형태처럼 중복을 포함하여 인접한 정점으로 이동하는 모습을 상상할 수 있다. 즉, 이 문제 역시 재귀적으로 설명할 수 있다. **연결이 되어있는 정점들에 대해 1분 전의 경우의 수를 모두 더하면** 현재 그 정점으로 도착할 수 있는 경우의 수를 구할 수 있는 것이다.  

예를 들어, T분 동안 정보과학관에서 출발하여 정보과학관으로 돌아오는 경우의 수를 구한다고 하자. *정보과학관을 0번으로 반시계방향으로 정점 번호가 증가한다고 가정*하면, T분 후에 K번 노드에 도착하는 경우의 수를 n<sub>K,T</sub>라고 했을 때, 다음의 식이 성립한다.  
```math
\begin{pmatrix} n_{0,T} \\ n_{1,T} \\ n_{2,T} \\ n_{3,T} \\ n_{4,T} \\ n_{5,T} \\ n_{6,T} \\ n_{7,T} \end{pmatrix} =
\begin{pmatrix}
0 & 1 & 0 & 0 & 0 & 0 & 0 & 1 \\
1 & 0 & 1 & 0 & 0 & 0 & 1 & 1 \\
0 & 1 & 0 & 1 & 0 & 1 & 1 & 0 \\
0 & 0 & 1 & 0 & 1 & 0 & 0 & 0 \\
0 & 0 & 0 & 1 & 0 & 1 & 0 & 0 \\
0 & 0 & 1 & 0 & 1 & 0 & 1 & 0 \\
0 & 1 & 1 & 0 & 0 & 1 & 0 & 1 \\
1 & 1 & 0 & 0 & 0 & 0 & 1 & 0
\end{pmatrix}
×
\begin{pmatrix} n_{0,T-1} \\ n_{1,T-1} \\ n_{2,T-1} \\ n_{3,T-1} \\ n_{4,T-1} \\ n_{5,T-1} \\ n_{6,T-1} \\ n_{7,T-1} \end{pmatrix}
```

위 행렬을 자세히 보면 0과 1로 이루어진 불 행렬은 그래프의 *인접행렬*처럼 보인다. 이는 예시로 주어진 그래프가 방향성이 없는 간선으로만 이루어진 그래프이기 때문이고, 일반적인 방향 그래프에서 점화식을 하나씩 나열해서 행렬을 만들어보면 **인접행렬의 전치행렬**이 만들어지는 것을 쉽게 확인할 수 있을 것이다. (정확히는 각 정점끼리 <b>연결된 간선의 '개수'</b>로 이루어진 행렬이 된다. 즉, 정점끼리의 간선이 여러 개인 경우를 허용하면 불 행렬이 아닐 수도 있다.)

따라서, 피보나치 수를 구했을 때와 비슷하게 위의 행렬을 거듭제곱하면 T분 동안 정보과학관에서 출발하여 정보과학관으로 돌아오는 경로의 경우의 수를 구할 수 있다. 아래의 위 첨자 T는 전치(Transpose)가 아닌 행렬의 거듭제곱을 의미한다.  

```math
\begin{pmatrix} n_{0,T} \\ n_{1,T} \\ n_{2,T} \\ n_{3,T} \\ n_{4,T} \\ n_{5,T} \\ n_{6,T} \\ n_{7,T} \end{pmatrix} =
\begin{pmatrix}
0 & 1 & 0 & 0 & 0 & 0 & 0 & 1 \\
1 & 0 & 1 & 0 & 0 & 0 & 1 & 1 \\
0 & 1 & 0 & 1 & 0 & 1 & 1 & 0 \\
0 & 0 & 1 & 0 & 1 & 0 & 0 & 0 \\
0 & 0 & 0 & 1 & 0 & 1 & 0 & 0 \\
0 & 0 & 1 & 0 & 1 & 0 & 1 & 0 \\
0 & 1 & 1 & 0 & 0 & 1 & 0 & 1 \\
1 & 1 & 0 & 0 & 0 & 0 & 1 & 0
\end{pmatrix} ^ {T}
\begin{pmatrix} 1 \\ 0 \\ 0 \\ 0 \\ 0 \\ 0 \\ 0 \\ 0 \end{pmatrix}
```

피보나치 수의 예제와 그래프 예제를 정리하면 다음과 같이 결론을 이끌어 낼 수 있다.

> 문제의 조건을 적절히 바꾸어 점화식으로 표현이 가능하고 이것이 **길이가 K인(점화식에서의 최대/최소 인덱스의 차) 선형 점화식**으로 표현된다면,
이를 **행렬로 표현**하여 분할 정복을 이용한 거듭제곱을 이용해 <b>O(<i>K</i><sup>3</sup> log *N*)</b>으로 해결할 수 있다.

***
## 키타마사법
앞에서 설명하였듯이 문제를 적절히 **인접한 항들의 선형 점화식**으로 표현할 수 있다면, 이를 **행렬로 표현**하여 분할 정복을 이용한 거듭제곱을 이용해 <b>O(K<sup>3</sup>log *N*)</b>으로 해결할 수 있다고 하였다.  

그런데, 그래프의 예제에서는 각 행이 유의미한 정보를 담고 있지만, 피보나치 수열처럼 주어진 선형 점화식을 그대로 사용하는 문제는 그렇지 않다는 것을 감이 좋다면 눈치를 챘을 것이다. 즉, 아래의 피보나치 수의 행렬 표현  

```math
\begin{pmatrix} F_{n+2} \\ F_{n+1} \end{pmatrix} =
\begin{pmatrix} 1 & 1 \\ 1 & 0 \end{pmatrix}
\begin{pmatrix} F_{n+1} \\ F_{n} \end{pmatrix}
```

에서 2번째 행은 F<sub>n+1</sub>=F<sub>n+1</sub>을 의미하므로 정보가 없는 부분이다. 다시 말해, 단순히 행렬의 거듭제곱을 위한 더미 데이터라고 말할 수 있고, 이로 인해 행렬의 크기를 결정하는 점화식 길이에 매우 민감한 시간 복잡도를 가지게 된다.  

실제로 점화식으로서 의미가 있는 것은 첫번째 행만이므로 행렬 거듭제곱을 하지 않고 동일한 결과를 만들어내도록 하는 방법이 없을까? 답은 Yes이다. 이러한 유형의 문제는 <b>'키타마사법'</b>으로 불리는 알고리즘을 이용해 <b>O(<i>K</i><sup>2</sup> log *N*)</b>의 시간 복잡도로 해결할 수 있다.  
여기에 고속 푸리에 변환(Fast Fourier Transform; FFT)을 적용하면 <b>O(*K* log *K* log *N*)</b>까지 줄일 수 있지만 이는 넘어가도록 한다.  

키타마사법이라는 알고리즘은 앞에서 계속 다루었던 선형 점화식

$$A_N = c_1 A_{N-1} + c_2 A_{N-2} + \dots + c_K A_{N-K} = \displaystyle\sum_{i=1}^{K} c_i A_{N-i}$$

을 조금 변형하여 점화식을 **최초의 항들로만 이루어지도록**하는 다음의 형태를 찾는 것이다.

$$A_N = \displaystyle\sum_{i=1}^{K} c_i A_{N-i} = \sum_{i=0}^{K-1} d_{i} A_{i}$$

이는 수열의 항을 하나씩 낮추면서 직접 찾을 수 있다. 피보나치 수열과 같이 c<sub>1</sub>=c<sub>2</sub>=1, N=5일 때를 예시로 수열 d<sub>i</sub>를 구해보면 다음과 같다.

+ $A_5 = A_4+A_3$
+ $A_5 = (A_3+A_2)+A_3 = 2A_3+A_2$
+ $A_5 = 2(A_2+A_1)+A_2 = 3A_2+2A_1$
+ $A_5 = 3(A_1+A_0)+2A_1 = 5A_1+3A_0$
+ $d_1 = 5, d_0 = 3$

그런데 이 과정은 양변에 $A_x - c_1 A_{x-1} - c_2 A_{x-2} - \dots = 0$<b>의 상수배를 빼는 과정</b>으로도 볼 수 있다. 즉, 피보나치 수열의 경우 $A_x - A_{x-1} - A_{x-2} = 0$의 상수배를 빼는 것이다.

+ $A_5 = A_4+A_3$
+ $A_5 = (A_4+A_3)-(A_4-A_3-A_2) = 2A_3+A_2$
+ $A_5 = (2A_3+A_2)-2(A_3-A_2-A_1) = 3A_2+2A_1$
+ $A_5 = (3A_3+2A_2)-3(A_2-A_1-A_0) = 5A_1+3A_0$
+ $d_1 = 5, d_0 = 3$

위 식을 자세히 보면 <b>다항식 나눗셈</b>과 매우 유사해보이며, 실제로 $x^N$을 다항식  

$$f(x) = x^K - c_1 x^{K-1} - c_2 x^{K-2} - \dots - c_K x^0 = x^K - \displaystyle\sum_{i=1}^{K} c_i x^{K-i}$$

로 나눈 <b>나머지</b>를 구하는 과정과 동일하다. 

예시를 대입해보면 $x^5$를 $x^2-2x-1$로 나눈 나머지를 구하는 과정과 대응하며, 이를 직접 계산해보면  

$$x^5 = (x^3+x^2+2x+3)(x^2-x-1)+5x+3$$

임을 알 수 있고, 몫의 각 계수들이 위 과정에서의 계수(상수배), 나머지의 각 계수들이 $d_i$와 일치하게 된다.  

즉, 행렬곱 연산이 <b>다항식의 곱셈 및 나머지 연산</b> $x^N \mod f(x)$으로 바뀌게 되며, 이를 통해 O(<i>K</i><sup>3</sup> log <i>N</i>)보다 빠르게 계산할 수 있다.
앞에서 언급하였듯이 여기서는  정수의 거듭제곱에서 사용했던 제곱 및 나머지 성질을 여기서도 그대로 사용하여 행렬에서와 비슷하게 정수가 다항식으로 바뀐 것으로 아래의 순서를 따르게 된다.

1. $x^N$은 $x^1, x^2, x^4, ..., x^{2^{k}}$의 곱으로 분해한다. 이 경우 최대 O(log <i>N</i>)번의 곱셈을 진행하게 된다.
2. $x^N \mod f(x)$를 구하기 위해 $x^1 \mod f(x), x^2 \mod f(x), ..., x^{2^{k}} \mod f(x)$를 구한다.
3. f(x)의 차수가 K이므로 최대 차수가 K 미만인 다항식들의 곱을 구한다.

위와 같은 방식을 Naive하게 구현하면 **다항식 곱셈 및 나눗셈에 O(<i>K</i><sup>2</sup>)**, **다항식 곱셈이 총 O(log *N*)번** 발생하므로 키타마사법을 통한 시간복잡도는 다음과 같다.

<div align="center"><b>
O((다항식 곱셈&나눗셈 시간) × (곱셈 분할)) = O(<i>K</i><sup>2</sup> log <i>N</i>)
</b></div>
