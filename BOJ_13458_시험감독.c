// #13458. 시험 감독
#if 01
int N;
int B;
int C;
int stu[1000100];

void Input(void)
{
	int i;

	scanf("%d", &N);
	for (i = 0; i < N; i++)
	{
		scanf("%d", &stu[i]);
	}
	scanf("%d %d", &B, &C);
}

long long Get_Sol(void)
{
	int i;
	long long sol = N;
	int res;

	for (i = 0; i < N; i++)
	{
		res = stu[i] - B;
		if (res <= 0) continue;
		sol += res / C + ((res % C != 0) ? 1 : 0);
	}
	return sol;
}

int main(void)
{
	Input();
	printf("%lld\n", Get_Sol());
}
#endif
