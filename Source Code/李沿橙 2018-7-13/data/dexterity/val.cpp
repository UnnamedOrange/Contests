
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include "testlib.h"
using namespace std;


int main()
{
	registerValidation();
	string S;
	int n;
	n=inf.readInt(1,100000,"n");
	inf.readEoln();
	S=inf.readToken();
	inf.readEoln();
	ensuref(S.size()==n,"The length of the string should match.");
	for(int i=0;i<n;i++)
	{
		ensuref(S[i]=='r'||S[i]=='s'||S[i]=='p', "Elements of S should be r, s or p");
	}
	for(int i=1;i<=n;i++)
	{
		int w,d;
		w=inf.readInt(0,1000000000,"w_i");
		inf.readSpace();
		d=inf.readInt(0,1000000000,"d_i");
		inf.readEoln();
		ensuref(d<=w,"d should be less than or equal to w.");
	}
	inf.readEof();
	return 0;
}
