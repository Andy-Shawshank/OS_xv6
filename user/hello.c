#include "kernel/types.h"
#include "user.h"

int main(int argc,char * argv){
	if(argc!=1){
		printf("该程序无需参数!\n");
		exit(-1);
	}

	printf("hello Linux:)\n");
    printf("version control is so fucking hard\n");
	exit(0);
}
