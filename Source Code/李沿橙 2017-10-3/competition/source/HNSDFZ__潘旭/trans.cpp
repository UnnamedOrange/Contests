#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;
const int len=1000000+50;
int n,k,l,t=0,st=0;
int x[len]={0},y[len]={0};
char h;
char s[len];

void oper(int t)
{
	if(t!=0)
	{
		if(y[st])
		{
			if(y[st]%2)
			{
				x[y[st]+1]=2;
				if(x[y[st]+2]==3)
				y[st]++;
				else
				st++;
			}
			else
			{
				x[y[st]]=3;
				if(x[y[st]]==2)
				y[st]--;
				else
				st++;
			}
			for(int i=1;i<=l;i++)
			printf("%d",x[i]);
			printf("\n");
		}
		else
		{
			for(int i=1;i<=l;i++)
			printf("%d",x[i]);
			printf("\n");
		}
		oper(t-1);
	}
}

void input()
{
	while(scanf("%d%d%c",&n,&k,&h)!=EOF)
	{
		scanf("%s",s);
		l=strlen(s);
		for(int i=0;i<l;i++)
		{
			x[i+1]=s[i]-'0';
			if(x[i+1]==3&&x[i]==2)
			{
				if(!st)
				st=1;
				y[++t]=i;
			}
		}
		oper(k);
		st=0;
		t=0;
		memset(y,0,sizeof(y));
	}
}

int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	input();
	fclose(stdin);
	fclose(stdout);
}
