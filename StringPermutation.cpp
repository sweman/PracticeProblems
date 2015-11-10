// StringPermutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using std::string;
// TODO: Make more eficient and do it in-place !!!!!!!
//void permute(string &out, int k, string &in
void permute(char out[], int k, string &in)

{
	if (k == in.length()) {
		out[k] = '\0';
		std::cout << out << std::endl;
	}
	else {
		//for (int i = k; i < in.length(); i++) {
		// inefficient way - FIXME
		for (int i = 0; i < in.length(); i++) {
			bool skip = false;
			for (int j = 0; j < k; j++) {
				if (in[i] == out[j]) {
					skip = true;
					break;
				}
			}
			if (skip) continue;
			out[k] = in[i];
			permute(out, k + 1, in);
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	string input = "ABC";
	string output;
	char outArr[4];
	output.reserve(input.length());
	//permute(output, 0, input);
	permute(outArr, 0, input);

	return 0;
}


