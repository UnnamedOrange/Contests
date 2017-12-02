#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
#include<vector>
#include<cstdio>

using namespace std;
const int N=1000006;
char p[N];
int main()
{
	freopen("trans.in","r",stdin);
	freopen("trans.out","w",stdout);
	int n,k,l;	
	while(scanf("%d",&n)==1)
	{
		scanf("%d",&k);
		scanf("%s",p);
		//cout<<n<<" "<<k<<endl;
		//
		//for(int i=0;i<strlen(p);i++) cout<<p[i];
		//		
		for(int i=1;i<=k;i++)
		{
			l=0;
			for(int j=0;j<n;j++)
			{////
				if(p[j]!='2')
				{
					l++;
					continue;
				}
				else 
				{///
					if(p[j+1]=='3') 
					{//
						if((j+1)%2==0) 
						{
							p[j]='3';
							if(p[j-1]=='2') l--;
							/*if(p[j-1]=='2'&&i!=k) 
							{	
								k--;
								cout<<j<<" "<<1<<endl;
								p[j]='2';	
							}*/
						}
						else 
						{
							p[j+1]='2';
							/*if(p[j+2]=='3'&&i!=k) 
							{	
								k--;
								cout<<j<<" "<<2<<endl;
								p[j+1]='3';	
							}*/
						}
					}//
					else l++;
				}///
			}////
			//cout<<"l:"<<l<<endl;	
			//cout<<"f:"<<f<<endl;	
			/*cout<<"k"<<i<<":";
			for(int o=0;o<n;o++)cout<<p[o];
			cout<<endl;*/
			if(l==strlen(p)) break;
		}
		for(int i=0;i<strlen(p);i++) printf("%c",p[i]);
		puts("");
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
