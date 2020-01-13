#include<iostream>
using namespace std;
int main()
{
	long long int a[21][21];
	int n, m, x, y;
	cin >> n >> m >> x >> y;
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			a[i][j] = -1;
	if (x < n + 1 && y < m + 1)
		a[x][y] = 0;
	for (int i = -2; i <= 2; i += 4)
		for (int j = -1; j <= 1; j += 2)
			if (x + i < n + 1 && y + j < m + 1 && x + i>-1 && y + j>-1)
				a[x + i][y + j] = 0;
	for (int i = -1; i <= 1; i += 2)
		for (int j = -2; j <= 2; j += 4)
			if (x + i < n + 1 && y + j < m + 1 && x + i>-1 && y + j>-1)
				a[x + i][y + j] = 0;
	a[n][m] = 1;
	for (int i = n - 1; i > -1; i--)
		if (a[i][m])
			a[i][m] = a[i + 1][m];
	for (int j = m - 1; j > -1; j--)
		if (a[n][j])
			a[n][j] = a[n][j + 1];
	for (int i = n - 1; i > -1; i--)
		for (int j = m - 1; j > -1; j--)
			if (a[i][j])
				a[i][j] = a[i + 1][j] + a[i][j + 1];
	cout << a[0][0];
	return 0;
}