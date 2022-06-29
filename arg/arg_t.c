#include<stdio.h>
#include<math.h>

int main()
{
	int i,j;
	int num;
	int sum = 0;	
	while(num!=0)
	{
		printf("NUM : ");
		scanf("%d",&num);

		for(i = num, j = 1;i>(num+1)/2  ; i--,j++) 
		{
			printf("i : %d,j : %d\n",i,j); 
			sum += (i+j);
		}
	
			
		printf("SUM : %d \n",sum + ((num+1)/2)*(num%2));
		sum = 0;
	}
	
}
