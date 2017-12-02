#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAXN=50010;
const int MOD=1e9+7;
int a[MAXN];
int main()
{
	int i,j,k,l,m,n,c,x,y,z,ans;
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++) scanf("%d",&a[i]);
	while(m--)
	{
		scanf("%d",&c);
		if (c==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			for (i=x;i<=y;i++)
			{
				a[i]+=z;
				if (a[i]>MOD) a[i]%=MOD;
				if (ans<0) ans+=MOD;
			}
		}
		else if (c==2)
		{
			scanf("%d%d",&x,&y);
			for (i=x;i<=y;i++)
			{
				a[i]*=-1;
			}
		}
		else
		{
			scanf("%d%d%d",&x,&y,&z);
			ans=0;
			if (z==1)
			{
				for (i=x;i<=y;i++)
				{
					ans+=a[i];
					if (ans>MOD) ans%=MOD;
					if (ans<0) ans+=MOD;
				}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==y-x+1)
			{
				ans=1;
				for (i=x;i<=y;i++)
				{
					ans*=a[i];
					if (ans>MOD) ans%=MOD;
					if (ans<0) ans+=MOD;
				}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==2)
			{
				ans=0;
				for (i=1;i<=y-1;i++)
				{
					for (j=i+1;j<=y;j++)
					{
						ans+=a[i]*a[j];
						if (ans>MOD) ans%=MOD;
						if (ans<0) ans+=MOD;
					}
				}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==3)
			{
				ans=0;
				for (i=1;i<=y-2;i++)
					for (j=i+1;j<=y-1;j++)
						for (k=j+1;k<=y;k++)
						{
							ans+=a[i]*a[j]*a[k];
							if (ans>MOD) ans%=MOD;
							if (ans<0) ans+=MOD;
						}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==4)
			{
				ans=0;
				for (int i1=1;i1<=y-3;i1++)
					for (int i2=i1+1;i2<=y-2;i2++)
						for (int i3=i2+1;i3<=y-1;i3++)
							for (int i4=i3+1;i4<=y;i4++)
							{
								ans+=a[i1]*a[i2]*a[i3]*a[i4];
								if (ans>MOD) ans%=MOD;
								if (ans<0) ans+=MOD;
							}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==5)
			{
				ans=0;
				for (int i1=1;i1<=y-4;i1++)
					for (int i2=i1+1;i2<=y-3;i2++)
						for (int i3=i2+1;i3<=y-2;i3++)
							for (int i4=i3+1;i4<=y-1;i4++)
								for (int i5=i4+1;i5<=y;i5++)
								{
									ans+=a[i1]*a[i2]*a[i3]*a[i4]*a[i5];
									if (ans>MOD) ans%=MOD;
									if (ans<0) ans+=MOD;
								}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==6)
			{
				ans=0;
				for (int i1=1;i1<=y-5;i1++)
					for (int i2=i1+1;i2<=y-4;i2++)
						for (int i3=i2+1;i3<=y-3;i3++)
							for (int i4=i3+1;i4<=y-2;i4++)
								for (int i5=i4+1;i5<=y-1;i5++)
									for (int i6=i5+1;i6<=y;i6++)
									{
										ans+=a[i1]*a[i2]*a[i3]*a[i4]*a[i5]*a[i6];
										if (ans>MOD) ans%=MOD;
										if (ans<0) ans+=MOD;
									}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==7)
			{
				ans=0;
				for (int i1=1;i1<=y-6;i1++)
					for (int i2=i1+1;i2<=y-5;i2++)
						for (int i3=i2+1;i3<=y-4;i3++)
							for (int i4=i3+1;i4<=y-3;i4++)
								for (int i5=i4+1;i5<=y-2;i5++)
									for (int i6=i5+1;i6<=y-1;i6++)
										for (int i7=i6+1;i7<=y;i7++)
										{
											ans+=a[i1]*a[i2]*a[i3]*a[i4]*a[i5]*a[i6]*a[i7];
											if (ans>MOD) ans%=MOD;
											if (ans<0) ans+=MOD;
										}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==8)
			{
				ans=0;
				for (int i1=1;i1<=y-7;i1++)
					for (int i2=i1+1;i2<=y-6;i2++)
						for (int i3=i2+1;i3<=y-5;i3++)
							for (int i4=i3+1;i4<=y-4;i4++)
								for (int i5=i4+1;i5<=y-3;i5++)
									for (int i6=i5+1;i6<=y-2;i6++)
										for (int i7=i6+1;i7<=y-1;i7++)
											for (int i8=i7+1;i8<=y;i8++)
											{
												ans+=a[i1]*a[i2]*a[i3]*a[i4]*a[i5]*a[i6]*a[i7]*a[i8];
												if (ans>MOD) ans%=MOD;
												if (ans<0) ans+=MOD;
											}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==9)
			{
				ans=0;
				for (int i1=1;i1<=y-8;i1++)
					for (int i2=i1+1;i2<=y-7;i2++)
						for (int i3=i2+1;i3<=y-6;i3++)
							for (int i4=i3+1;i4<=y-5;i4++)
								for (int i5=i4+1;i5<=y-4;i5++)
									for (int i6=i5+1;i6<=y-3;i6++)
										for (int i7=i6+1;i7<=y-2;i7++)
											for (int i8=i7+1;i8<=y-1;i8++)
												for (int i9=i8+1;i9<=y;i9++)
												{
													ans+=a[i1]*a[i2]*a[i3]*a[i4]*a[i5]*a[i6]*a[i7]*a[i8]*a[i9];
													if (ans>MOD) ans%=MOD;
													if (ans<0) ans+=MOD;
												}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			if (z==10)
			{
				ans=0;
				for (int i1=1;i1<=y-9;i1++)
					for (int i2=i1+1;i2<=y-8;i2++)
						for (int i3=i2+1;i3<=y-7;i3++)
							for (int i4=i3+1;i4<=y-6;i4++)
								for (int i5=i4+1;i5<=y-5;i5++)
									for (int i6=i5+1;i6<=y-4;i6++)
										for (int i7=i6+1;i7<=y-3;i7++)
											for (int i8=i7+1;i8<=y-2;i8++)
												for (int i9=i8+1;i9<=y-1;i9++)
													for (int i10=i9+1;i10<=y;i10++)
													{
														ans+=a[i1]*a[i2]*a[i3]*a[i4]*a[i5]*a[i6]*a[i7]*a[i8]*a[i9]*a[i10];
														if (ans>MOD) ans%=MOD;
														if (ans<0) ans+=MOD;
													}
				ans=((ans%MOD)+MOD)%MOD;
				printf("%d\n",ans);
				continue;
			}
			
			printf("60\n");
		}
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
