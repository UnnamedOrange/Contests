#include <cstdio>
#include <cstdlib>
using namespace std;
const int maxn=100005;
int N,p[maxn],M,ex[maxn],ey[maxn];
FILE *fscore, *freport, *fstd, *fin, *fout;
int score;
char str1[10],str2[10];
bool F[maxn];
void _qst(int l,int r)
{
    int i,j,m,mm,t;
    i=l;j=r;
    m=ex[(i+j)>>1];
    mm=ey[(i+j)>>1];
    while(i<=j)
    {
        while(ex[i]<m||(ex[i]==m&&ey[i]<mm))i++;
        while(ex[j]>m||(ex[j]==m&&ey[j]>mm))j--;
        if(i<=j)
        {
            t=ex[i];ex[i]=ex[j];ex[j]=t;
            t=ey[i];ey[i]=ey[j];ey[j]=t;
            i++;j--;
        }
    }
    if(i<r)_qst(i,r);
    if(l<j)_qst(l,j);
}
int _bsearch(int u,int v)
{
    int l=1,r=M,mid;
    while(l<r)
    {
        mid=(l+r+1)>>1;
        if(u<ex[mid]||(u==ex[mid]&&v<ey[mid]))r=mid-1;
        else l=mid;
    }
    if(u==ex[l]&&v==ey[l])return l;
    else return -1;
}
int _int(char *s)
{
    if(s[0]=='Y'&&s[1]=='E'&&s[2]=='S'&&s[3]==0)
        return 1;
    if(s[0]=='N'&&s[1]=='O'&&s[2]==0)
        return 2;
    else
        return 3;
}
int main(int argc, char *argv[])
{
	fscore = fopen(argv[5], "w");
	freport = fopen(argv[6], "w");
	fstd = fopen(argv[3], "r");
    score = atoi(argv[4]);
	fin = fopen(argv[1], "r");
	fout = fopen(argv[2], "r");
	
    int i,t,u,v;

    
    fscanf(fstd,"%s",str1);
    u=_int(str1);
    fscanf(fout,"%s",str2);
    v=_int(str2);
    if(u!=v)
    {
        fprintf(freport,"这是在逗我吗，第一行就是错的！\n");
        fprintf(freport,"本来是%s，你输出一个%s是什么鬼！\n",str1,str2);
        fprintf(freport,"0\n");
        fprintf(fscore,"0\n");
        return 0;
    }
    if(u==2)
    {
        if(fscanf(fout,"%s",str2)==1)
        {
            fprintf(freport,"为什么输出了NO之后，还输出了其他的一些奇怪的东西？\n");
            fprintf(freport,"0\n");
            fprintf(fscore,"0\n");
            return 0;
        }
        fprintf(freport,"哎呀，答案太简单，一不小心被你猜对了个NO！\n");
        fprintf(freport,"5\n");
        fprintf(fscore,"5\n");
        return 0;
    }
    
    fscanf(fin,"%d",&N);
    for(i=1;i<=N;i++)
    {
        if(fscanf(fout,"%d",&p[i])!=1)
        {
            fprintf(freport,"这是在输出什么东西呀，你确定你输出了n=%d个整数？\n",N);
            fprintf(freport,"0\n");
            fprintf(fscore,"0\n");
            return 0;
        }
        if(p[i]<1||p[i]>N)
        {
            fprintf(freport,"不要开玩笑了，这根本不是1到n=%d的一个排列！\n",N);
            fprintf(freport,"悄悄告诉你，你输出了一个%d。\n",p[i]);
            fprintf(freport,"0\n");
            fprintf(fscore,"0\n");
            return 0;
        }
        if(F[p[i]]==true)
        {
            fprintf(freport,"不要开玩笑了，这根本不是1到n=%d的一个排列！\n",N);
            fprintf(freport,"悄悄告诉你，你输出了至少两次%d\n",p[i]);
            fprintf(freport,"0\n");
            fprintf(fscore,"0\n");
            return 0;
        }
        F[p[i]]=true;
    }
    if(fscanf(fout,"%s",str1)==1)
    {
        fprintf(freport,"为什么输出了一个排列之后，还输出了其他的一些奇怪的东西？\n");
        fprintf(freport,"0\n");
        fprintf(fscore,"0\n");
        return 0;
    }
    
    M=N-1;
    for(i=1;i<=M;i++)
    {
        fscanf(fin,"%d%d",&ex[i],&ey[i]);
        ex[i]=p[ex[i]];ey[i]=p[ey[i]];
        if(ex[i]>ey[i])
            t=ex[i],ex[i]=ey[i],ey[i]=t;
    }
    _qst(1,M);
    for(i=1;i<=M;i++)
    {
        fscanf(fin,"%d%d",&u,&v);
        if(u>v)t=u,u=v,v=t;
        if(_bsearch(u,v)==-1)
        {
            fprintf(freport,"你给的方案是错的哦！\n");
            fprintf(freport,"0\n");
            fprintf(fscore,"0\n");
            return 0;
        }
    }
    fprintf(freport,"好厉害！你的答案是正确的！膜膜膜！\n");
    fprintf(freport,"5\n");
    fprintf(fscore,"5\n");
    return 0;
}
