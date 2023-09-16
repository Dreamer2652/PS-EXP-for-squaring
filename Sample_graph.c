// #12850 : 본대 산책2
#include <stdio.h>
typedef long long L;

L adj[8][8], result[8][8];
int D;

void MatMul(L matrix[][8])
{
  L temp[8][8], t;
  int P = 1e9+7, i, j, k;

  for(i = 0; i < 8; i++)
    for(j = 0; j < 8; temp[i][j++] = t%P)
      for(t = k = 0; k < 8 ; k++)
        t += (L)matrix[i][k]*adj[k][j];

  for(i = 0; i < 8; i++)
    for(j = 0; j < 8; j++)
      matrix[i][j] = temp[i][j];
}

int main()
{
  // Initialize adj matrix
  adj[0][1] = adj[0][7]=
  adj[1][0] = adj[1][2] = adj[1][6] = adj[1][7] =
  adj[2][1] = adj[2][3] = adj[2][5] = adj[2][6] =
  adj[3][2] = adj[3][4] =
  adj[4][3] = adj[4][5] =
  adj[5][2] = adj[5][4] = adj[5][6] =
  adj[6][1] = adj[6][2] = adj[6][5] = adj[6][7] =
  adj[7][0] = adj[7][1] = adj[7][6] = 1;
  for(int i = 0; i < 8; i++)
    result[i][i]=1;    // Identity matrix

  for(scanf("%d",&D); D; D >>= 1)
  {
    if(D & 1)
      MatMul(result);
    MatMul(adj);
  }

  printf("%lld", result[0][0]);
  return 0;
}
