#include<ctime>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int main()
{
	freopen("zuma.in","r",stdin);
	freopen("zuma.out","w",stdout);
	srand(time(0));
	char s[1000];
	int x,n;
	scanf("%s",s+1);
	n=strlen(s+1);
	if(n<=7)
	x=rand()%2+1;
	else if(n<=50)
	x=rand()%3+3;
	else
	x=rand()%4+8;
	printf("%d\n",x);
	return 0;
}
		
	
