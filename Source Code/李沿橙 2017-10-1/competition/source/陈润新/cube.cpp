#include<cstdio>
#include<cstdlib>
using namespace std;
typedef long long LL; 
#define MAXN 30000+5
const LL MAXN2=300000+5;//??
struct Node{//写大写是为了避免与之后的node重复 
	//int data;
	int rank;//rank代表这一个节点和他的所有子节点的深度 
	int father;
}node[MAXN+1];
int get_bigfather(int k)//寻找根节点 ——一般是在这里加上路径压缩的 
{
	if(node[k].father==k)
		return k;
	else
	{
		node[k].father=get_bigfather(node[k].father);
		//路径压缩——一路上每次函数返回时顺便把其指向的父节点直接改为根节点 
		//即直接把这个点挂到根节点上 
		return node[k].father;//每次返回的值都已经是上面if中的k了——根节点 
	}	
}
void merge(int u,int v)//合并 
{
	u=get_bigfather(u);
	v=get_bigfather(v);
	node[v].father=u;//按照题目要求直接这样 
	/*if(node[u].rank >= node[v].rank)//如果一样深也是——按照题目要求 
		node[v].father=u;
	else
	{
		node[u].father=v;
		if(node[u].rank==node[v].rank)//如果一样深 
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
	LL Travel2(int x)//找下面有多少元素 
	{
		LL sum=0;
		//中间条件不能写==x 因为如果没有就不能终止了 
		while(head[x])//符合条件就执行——表示此数下面还有数字 
		{
			for(int i=head[x]; i ;i = h[i].next)//注意i只是tot编号
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
	//注意head[]为最底层 
};
using namespace QXX;
int n,p;
int main()
{
	freopen("cube.in","r",stdin);
    freopen("cube.out","w",stdout);
	scanf("%d",&p);
	//特别注意n没有进行输入一定不能写<=n 
	for(int i=1;i<=30005;i++)//初始化，自己的父亲一开始是自己 
		node[i].father=i;
	for(int i=1;i<=p;i++)
	{
		char temp;
		getchar();//解决换行符问题 
		scanf("%c",&temp);
		//cin>>temp;
		if(temp == 'M')
		{
			int u,v;
			scanf("%d%d",&u,&v);
			//int k1 = h[head[u]].node; 
			int k1;//这里找最底层
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
			//注意merge一定要在add后面！ 
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
//自环重边？？ 
	/*int Travel(int x)//找最高层 
	{
		int i=head[x];//要定义出来，不然return时找不到 
		while(h[i].next)
		{
			
			i = h[i].next;
		}
		return 
		/*for(i=head[x]; i ;i = h[i].next)//注意i只是tot编号
			if(!h[i].next)
				break;
		return h[i].node;
}*/ 
