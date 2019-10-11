// #16235. 나무 재테크
#if 01
#include <stdio.h>
#define MAX (300000)
int N, M, K;
int add[12][12];
int yang[12][12];
int dr[MAX], dc[MAX], dage[MAX], dcnt;
int nr[MAX], nc[MAX], ncnt;

int rr[8] = { 1, 1, 1, 0, 0, -1, -1, -1 };
int cc[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
typedef struct st{
	int r, c, age;
}TREE;
TREE QUE1[MAX];
TREE QUE2[MAX];
int RWP, LWP;

void Input(void)
{
	int i, j;
	int r, c, age;

	scanf("%d %d %d", &N, &M, &K);
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= N; j++)
		{
			scanf("%d", &add[i][j]);
			yang[i][j] = 5;
		}
	}

	for (i = 0; i<M; i++)
	{
		scanf("%d %d %d", &r, &c, &age);
		QUE1[RWP++] = (TREE){ r, c, age };
	}
}

int Get_Sol(void)
{
	TREE out;
	int i, j, tr, tc;
	TREE * read = &QUE1, *write = &QUE2, *tmp;
	int RP;
	int lim;

	LWP = -1;
	while (K--)
	{

		// 봄
		RP = RWP;
		lim = LWP + 1;
		RWP = RWP - LWP;
		LWP = RWP - 1;
		ncnt = dcnt = 0;

		for (i = RP - 1; i >= lim; i--)
		{
			out = read[i];
			if (out.age <= yang[out.r][out.c]){
				yang[out.r][out.c] -= out.age;
				write[LWP--] = (TREE){ out.r, out.c, ++(out.age) };
				if (out.age % 5 == 0)
				{
					nr[ncnt] = out.r;
					nc[ncnt++] = out.c;
				}
			}
			else if (out.age >= 2)
			{
				dr[dcnt] = out.r;
				dc[dcnt] = out.c;
				dage[dcnt++] = out.age;
			}
		}

		//가을
		for (i = 0; i < ncnt; i++)
		{
			for (j = 0; j < 8; j++)
			{
				tr = nr[i] + rr[j];
				tc = nc[i] + cc[j];
				if (add[tr][tc])
				{
					//					printf("fall : %d %d %d\n", tr, tc, RWP);
					write[RWP++] = (TREE){ tr, tc, 1 };
				}
			}
		}

		// 여름
		for (i = 0; i < dcnt; i++)
		{
			yang[dr[i]][dc[i]] += dage[i] / 2;
		}

		// 겨울
		for (i = 1; i <= N; i++)
		{
			for (j = 1; j <= N; j++)
			{
				yang[i][j] += add[i][j];
			}
		}

		tmp = write;
		write = read;
		read = tmp;
	}
	return RWP - LWP - 1;
}

int main(void)
{
	Input();
	printf("%d\n", Get_Sol());
	return 0;
}
#endif
