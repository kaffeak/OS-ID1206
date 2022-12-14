#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int distance(int input[], int extra){
	int output = 0;
	for (int i = 0; i < 1000+extra; i++)
	{
		//printf("dif: %d\n", abs(input[i] - input[i+1]));
		output += abs(input[i] - input[i+1]);
	}
	return output;
}

int * fcfs(int input[], int head){
	static int output[1001];
	output[0] = head;
	for (int i = 1; i < 1001; i++)		
	{
		output[i] = input[i-1];
	}	
	return output;
}

int * sstf(int input[], int head){
	static int output[1001];
	output[0] = head;
	int dist = abs(input[0] - input[1]), pos = 1, last;
	for (int i = 1; i < 1001; i++)
	{
		for (int j = 0; j < 1000; j++)
		{			
			if (last != j){			
				if (dist > abs(output[i-1]-input[j]))
				{
					dist = abs(output[i-1]-input[j]);
					pos = j;
				}
			}
		}
		output[i] = input[pos];
		input[pos] = 1000000;
		last = pos;
		dist = 9999;
		
	}
	return output;
}

int * scan(int input[], int head){
	static int output[1002];
	output[0] = head;
	short smallest = 0; //smallest works as boolean
	int dist = abs(input[0] - input[1]), pos = 1, last;
	for (int i = 1; i < 1002; i++)
	{
		for (int j = 0; j < 1000; j++){			
			if (last != j){		
				if (smallest == 0){
					if (dist > output[i-1]-input[j] && output[i-1]-input[j] >= 0){
						dist = output[i-1]-input[j];
						pos = j;
					}					
				}
				else{
					if (dist > input[j]-output[i-1] && input[j]-output[i-1] >= 0){
						dist = input[j]-output[i-1];
						pos = j;
					}
				}				
			}			
		}
		if (pos == last)
			{
				smallest = 1;
				output[i] = 0;
			}
			else{
				output[i] = input[pos];
				input[pos] = 1000000;
				last = pos;
				dist = 9999;
			}	
	}
	return output;
}

int * cscan(int input[], int head){
	static int output[1003];
	output[0] = head;
	short smallest = 0; //smallest works as boolean
	int dist = abs(input[0] - input[1]), pos = 1, last;
	for (int i = 1; i < 1003; i++)
	{
		for (int j = 0; j < 1000; j++){			
			if (last != j){		
				if (dist > output[i-1]-input[j] && output[i-1]-input[j] >= 0){
					dist = output[i-1]-input[j];
					pos = j;
				}				
			}			
		}
		if (pos == last)
			{
				output[i++] = 0;
				output[i] = 4999;			
			}
		else{
			output[i] = input[pos];
			input[pos] = 1000000;
			last = pos;
			dist = 9999;
		}
	}
	return output;
}

int * look(int input[], int head){
	static int output[1001];
	output[0] = head;
	short smallest = 0; //smallest works as boolean
	int dist = abs(input[0] - input[1]), pos = 1, last;
	for (int i = 1; i < 1001; i++)
	{
		for (int j = 0; j < 1000; j++){			
			if (last != j){		
				if (smallest == 0){
					if (dist > output[i-1]-input[j] && output[i-1]-input[j] >= 0){
						dist = output[i-1]-input[j];
						pos = j;
					}					
				}
				else{
					if (dist > input[j]-output[i-1] && input[j]-output[i-1] >= 0){
						dist = input[j]-output[i-1];
						pos = j;
					}
				}				
			}			
		}
		if (pos == last)
			{
				smallest = 1;
				i--;
			}
			else{
				output[i] = input[pos];
				input[pos] = 1000000;
				last = pos;
				dist = 9999;
			}	
	}
	return output;
}

int * clook(int input[], int head){
	static int output[1001];
	output[0] = head;
	short smallest = 0; //smallest works as boolean
	int dist = abs(input[0] - input[1]), pos = 1, last;
	for (int i = 1; i < 1001; i++)
	{
		for (int j = 0; j < 1000; j++){			
			if (last != j){		
				if (dist > output[i-1]-input[j] && output[i-1]-input[j] >= 0){
					dist = output[i-1]-input[j];
					pos = j;
				}				
			}			
		}
		if (pos == last)
			{
				int temp = 0, tpos;
				for (int k = 0; k < 1000; k++)
				{
					if (temp < input[k] && input[k] < 6000){
						temp = input[k];
						tpos = k;
					} 					
				}	
				output[i] = input[tpos];
				input[tpos] = 1000000;	
			}
		else{
			output[i] = input[pos];
			input[pos] = 1000000;
			last = pos;
			dist = 9999;
		}
	}
	return output;
}

int main(int argc, char const *argv[]){
	if (argc < 2)
		return 0;
	time_t t;
	int head = atoi(argv[1]);
	int test[1000], testFCFS[1000], testSSTF[1000], testSCAN[1000], testCSCAN[1000], testLOOK[1000], testCLOOK[1000];
	int temp[] = {176, 79, 34, 60, 92, 11, 41, 114};
	srand((unsigned) time(&t));
	for (int i = 0; i < 1000; i++)
	{
		test[i] = rand() % 5000;
		testFCFS[i] = test[i];
		testSSTF[i] = test[i];
		testSCAN[i] = test[i];
		testCSCAN[i] = test[i];
		testLOOK[i] = test[i];
		testCLOOK[i] = test[i];
	}
	int distFCFS, distSSTF, distSCAN, distCSCAN, distLOOK, distCLOOK;
	int *orderFCFS, *orderSSTF, *orderSCAN, *orderCSCAN, *orderLOOK, *orderCLOOK;

	orderFCFS = fcfs(testFCFS, head);
	distFCFS = distance(orderFCFS, 0);
	for (int i = 0; i < 1000; i++)
	{
		//printf("%d\n", testFCFS[i]);
	}
	//printf("\n\n\n");
	orderSSTF = sstf(testSSTF, head);
	distSSTF = distance(orderSSTF, 0);
	for (int i = 0; i < 1002; i++)
	{
		//printf("%d\n", testSSTF[i]);
	}
	//printf("\n\n\n");
	orderSCAN = scan(testSCAN, head);
	distSCAN = distance(orderSCAN, 1);
	for (int i = 0; i < 1002; i++)
	{
		//printf("%d\n", testSCAN[i]);
	}
	//printf("\n\n\n");
	orderCSCAN = cscan(testCSCAN, head);
	distCSCAN = distance(orderCSCAN, 2);
	for (int i = 0; i < 1002; i++)
	{
		//printf("%d\n", testCSCAN[i]);
	}
	//printf("\n\n\n");
	orderLOOK = look(testLOOK, head);
	distLOOK = distance(orderLOOK, 0);
	for (int i = 0; i < 9; i++)
	{
		//printf("%d\n", *(orderLOOK+i));
	}
	//printf("\n\n\n");
	orderCLOOK = clook(testCLOOK, head);
	distCLOOK = distance(orderCLOOK, 0);
	for (int i = 0; i < 9; i++)
	{
		//printf("%d\n", *(orderCLOOK+i));
	}
	//printf("\n\n\n");
	printf("\n\nFCFS dist: %d\n", distFCFS);
	printf("SSTF dist: %d\n", distSSTF);
	printf("SCAN dist: %d\n", distSCAN);
	printf("CSCAN dist: %d\n", distCSCAN);
	printf("LOOK dist: %d\n", distLOOK);
	printf("CLOOK dist: %d\n", distCLOOK);
	return 0;
}


/*
int temp[] = {45, 21, 67, 90, 4, 89, 52, 61, 87, 25};

lenght 10 / 11
*/