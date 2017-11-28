#include <cstdio>
#include <cstdlib>
using namespace std;
const int maxn=100005;
int N,p[maxn],M,ex[maxn],ey[maxn];
FILE *in,*ou1,*ou2,*rep,*sco;
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
int main(int argc,char **argv)
{
    int i,t,u,v;
    
    in=fopen("C.in","r");
    ou1=fopen(argv[2],"r");
    ou2=fopen("C.out","r");
    rep=fopen("report.log","w");
    sco=fopen("score.log","w");
    
    fscanf(ou1,"%s",str1);
    u=_int(str1);
    fscanf(ou2,"%s",str2);
    v=_int(str2);
    if(u!=v)
    {
        fprintf(rep,"�����ڶ����𣬵�һ�о��Ǵ�ģ�\n");
        fprintf(rep,"������%s�������һ��%s��ʲô��\n",str1,str2);
        fprintf(rep,"0\n");
        fprintf(sco,"0\n");
        return 0;
    }
    if(u==2)
    {
        if(fscanf(ou2,"%s",str2)==1)
        {
            fprintf(rep,"Ϊʲô�����NO֮�󣬻������������һЩ��ֵĶ�����\n");
            fprintf(rep,"0\n");
            fprintf(sco,"0\n");
            return 0;
        }
        fprintf(rep,"��ѽ����̫�򵥣�һ��С�ı���¶��˸�NO��\n");
        fprintf(rep,"5\n");
        fprintf(sco,"5\n");
        return 0;
    }
    
    fscanf(in,"%d",&N);
    for(i=1;i<=N;i++)
    {
        if(fscanf(ou2,"%d",&p[i])!=1)
        {
            fprintf(rep,"���������ʲô����ѽ����ȷ���������n=%d��������\n",N);
            fprintf(rep,"0\n");
            fprintf(sco,"0\n");
            return 0;
        }
        if(p[i]<1||p[i]>N)
        {
            fprintf(rep,"��Ҫ����Ц�ˣ����������1��n=%d��һ�����У�\n",N);
            fprintf(rep,"���ĸ����㣬�������һ��%d��\n",p[i]);
            fprintf(rep,"0\n");
            fprintf(sco,"0\n");
            return 0;
        }
        if(F[p[i]]==true)
        {
            fprintf(rep,"��Ҫ����Ц�ˣ����������1��n=%d��һ�����У�\n",N);
            fprintf(rep,"���ĸ����㣬���������������%d\n",p[i]);
            fprintf(rep,"0\n");
            fprintf(sco,"0\n");
            return 0;
        }
        F[p[i]]=true;
    }
    if(fscanf(ou2,"%s",str1)==1)
    {
        fprintf(rep,"Ϊʲô�����һ������֮�󣬻������������һЩ��ֵĶ�����\n");
        fprintf(rep,"0\n");
        fprintf(sco,"0\n");
        return 0;
    }
    
    M=N-1;
    for(i=1;i<=M;i++)
    {
        fscanf(in,"%d%d",&ex[i],&ey[i]);
        ex[i]=p[ex[i]];ey[i]=p[ey[i]];
        if(ex[i]>ey[i])
            t=ex[i],ex[i]=ey[i],ey[i]=t;
    }
    _qst(1,M);
    for(i=1;i<=M;i++)
    {
        fscanf(in,"%d%d",&u,&v);
        if(u>v)t=u,u=v,v=t;
        if(_bsearch(u,v)==-1)
        {
            fprintf(rep,"����ķ����Ǵ��Ŷ��\n");
            fprintf(rep,"0\n");
            fprintf(sco,"0\n");
            return 0;
        }
    }
    fprintf(rep,"����������Ĵ�����ȷ�ģ�ĤĤĤ��\n");
    fprintf(rep,"5\n");
    fprintf(sco,"5\n");
    return 0;
}
