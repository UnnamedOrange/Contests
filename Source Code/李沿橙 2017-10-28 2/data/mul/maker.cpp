#include<bits/stdc++.h>
#include<string>
#define G(x) ((rand()*(1LL<<47)+ rand()*(1LL<<31)+rand()*(1LL<<15)+rand() )%(x)+1)
using namespace std;
int data_start=1,data_end=20;
string problem_name="mul";
ofstream fout;
string cmd_text,out_name;
void make_data1(int n);
void make_data2(int n);
void make_data3(int n);
void make_data4(int n);
void make_data5(int n);
void make_data6(int n);
string int_to_string(int k){
	stringstream ss;
	ss<<k;
	string ret=ss.str();
	return ret; 
}

int T[21]={0,1,10,1,2,5,8,10,10,1,1,5,5,10,10,1,3,5,7,10,10};
int n[21]={0,8,8,16,16,16,16,16,16,30,30,30,30,30,30,500,500,500,500,500,500};
int main(){
    srand(time(0));
    for(int id=data_start;id<=data_end;id++){
    	out_name=problem_name;
    	out_name+=int_to_string(id);
    	out_name+=".in"; 
        fout.open(out_name.c_str(),ios::out);
        
        fout<<T[id]<<endl;
        for(int i=1;i<=T[id];i++)
			make_data1(n[id]);
        
        fout.close();
		cmd_text=problem_name;
        cmd_text+=".exe <";
        cmd_text+=out_name;
        cmd_text+=" >";
        cmd_text+=problem_name;
        cmd_text+=int_to_string(id);
        cmd_text+=".out";
        system(cmd_text.c_str());
        cout<<cmd_text<<endl;
    }
    system("pause");
    return 0;
}

void make_data1(int n){
	int l=G(n/2)+n/2,r=n;
	if(l>r) swap(l,r);
	fout<<r<<" "<<l<<endl;
}
void make_data2(int n){
}
void make_data3(int n){
}
void make_data4(int n){
}
void make_data5(int n){
} 
void make_data6(int n){
}

