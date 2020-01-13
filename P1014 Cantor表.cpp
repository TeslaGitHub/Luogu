#include<iostream>
#include<math.h>
int main(void)
{
	int N, n, r, den, num;
	std::cin >> N;
	n = ceil((sqrt(1 + 8 * N) - 1.0) / 2.0);
	r = N - (n - 1) * n / 2;
	num = n % 2 == 0 ? r : n + 1 - r;
	den = n + 1 - num;
	std::cout << num << '/' << den;
	return 0;
}