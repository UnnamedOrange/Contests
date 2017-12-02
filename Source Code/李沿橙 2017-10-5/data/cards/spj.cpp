#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

bool isLemon = true;

FILE *in, *out, *ans, *score, *report;

void result(int mark, char *msg) {
	if (score) fprintf(score, "%d", mark);
	if (report) fprintf(report, "%s", msg);
	if (in) fclose(in);
	if (out) fclose(out);
	if (ans) fclose(ans);
	if (score) fclose(score);
	if (report) fclose(report);
	exit(0);
}

const double eps = 1e-6;
char res[55];
void judge(char *Input, char *Output, char *Answer, char *Score, char *Log, int full) {
	
	if (!(score = fopen(Score, "w"))) result(0, "");
	if (!(report = fopen(Log, "w"))) result(0, "");
	if (!(in = fopen(Input, "r"))) result(0, "打开标准输入文件错误");
	if (!(out = fopen(Output, "r"))) result(0, "打开选手输出文件错误");
	if (!(ans = fopen(Answer, "r"))) result(0, "打开标准输出文件错误");
	
	int task1=0,task2=0;
	
	double a1,a2,b1,b2; 
	fscanf(out,"%lf%lf",&a1,&a2);
	fscanf(ans,"%lf%lf",&b1,&b2);
	
	if (fabs(a1-b1)<eps) task1+=6;
	if (fabs(a2-b2)<eps) task2+=4;
	
	sprintf(res,"第一问得分:%d 第二问得分:%d",task1,task2);
	result(task1+task2,res);
}

int main(int argc, char* argv[]) {

	if (isLemon) {
		judge(argv[1], argv[2], argv[3], argv[5], argv[6], atoi(argv[4]));
	} else {
		judge("lct.in", "lct.out", argv[2], "score.log", "report.log", atoi(argv[1]));
	}
	
	return 0;
}

