#include <stdio.h>

int main()
{
//정수값 입력, 1부터 정수값까지 다 더한 합을 구하는 프로그램
	double ins_value = 0;
	int num = 0;
	int sum = 0;
	
	
	printf("insert value : ");
	scanf("%d",&ins_value);

	for(double i = 1 ;i<=ins_value/2;i++)
		sum += (ins_value+1);
	
	printf("sum value : %d \n",sum);
	
	return 0;
}
