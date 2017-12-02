#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;
char s[250];
int a[250];
int dp[250][250];
int main()
{
    freopen("zuma.in", "r", stdin);
    freopen("zuma.out", "w", stdout);

    int t = 1;
    int kase=0;
    while(t--)
    {
        scanf("%s",s);
        int n=strlen(s);
        int m=1;
        a[1]=1;
        for(int i=1;i<n;i++)
        {
            if(s[i]==s[i-1])a[m]++;
            else a[++m]=1;
        }
        for(int len=0;len<=m;len++)
        {
            for(int i=1;i<=m;i++)
            {
                int j=i+len;
                if(j<=m&&j>=1)
                {
                    dp[i][j]=2*n;
                    if(len==0)
                    {
                        dp[i][j]=3-a[i];
                    }
                    else
                    {
                        for(int k=i;k<j;k++)
                        {
                            dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
                        }
                        if((j-i-1)%2==1)
                        {
                            if(a[i]+a[j]==2)
                            dp[i][j]=min(dp[i][j],dp[i+1][j-1]+1);
                            else dp[i][j]=min(dp[i][j],dp[i+1][j-1]);
                            if(a[i]+a[j]<4)
                            for(int k=i+2;k<j;k+=2)
                            {
                                if(a[k]==1)
                                dp[i][j]=min(dp[i][j],dp[i+1][k-1]+dp[k+1][j-1]);
                            }
                        }
                    }
                }
            }
        }
        printf("%d\n",dp[1][m]);
    }
}