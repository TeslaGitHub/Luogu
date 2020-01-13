#include<iostream>
#include<math.h>

using namespace std;

int n, k, result = 0;
int A[20];

bool isPrime(int x)
{
	int sqr = sqrt(x);
	for (int idx = 2; idx <= sqr; idx++)
		if (x % idx == 0)
			return false;
	return true;
}

void counter(int n_, int k_, int sum)
{
	if (k_ == 1)
	{
		for (int i = n - n_; i < n; i++)
			if (isPrime(sum + A[i]))
				result += 1;
	}
	else
		for (int i = n - n_; i <= n - k_; i++)
		{
			counter(n - i - 1, k_ - 1, sum + A[i]);
		}
}

int main()
{
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> A[i];
	counter(n, k, 0);
	cout << result;
}