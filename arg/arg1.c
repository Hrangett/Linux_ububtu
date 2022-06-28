#include <stdio.h>

int main()
{
//정수값 입력, 1부터 정수값까지 다 더한 합을 구하는 프로그램
	int ins_value = 0;
	int num = 1;
	int sum = 0;
	printf("insert value : ");
	scanf("%d",&ins_value);

	for(num ;num<=ins_value;num++)
		sum += num;

	
	printf("sum value : %d \n",sum);
	
	return 0;
}
