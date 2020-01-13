#include<iostream>

using namespace std;

int n;
int A[1024];

void counter(int a)
{
	int sum = 0;
	for (int i = 0; i <= a / 2; i++)
		sum += A[i];
	A[a] = sum;
}

int main()
{
	A[0] = 1;
	for (int i = 1; i < 1024; i++)
		counter(i);
	cin >> n;
	cout << A[n];
	return 0;
}