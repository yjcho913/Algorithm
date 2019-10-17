// #16987. 계란으로 계란치기
#include <stdio.h>

int N;
int S[10];
int W[10];
int dead[10];
int sol;

void Input(void)
{
	int i;

	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d %d", &S[i], &W[i]);
	}
}

// L : 손에 든 계란
void DFS(int L, int cnt)
{
	int i;
	int tmp;

	if (cnt >sol) sol = cnt;
	if (sol == N || L >= N) return;
	if (dead[L])
	{
		DFS(L + 1, cnt);
		return;
	}
	
	// i : 깰 계란
	for (i = 0; i < N; i++)
	{
		if (L == i || dead[i]) continue;

		tmp = 0;
		S[L] -= W[i];
		S[i] -= W[L];
		if (S[L] <= 0)
		{
			tmp++;
			dead[L] = 1;
		}
		if (S[i] <= 0)
		{
			tmp++;
			dead[i] = 1;
		}

		DFS(L + 1, cnt + tmp);

		if (S[L] <= 0) dead[L] = 0;
		if (S[i] <= 0) dead[i] = 0;
		S[L] += W[i];
		S[i] += W[L];
	}
}

int main(void)
{
	Input();
	DFS(0, 0);
	printf("%d\n", sol);
	return 0;
}
