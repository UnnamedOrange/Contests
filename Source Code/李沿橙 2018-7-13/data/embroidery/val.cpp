#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include "testlib.h"
using namespace std;

int n,m,P,tp;

bool isp(int pp)
{
	for(int i=2;i*i<=pp;i++)
		if(pp%i==0)return 0;
	return 1;
}

int main(int ac,char *av[])
{
	registerValidation();
	n=inf.readInt(1,1000000,"n");
	inf.readSpace();
	m=inf.readInt(1,1000000,"m");
	inf.readSpace();
	P=inf.readInt(1000,1000000007,"P");
	ensuref(isp(P),"P must be prime. %d",P);
	inf.readSpace();
	tp=inf.readInt(0,1,"tp");
	inf.readEoln();
	
	string s=inf.readString();
	ensuref(s.size()==n,"String length should match.");
	
	for(int i=0;i<s.size();i++)
		ensuref(s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z',"The string should only contain letters.");
		
	if(tp==0)
	{
		for(int i=0;i<m;i++)
		{
			int l=inf.readInt(1,n);
			inf.readSpace();
			int r=inf.readInt(1,n);
			inf.readEoln();
			ensuref(l<=r,"l should be less than or equal to r.");
		}
	}
	else
	{
		int a,b,c,x,y;
		x=inf.readInt(1,1000000006,"x");
		inf.readSpace();
		y=inf.readInt(1,1000000006,"y");
		inf.readSpace();
		a=inf.readInt(1,1000000006,"a");
		inf.readSpace();
		b=inf.readInt(1,1000000006,"b");
		inf.readSpace();
		c=inf.readInt(1,1000000006,"c");
		inf.readEoln();
	}
	inf.readEof();
	inf.readEof();
	return 0;
}