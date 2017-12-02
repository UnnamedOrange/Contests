#include<cstdio>
#include<cstdlib>
using namespace std;
typedef long long LL; 
#define MAXN 30000+5
const LL MAXN2=300000+5;//??
struct Node{//д��д��Ϊ�˱�����֮���node�ظ� 
	//int data;
	int rank;//rank������һ���ڵ�����������ӽڵ����� 
	int father;
}node[MAXN+1];
int get_bigfather(int k)//Ѱ�Ҹ��ڵ� ����һ�������������·��ѹ���� 
{
	if(node[k].father==k)
		return k;
	else
	{
		node[k].father=get_bigfather(node[k].father);
		//·��ѹ������һ·��ÿ�κ�������ʱ˳�����ָ��ĸ��ڵ�ֱ�Ӹ�Ϊ���ڵ� 
		//��ֱ�Ӱ������ҵ����ڵ��� 
		return node[k].father;//ÿ�η��ص�ֵ���Ѿ�������if�е�k�ˡ������ڵ� 
	}	
}
void merge(int u,int v)//�ϲ� 
{
	u=get_bigfather(u);
	v=get_bigfather(v);
	node[v].father=u;//������ĿҪ��ֱ������ 
	/*if(node[u].rank >= node[v].rank)//���һ����Ҳ�ǡ���������ĿҪ�� 
		node[v].father=u;
	else
	{
		node[u].father=v;
		if(node[u].rank==node[v].rank)//���һ���� 
			node[v].rank++;
	}*/
}
namespace QXX
{
	int tot=1,head[MAXN+5];
	struct Edge{
		int next;
		int node;
	}h[MAXN2+5];
	void add(int u,int v)
	{
		h[++tot].next = head[u];
		head[u] = tot;
		h[tot].node = v;
	}
	LL Travel2(int x)//�������ж���Ԫ�� 
	{
		LL sum=0;
		//�м���������д==x ��Ϊ���û�оͲ�����ֹ�� 
		while(head[x])//����������ִ�С�����ʾ�������滹������ 
		{
			for(int i=head[x]; i ;i = h[i].next)//ע��iֻ��tot���
			{
				if(h[i].node == x)
					break;
				else
					sum++;
			}
			x = h[head[x]].node; 
			//printf("-%d %d- ",x,head[x]);
			//printf("---");
		} 
		return sum;
	}
	//ע��head[]Ϊ��ײ� 
};
using namespace QXX;
int n,p;
int main()
{
	freopen("cube.in","r",stdin);
    freopen("cube.out","w",stdout);
	scanf("%d",&p);
	//�ر�ע��nû�н�������һ������д<=n 
	for(int i=1;i<=30005;i++)//��ʼ�����Լ��ĸ���һ��ʼ���Լ� 
		node[i].father=i;
	for(int i=1;i<=p;i++)
	{
		char temp;
		getchar();//������з����� 
		scanf("%c",&temp);
		//cin>>temp;
		if(temp == 'M')
		{
			int u,v;
			scanf("%d%d",&u,&v);
			//int k1 = h[head[u]].node; 
			int k1;//��������ײ�
			if(head[u] == 0)
				k1 = u;	
			else
				k1 = h[head[u]].node;
			int k2;
			/*if(head[v] == 0)
				k2 = v;
			else
				k2 = Travel(v);*/
			k2 = get_bigfather(v);
			add(k1,k2);
			//ע��mergeһ��Ҫ��add���棡 
			merge(u,v);
		}
		else{
			//printf("-----");
			int x;
			scanf("%d",&x);
			/*int k1 = Travel(x);
			int k2 = head[k1];*/
			LL sum = Travel2(x);
			printf("%lld\n",sum);
		}
	}
	//printf("-%d-",get_bigfather(4));
	//printf("-%d-",Travel2(4));
	return 0;
}
//�Ի��رߣ��� 
	/*int Travel(int x)//����߲� 
	{
		int i=head[x];//Ҫ�����������Ȼreturnʱ�Ҳ��� 
		while(h[i].next)
		{
			
			i = h[i].next;
		}
		return 
		/*for(i=head[x]; i ;i = h[i].next)//ע��iֻ��tot���
			if(!h[i].next)
				break;
		return h[i].node;
}*/ 
