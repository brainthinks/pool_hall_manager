#include<stdio.h>

main()
{

float t_cost=1.00;
float a = 2.50;          /*credit*/
float b=0;               /*uncollected*/
char F10[8];

	t_cost-= a;
	sprintf(F10,"%4.2f",a);          /* format line cost */
	b+=t_cost;
}
