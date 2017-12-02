#include<iostream>
#include<cstdio>
using namespace std;
int a[100];
int sum;
int i,j,n,t;
void dfs(int i,int j)
{
    if(i==n) sum++;
    else  
    if(j==n)
     {
    t--;
    dfs(i+1,j);
		 t++;
     }
    else
    {
		if(t!=0)
		{t--;
        dfs(i+1,j);
		t++;
		}
        t++;
		a[t]=j+1;
        dfs(i,j+1);
        t--;
        
    }
    
    
    
 }
int main()
{
	freopen("stack.in","r",stdin);
	freopen("stack.out","w",stdout);
    cin>>n;
    dfs(0,0);
    cout<<sum%7;
	
    return 0;
}