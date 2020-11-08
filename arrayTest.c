#include <stdio.h>

int * arrayReturner(){
	static int r[] = {1,2,3,4,5,6,7,8,9,10};
	
	return r;
}

int main(){
	int *results;
results = arrayReturner();

for(int i=0;i<10;i++){
printf("r[%d]= %i\n", i, results[i]);
}


}
