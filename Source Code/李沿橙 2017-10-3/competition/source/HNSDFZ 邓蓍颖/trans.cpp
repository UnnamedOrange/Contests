#include<bits/stdc++.h>
using namespace std;
char s[1001000];int n,k;
void kkk()
{
	int i,tot=0;
	for(i=0;i<n-1;i++)
	{
		tot++;
		if(k==0)break;
		if(!(tot%2)&&s[i]=='2'&&s[i+1]=='3')
		{
			if(k>=2&&s[i-1]=='2')
			{
				k-=2;
				continue;
			}
			s[i]='3',k--;
		}
		else if(tot%2&&s[i]=='2'&&s[i+1]=='3') s[i+1]='2',k--;
	}
	for(i=0;i<n;i++)printf("%c",s[i]);
	printf("\n");
}
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	int i;
	while(scanf("%d%d",&n,&k))
	{
		cin>>s;
		kkk();
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
