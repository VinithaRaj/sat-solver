#include <stdio.h>
#include <iostream>

int main() {
	int arr[5], i;

	printf("Size of integer in this compiler is %lu\n",
		sizeof(int));

	for(i=0; i<5; i++)
	  arr[i] = i*i;
	
	for (i = 0; i < 5; i++)
	  printf("Address arr[%d] is %p and contains %d\n", i, &arr[i], arr[i]);

	return 0;
} //end of main()
