# include<iostream>
# include<cstdio>
# include<cstring>
# include<cstdlib>
using namespace std;
const int pp=1000000007;
int c[2008][2008],f[2008],p[2008],ni[2008];
int n,m,k,nn;
inline int power(int x,int n)
{
    int ans=1,tmp=x;
    while (n)
    {
          if (n&1) ans=(long long)ans*tmp%pp;
          tmp=(long long)tmp*tmp%pp;n>>=1;
    }    
    return ans;
}
void Count_c()
{
     for (int i=0;i<=nn;i++) c[i][0]=1;
     for (int i=1;i<=nn;i++)
      for (int j=1;j<=i;j++)
      {
          c[i][j]=c[i-1][j-1]+c[i-1][j];
          if (c[i][j]>=pp) c[i][j]-=pp;
      }
}
void Count_p()
{
     int mm=(m-2)*n;
     for (int i=0;i<=nn;i++)
      p[i]=power(i,mm);
}
void Count_f()
{
     f[0]=0;f[1]=1;
     for (int i=2;i<=nn;i++)
     {
         f[i]=power(i,n);
         for (int j=1;j<i;j++)
         {
             f[i]-=(long long)f[j]*c[i][j]%pp;
             if (f[i]<=-pp) f[i]+=pp;
         }
         if (f[i]<0) f[i]+=pp;
     }
}
void Count_ni()
{
     ni[1]=1;
     for (int i=2;i<=nn;i++)
     ni[i]=power(i,pp-2);
}
int main()
{
    freopen("photo.in","r",stdin);
    freopen("photo.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    nn=min(n,k);
    if (m==1)
       printf("%d\n",power(k,n));
    else
    {
        Count_c();
        Count_p();
        Count_f();
        Count_ni();
        long long tmp=1,tmp1=1,sum=0,sum1;
        for (int s=1;s<=nn;s++)
        {
            tmp=tmp*ni[s]%pp;
            tmp=tmp*(k-s+1)%pp;
            tmp1=1;sum1=0;
            for (int j=0;j<=s;j++)
            {
                sum1+=tmp1*c[s][s-j]%pp*p[s-j]%pp;
                if (sum1>=pp) sum1-=pp;
                tmp1=tmp1*ni[j+1]%pp; 
                if (k-s<j+1) break;
                tmp1=tmp1*(k-s-j)%pp;
            }
            sum+=tmp*f[s]%pp*f[s]%pp*sum1%pp;
            if (sum>=pp) sum-=pp;
        }
	    printf("%d\n",sum);
	}
	fclose(stdin);
	fclose(stdout);
    return 0;
}
