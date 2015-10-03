// StringCompression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string compress(string s)
{
	string ret;
	int cnt;
	bool compressed = false;
	
	if (s.empty()) return s;

	char prev = s[0];
//	cnt = 1;
	cnt = 0;
	//for (int i = 1; i < s.length(); i++) {
	for (int i = 0; i < s.length(); i++) {
		//if (s[i] == prev) {
		//	cnt++;
		//	compressed = true;
		//}
		//else{
		//	ret.append(1, prev);
		//	ret.append(to_string(cnt));
		//	cnt = 1;
		//	prev = s[i];
		//}
		cnt++;
		if (i + 1 >= s.length() || s[i + 1] != s[i]) {
			ret.append(1, s[i]);
			ret.append(to_string(cnt));
			cnt = 0;
		}
	}
	//ret.append(1, prev);
	//ret.append(to_string(cnt));
	return ret.length() > s.length() ? s : ret;

	//if (compressed)
	//	return ret;
	//else
	//	return s;

}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << "compress(aabcdd) => " << compress("aabcdd") << endl;
	cout << "compress(abcd) => " << compress("abcd") << endl;
	cout << "compress(aaaaaaaaabbbbbcdd) => " << compress("aaaaaaaaabbbbbcdd") << endl;
	cout << "compress(ddddd) => " << compress("ddddd") << endl;
	return 0;
}

