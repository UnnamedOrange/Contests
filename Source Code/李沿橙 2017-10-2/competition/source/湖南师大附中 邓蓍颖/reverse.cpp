#include<bits/stdc++.h>
using namespace std;
struct abc{
	int z,o;
};
char c[100100];int ans=9999999,z,len,x,y;abc sum[100100];
int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	int j,i,tot=0;
	cin>>c;
	len=strlen(c);
	if(len==1)
	{
		printf("0");
		return 0;
	}
	i=0;
	if(c[i]=='0')sum[i].z=1;
	if(c[i]=='1')sum[i].o=1;
	for(i=1;i<len;i++)
	{
		sum[i].z=sum[i-1].z;
		sum[i].o=sum[i-1].o;
		if(c[i]=='0')sum[i].z++;
		if(c[i]=='1')sum[i].o++;
	}
	for(i=0;i<len;i++)
	{
		if(sum[i].o+sum[len-1].z-sum[i].z<ans)
			ans=sum[i].o+sum[len-1].z-sum[i].z;
	}
	printf("%d",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
