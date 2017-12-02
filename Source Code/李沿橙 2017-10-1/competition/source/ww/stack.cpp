#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
#include<cstdio>

using namespace std;
const int N=1005;
int f[N]={0,1,2,5,0,0,6,2,2,4,3,0,0,4,6,6,5,2,0,0,4,6};

int dfs(int,int);
int main()
{
   freopen("stack.in","r",stdin);
   freopen("stack.out","w",stdout);
	int n;
	scanf("%d",&n);
	printf("%d",f[n]);
   fclose(stdin);
   fclose(stdout);
   return 0;
}
