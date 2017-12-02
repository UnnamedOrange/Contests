#include<vector>
#include<cstdio>
#include<cstring>

const int maxl=1e4+10;
const int mod=1000000007;
const int maxn=5e4+1e6+1;

using namespace std;
int n,m,t;
int l[maxn];
vector<int>v[maxn];

int main()
{
	freopen("biology.in","r",stdin);
	freopen("biology.out","w",stdout);
	scanf("%d%d",&n,&m);
	char ch[maxl];
	if(n>50000) return 0;
	for(int i=1; i<=n; i++)
	{
		scanf("%s",ch);
		l[i]=strlen(ch);
		v[i].push_back(1);
		for(int j=l[i]-1,k=1; j>=0; j--,k++)
			v[i].push_back((v[i][k-1]*31ll+ch[j]*29)%mod);
	}
	int a,b,li,ri,mid;
	
	while(m--)
	{
		scanf("%d",&a);
		if(a==1)
		{
			scanf("%s",ch);
			n++;
			l[n]=strlen(ch);
			v[n].push_back(1);
			for(int i=l[n]-1,j=1; i>=0; i--,j++)
				v[n].push_back((v[n][j-1]*31ll+ch[i]*29)%mod);
		}
		else
		{
			scanf("%d",&t);
			scanf("%d",&a);
			ri=l[a];
			for(int i=2; i<=t; i++)
			{
				scanf("%d",&b);
				li=0;
				if(l[b]<ri) ri=l[b];
				while(li<ri)
				{
					mid=li+ri>>1;
					if(v[a][mid]==v[b][mid]) li=mid+1;
					else ri=mid-1;
				}
				if(v[a][ri]!=v[b][ri]) ri--;
			}
			printf("%d\n",ri);
		}
	}
	return 0;
}

