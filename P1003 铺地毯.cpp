// P1003 铺地毯.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

using namespace std;

int A[10001][4];

int main()
{
	int n, x, y, result = -1;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> A[i][0] >> A[i][1] >> A[i][2] >> A[i][3];
	cin >> x >> y;
	for (int i = 0; i < n; i++)
		if (A[i][0] <= x && A[i][1] <= y && A[i][0] + A[i][2] >= x && A[i][1] + A[i][3] >= y)
			result = i + 1;
	cout << result;
	return 0;
}

/*int A[10001][10001];

int main()
{
	int n, a, b, g, k;
	cin >> n;
	for (int i = 0; i < 10001; i++)
	{
		for (int j = 0; j < 10001; j++)
			A[i][j] = -1;
	}
	for (int i = 0; i < n; i++) 
	{
		cin >> a >> b >> g >> k;
		for (int x = a; x <= a + g; x++)
		{
			for (int y = b; y <= b + k; y++)
				A[x][y] = i+1;
		}
	}
	cin >> a >> b;
	cout << A[a][b];
	return 0;
}*/

