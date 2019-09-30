// #14891. 톱니바퀴
#if 01

int K;
int TOP[4][8];
int PT[4];

void Input(void)
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 8; j++)
		{
			scanf("%1d", &TOP[i][j]);
		}
	}
}

void Operate(void)
{
	int k;
	int dir, tdir;
	int n;
	int i, j;

	scanf("%d", &K);
	for (k = 0; k < K; k++)
	{
		scanf("%d %d", &n, &dir);
		dir *= -1;
		n--;

		tdir = dir;
		for (i = n - 1; i >= 0; i--)
		{
			if (TOP[i][(PT[i] + 2) % 8] == TOP[i + 1][(PT[i + 1] + 6) % 8]) break;
		}
		for (j = n - 1; j > i; j--)
		{
			tdir *= -1;
			PT[j] = (PT[j] + tdir + 8) % 8;
		}

		tdir = dir;
		for (i = n + 1; i < 4; i++)
		{
			if (TOP[i][(PT[i] + 6) % 8] == TOP[i - 1][(PT[i - 1] + 2) % 8]) break;
		}
		for (j = n + 1; j < i; j++)
		{
			tdir *= -1;
			PT[j] = (PT[j] + tdir + 8) % 8;
		}

		PT[n] = (PT[n] + dir + 8) % 8;
	}
}

int Calc_Score(void)
{
	int score = 0;
	int two = 1;
	int i;

	for (i = 0; i < 4; i++)
	{
		if (TOP[i][PT[i]]) score += two;
		two <<= 1;
	}
	return score;
}

int main(void)
{
	Input();
	Operate();
	printf("%d\n", Calc_Score());
}
#endif
