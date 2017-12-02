#include<iostream>
#include<cstdio>
#include<cstring>
#include<climits>
#include<algorithm>
#define N 100010
#define INF INT_MAX
using namespace std;
char s[N];int cnt[N][2];
int main()
{
    freopen("reverse.in","r",stdin);
    freopen("reverse.out","w",stdout);
    scanf("%s",s+1);
    int n=strlen(s+1);
    for(int i=1;i<=n;i++)
    {
        int w=s[i]^'0',g=w^1;
        cnt[i][w]=cnt[i-1][w]+1;
        cnt[i][g]=cnt[i-1][g];
    }
    int ans=INF;
    for(int i=1;i<=n+1;i++)
        ans=min(ans,cnt[i-1][1]+cnt[n][0]-cnt[i-1][0]);
    printf("%d\n", ans);return 0;
}
