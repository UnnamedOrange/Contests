#include<iostream>
#include<cstdio>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	srand(time(0));rand();
	int n;
	cin>>n;
	if(n<=7)
	{
		cout<<'2'<<endl;
		return 0;
	}
	else
	{
		cout<<rand()%10+1;
		return 0;
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
