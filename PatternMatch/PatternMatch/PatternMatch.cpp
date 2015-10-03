// PatternMatch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using std::cout;
using std::string;
using std::endl;



bool isMatch(string str, string pat)
{
	size_t p = 0;
	size_t s = 0;

	while (s != str.length() && p != pat.length()) {
		if (pat[p] == str[s] || pat[p] == '.') {
			// match
			s++; p++;
		}
		else if (pat[p] == '*') {
			// input guaranteed to not start with '*'
			if (pat[p - 1] == str[s]) {
				s++;
			}
			else {
				p++;
			}
		}
		else   { // (pat[p] != str[s] && pat[p] != '.' && pat[p] != '*') {
			//s++;
			if ((p < pat.length() - 1) && pat[p + 1] == '*') {
				p++;
			}
			else {
				p = 0;
				s++;
			}
		}
    }	
	if (p == pat.length())
		return true;
	else
		return false;
}

bool isMatchRecursive(string str, string pat, size_t s, size_t p)
{
	if (p == pat.length())
		return true;
	if (s == str.length())
		return false;
	if (pat[p] == str[s] || pat[p] == '.') {
		p++; 
		s++;
	}
	else if (pat[p] == '*'){
		if (pat[p - 1] == str[s]) {
			s++;
		}
		else {
			p++;
		}
	}
	else {  // pat[p] != str[s] && pat[p] != '.' && pat[p] != '*'
		if (p < (pat.length() - 1) && pat[p + 1] == '*') {
			p++;
		}
		else {
			p = 0; s++;
		}

	}
	return isMatchRecursive(str, pat, s, p);
}

int main(int argc, _TCHAR* argv[])
{
	cout << "isMatch(abcd, bd) = " << isMatch("abcd", "bd") << endl;
	cout << "isMatch(abcd, ef) = " << isMatch("abcd", "ef") << endl;
	cout << "isMatch(abcd, b) = " << isMatch("abcd", "b") << endl;
	cout << "isMatch(abcd, b.d) = " << isMatch("abcd", "b.d") << endl;
	cout << "isMatch(abcd, a*b) = " << isMatch("abcd", "a*b") << endl;
	cout << "isMatch(abcd, x*bc) = " << isMatch("abcd", "x*bc") << endl;
	cout << "isMatch(abcd, b*) = " << isMatch("abcd", "b*") << endl;
	cout << "isMatch(abcd, x*) = " << isMatch("abcd", "x*") << endl;
	cout << "isMatch(abcd, x*abcd) = " << isMatch("abcd", "x*abcd") << endl;
	cout << "isMatch(abcd, x*ab) = " << isMatch("abcd", "x*ab") << endl;
	cout << "isMatch(abcd, abcd) = " << isMatch("abcd", "abcd") << endl;



	cout << endl;
	cout << "isMatchRecursive(abcd, bd) = " << isMatchRecursive("abcd", "bd", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, ef) = " << isMatchRecursive("abcd", "ef", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, b) = " << isMatchRecursive("abcd", "b", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, b.d) = " << isMatchRecursive("abcd", "b.d", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, a*b) = " << isMatchRecursive("abcd", "a*b", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, x*bc) = " << isMatchRecursive("abcd", "x*bc", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, b*) = " << isMatchRecursive("abcd", "b*", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, x*) = " << isMatchRecursive("abcd", "x*", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, x*abcd) = " << isMatchRecursive("abcd", "x*abcd", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, x*ab) = " << isMatchRecursive("abcd", "x*ab", 0, 0) << endl;
	cout << "isMatchRecursive(abcd, abcd) = " << isMatchRecursive("abcd", "abcd", 0, 0) << endl;



	return 0;
}

