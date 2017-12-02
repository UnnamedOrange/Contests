#include<bits/stdc++.h>
using namespace std;
#define N 1000+5
double x[N],y[N],xq,yq;
int query[N];
int main()
{
	freopen("geometry.in","r",stdin);
	freopen("geometry.out","w",stdout); 
	int n,m;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>x[i];
	for(int i=0;i<n;i++)
		cin>>y[i];
	sort(x+0,x+n);
	sort(y+0,y+n);
	cin>>m;
	for(int i=0;i<m;i++)
	{
		cin>>xq>>yq;
		for(int j=0;j<n;j++)
		{
			if(x[j]<=xq||y[j]<=yq)
				query[i]++;
			else
			{
				if(x[j]<=((xq*y[j])/(y[j]-yq)))
				{
					query[i]++;
					
				}
				else
					break;
			}
		//	cout<<xq<<" "<<yq<<" "<<x[j]<<" "<<y[j]<<" "<<(xq*y[j])/(y[j]-yq)<<" "<<i<<" "<<j<<endl;
		}
	//	cout<<query[i]<<endl;
	}
	for(int i=0;i<m;i++)
	{
		cout<<query[i]<<endl;
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
