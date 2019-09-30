// #14890. 경사로
#if 01
#define MAX (110)

int N, L;
int map[MAX][MAX];
int arr[MAX][MAX];
int zero_cnt, must_zero;
int sol;

void Input(void)
{
	int i, j;
	scanf("%d %d", &N, &L);
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			scanf("%d", &map[i][j]);
		}
	}
}

void Get_Solution(void)
{
	int i, j; 
	int num;
	// ROW
	for (i = 0; i < N; i++)
	{
		zero_cnt = 1;
		must_zero = 0;
		sol++;
		for (j = 1; j < N; j++)
		{
			num = map[i][j] - map[i][j - 1];
			if (must_zero)
			{
				if (num == 0) must_zero--;
				else
				{
					sol--;
					must_zero = 0;
					break;
				}
			}
			else if (num == 0) zero_cnt++;
			else if (num == 1)
			{
				if (zero_cnt < L)
				{
					sol--;
					break;
				}
				zero_cnt = 1;
			}
			else if (num == -1)
			{
				zero_cnt = 0;
				must_zero = L - 1;
			}
			else
			{
				sol--;
				break;
			}
		}
		if (must_zero) sol--;
	}

	// COLUMN
	for (j = 0; j < N; j++)
	{
		zero_cnt = 1;
		must_zero = 0;
		sol++;
		for (i = 1; i < N; i++)
		{
			num = map[i][j] - map[i-1][j];
			if (must_zero)
			{
				if (num == 0) must_zero--;
				else
				{
					sol--;
					must_zero = 0;
					break;
				}
			}
			else if (num == 0) zero_cnt++;
			else if (num == 1)
			{
				if (zero_cnt < L)
				{
					sol--;
					break;
				}
				zero_cnt = 1;
			}
			else if (num == -1)
			{
				zero_cnt = 0;
				must_zero = L - 1;
			}
			else
			{
				sol--;
				break;
			}
		}
		if (must_zero) sol--;
	}
}

int main(void)
{
	Input();
	Get_Solution();
	printf("%d\n", sol);
}
#endif
