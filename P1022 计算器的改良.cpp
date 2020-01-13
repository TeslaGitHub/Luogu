#include<stdio.h>
#include<math.h>
int main()
{
	bool isDigit(char);
	bool isLetter(char);
	char tmp, x = 0;
	int eco = 0, con = 0, curNum = 0, curSign = 1, isLeft = 1;
	while ((tmp = getchar()) != '\n' && tmp != EOF)
	{
		if (isLetter(tmp))
		{
			if (x == 0)
				x = tmp;
			if (curNum == 0)
				curNum = 1;
			eco += curSign * isLeft * curNum;
			curNum = 0;
		}
		else if (isDigit(tmp))
		{
			curNum *= 10;
			curNum += tmp - '0';
		}
		else
		{
			con -= isLeft * curSign * curNum;
			curNum = 0;
			if (tmp == '=')
			{
				isLeft = -1;
				curSign = 1;
			}
			else if (tmp == '+')
				curSign = 1;
			else if (tmp == '-')
				curSign = -1;
		}
	}
	con -= isLeft * curSign * curNum;
	printf("%c=%.3f", x, (double)con / (double)eco == 0 ? fabs((double)con / (double)eco) : (double)con / (double)eco);
}
bool isDigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}
bool isLetter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return true;
	else
		return false;
}
