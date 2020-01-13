#include<iostream>

using namespace std;

int main(void)
{
	int A[21][21][21];
	int i, j, k, a, b, c;

	//Initialize
	i = 0;
	for (j = 0; j < 21; j++)
		for (k = 0; k < 21; k++)
			A[i][j][k] = 1;
	j = 0;
	for (i = 0; i < 21; i++)
		for (k = 0; k < 21; k++)
			A[i][j][k] = 1;
	k = 0;
	for (j = 0; j < 21; j++)
		for (i = 0; i < 21; i++)
			A[i][j][k] = 1;

	//Calculate
	for (i = 1; i < 21; i++)
	{
		for (j = 1; j < 21; j++)
		{
			for (k = 1; k < 21; k++)
			{
				if (i < j && j < k)
					A[i][j][k] = A[i][j][k - 1] + A[i][j - 1][k - 1] - A[i][j - 1][k];
				else
					A[i][j][k] = A[i - 1][j][k] + A[i - 1][j - 1][k] + A[i - 1][j][k - 1] - A[i - 1][j - 1][k - 1];
			}
		}
	}

	cin >> a >> b >> c;
	while (!(a == -1 && b == -1 && c == -1))
	{
		if (a <= 0 || b <= 0 || c <= 0)
			cout << "w(" << a << ", " << b << ", " << c << ") = 1" << endl;
		else if (a > 20 || b > 20 || c > 20)
			cout << "w(" << a << ", " << b << ", " << c << ") = " << A[20][20][20] << endl;
		else
			cout << "w(" << a << ", " << b << ", " << c << ") = " << A[a][b][c] << endl;
		cin >> a >> b >> c;
	}

	return 0;
}