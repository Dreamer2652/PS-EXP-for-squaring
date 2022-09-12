// 2500 : 복불복 (22.2.13 solved)

#include <stdio.h>
typedef unsigned short U;

int N,K,T,i,j,z;
U I[1001]={1,},a[1001],P=42043;

void M(U T[])
{
  U t[1001]={0,};
  for(i=0;i<=K;i++)
    for(j=0;i+j<=K;t[i+j++]=z<P?z:z%P)
      z=t[i+j]+(int)T[i]*a[j];
  
  for(i=0;i<=K;i++)
    T[i]=t[i];
}

int main()
{
  for(scanf("%d%d%d",&N,&K,&T);T--;)
  {
    scanf("%d",&i);
    if(i<=K)
      a[i]++;
  }
  
  for(;N;N>>=1)
  {
    if(N&1)
      M(I);
    M(a);
  }

  for(i=j=0;i<=K;j=j<P?j:j-P)
    j+=I[i++];
  printf("%d",j);
  return 0;
}

/*
n번째 돌림판에서 나온 수를 Xn이라고 하면 ΣXn≤K를 만족해야함

이것을 다항식의 관점으로 바라보면 Πx^Xn<=x^K가 되므로 자연수 N에 대해
x^(K+N)=0인 きたまさ法을 사용해서 모든 경우의 수를 구할 수 있음
*/