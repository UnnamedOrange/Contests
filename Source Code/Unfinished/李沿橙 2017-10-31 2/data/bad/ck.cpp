//������ļ������޷������ۼ��ʱ����ʹ�ñ�����Ƚ��������ļ����׼����ļ��Ƿ���ڲ�ͬ
//��������,�������ļ��ͱ�׼����ļ�����ͬһ�ļ����£���������Ĵ��뼴��
#include<cstdio>
#include<windows.h>
using namespace std;
main()
{
	//�����������ļ�Ϊmy.out,��׼����ļ�Ϊstd.out
	if (system("fc bad6.out badbl.out")) puts("Sorry,wrong answer");
	else puts("Yes,accepted");
}
