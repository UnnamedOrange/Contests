#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;

int c;
int n;
const char *name[]=
{
	"xiaoyong",
	"xiaoshi"
};

namespace Regular
{
	int f[105];
	int dp(int x)
	{
		if(f[x]!=-1) return f[x];
		if(x==1) return f[x] = true;
		if(x==2) return f[x] = false;
		return f[x]=!dp(x-1);
//		if(x==3) return f[x] = true;
//		if(x==4) return f[x] = false;
	}

	//��ȫ���������£���ôʤ����n����ż�й�
	//�������֪���Լ������»��䣬��ô��������
	//�����£����Ƕ���Ҳ֪��������Ѻ����µ�
	//��һ��������ͻ��䡣���Զ���ʼ�ձ��ֶ���
	//���Բ�Ӱ��ʤ��

	//��������벻����غ�������Ťת���ƣ�ǰ��
	//���������Ⱥ������ˡ���Ȼ�������п��ܻ���
	//�������ֲ�������¡�

	//�ʵ�֤��ʤ��ֻ��n����ż�й�
	void run()
	{
		memset(f,-1,sizeof(f));
		while(c--)
		{
			scanf("%d",&n);
			printf("%s\n",name[n%2]);
		}
	}
	void input()
	{
		scanf("%d",&c);
	}
}

int main()
{
#ifndef DEBUG
	freopen("game.in","r",stdin);
	freopen("game.out","w",stdout);
#endif
	Regular::input();
	Regular::run();
	return 0;
}
