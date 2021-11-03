#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int get(int x, int n) {
	unsigned short temp = x;
	temp = temp >> n;
	if((temp&1) == 0) {
		return 0;
	} else {
		return 1;
	}
}

int set(int x, int n, int v) {
	int hold = get(x, n);

	if((v ^ hold) == 0) {
		return (x | 0);
	} else {
	        return (x ^ (int)(pow(2, n)));
	}
}
int one(int x, int num) {
	int s = 0; //for the sum of x + num
	int c = 0; //for the carry on of x&num
	if(num == 0) { //adding to nothing
		return x;
	} else {
		s = x^num; //will take the xor of x and num, allowing us in the future to recurse back and create the number we want
		c = (x&num)<<1; //shifting will create an even number to use on s as the xor
		return one(s, c);
	}
}

int main(int argc, char* argv[])
{
	int prev = -1;
	int curr;
	char* temp = (char*)malloc(sizeof(char)*10);

	int i;
	for(i = 1; i < argc; i++) { //find this in bitwise?
		if(argv[i] != NULL) {
			int j;
			for(j = 0; argv[i][j] != '\0'; j++) {
					temp[j] = argv[i][j];
			}
		}
	}

	int num = atoi(temp);
	unsigned short x = num;

	int pairs = 0;
	int count = 0;


	for(i = 0; i < 16; i = one(i, 1)) { //should not exceed 16 bits, find this in bitwise
		curr = get(x, i);

		if((prev ^ curr) == 0 && prev != 0 && curr != 0) {
			pairs = one(pairs, 1); //find the bitwise equivalent of this line
			count = one(count, 1); //if there is a pair that means curr is 1
			prev = -1;  //reset so next one can be set properly
		} else {
			if((curr ^ 1)== 0){  //find the bitwise equivalent of this line
				count = one(count, 1); //find bitwise equivalent of this line
				prev = curr;
			} else {
				prev = curr;
			}
		}
	}

	if(count%2 == 0) { //even, see if there is a bitwise equivalent to this line
		printf("Even-Parity\t%d\n", pairs);
	} else {
		printf("Odd-Parity\t%d\n", pairs);
	}

	free(temp);
	return 0;
}
