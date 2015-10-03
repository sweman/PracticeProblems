// Recursion.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>

using namespace std;

int sum(int n)
{
	if (n == 0)  return n;
	return n + sum(n - 1);
}

int factorial(int n)
{
	if (n <= 1)
		return 1;
	return n * factorial(n - 1);
}

int fibonacci(int n)
{
	if (n <= 1)
		return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}
int main(int argc, char* argv[])
{
	for (int i = 0; i < 10; i++)
		cout << "sum(" << i << ")   =    " << sum(i) << endl;
	for (int i = 0; i < 10; i++)
		cout << "factorial(" << i << ")   =    " << factorial(i) << endl;
	for (int i = 0; i < 10; i++)
		cout << "fibonacci(" << i << ")   =    " << fibonacci(i) << endl;
	return 0;
}

