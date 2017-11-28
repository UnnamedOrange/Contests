//当输出文件过大，无法用肉眼检查时，可使用本程序比较你的输出文件与标准输出文件是否存在不同
//将本程序,你的输出文件和标准输出文件放在同一文件夹下，运行下面的代码即可
#include<cstdio>
#include<windows.h>
using namespace std;
main()
{
	//假设你的输出文件为my.out,标准输出文件为std.out
	if (system("fc bad6.out badbl.out")) puts("Sorry,wrong answer");
	else puts("Yes,accepted");
}
