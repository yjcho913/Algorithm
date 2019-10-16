// #16986. 인싸들의 가위바위보
#if 01
#include <stdio.h>

int visited[10];
int RES[10][10];
// 0: B, 1: C, 2: A
int wins[3];
int son[3][21];
int idx[2];
int N, K;
int sol;

void Input(void)
{
	int i, j;

	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &RES[i][j]);
		}
	}

	for (i = 1; i <= 20; i++) scanf("%d", &son[0][i]);
	for (i = 1; i <= 20; i++) scanf("%d", &son[1][i]);
}

void DFS(int op)
{
	int i;
	int tmp;

	if (sol || wins[0] >= K || wins[1] >= K) return;
	if (wins[2] >= K)
	{
		sol = 1;
		return;
	}

	idx[op]++;
	for (i = 1; i <= N; i++)
	{
		if (visited[i]) continue;
		visited[i] = 1;

		tmp = RES[i][son[op][idx[op]]];
		// A가 이기는 경우
		if (tmp == 2)
		{
			wins[2]++;
			DFS(op ^ 1);
			wins[2]--;
		}
		// A가 지는 경우
		else
		{
			wins[op]++;
			idx[1]++, idx[0]++;
			tmp = RES[son[op][idx[op]]][son[op ^ 1][idx[op ^ 1]]];
			if (tmp == 2 || ((tmp == 1) && (op > (op ^ 1))))
			{
				wins[op]++;
				DFS(op);
				wins[op]--;
			}
			else
			{
				wins[op ^ 1]++;
				DFS(op ^ 1);
				wins[op ^ 1]--;
			}
			idx[1]--; idx[0]--;
			wins[op]--;
		}
		visited[i] = 0;
	}
	idx[op]--;
}

int main(void)
{
	Input();
	if (N >= K) DFS(0);
	printf("%d\n", sol);
	return 0;
}
#endif
