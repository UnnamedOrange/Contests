#include<bits/stdc++.h>
using namespace std;
int i,x,y,bgi,end;
char a[100005];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	scanf("%s",a);
	end=strlen(a)-1;
	while(a[bgi]=='0')
		bgi++;
	while(a[end]=='1')
		end--;
	for(i=end;i>=bgi;i--)
	{
		if(a[i]=='0')	x++;
		else	y++;
	}
	printf("%d",x>=y?y:x);
	return 0;
}
