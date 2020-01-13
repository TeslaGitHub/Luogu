#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

using namespace std;

int A[10000][10];
int B[10];
int res = 0, n;

void dp(int i, int sum)
{
	if (i == 9)
	{
		for (int j = 1; j < 4; j++)
		{
			if (sum + j == n)
			{
				res++;
				B[9] = j;
				for (int k = 0; k < 10; k++)
				{
					A[res - 1][k] = B[k];
				}
			}
		}
	}
	else
	{
		for (int j = 1; j < 4; j++)
		{
			B[i] = j;
			dp(i + 1, sum + j);
		}
	}
}

int main()
{
	cin >> n;
	dp(0, 0);
	cout << res << endl;
	for (int i = 0; i < res; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << A[i][j] << ' ';
		cout << endl;
	}
	return 0;
}