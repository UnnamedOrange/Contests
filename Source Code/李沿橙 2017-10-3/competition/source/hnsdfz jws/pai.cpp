#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	int cnt=0;
	while(1)
	{
		system("./snakevsblock");
		cnt++;
		if(system("diff -b8 snakevsblock.out snakevsblock.ans"))
		{
			cout<<"no "<<cnt<<endl;
		}
		else
		{
			cout<<"yes"<<endl;
			cout<<"After tried "<<cnt<<" times"<<endl;
			exit(233);
		}
	}
	return 0;
}
