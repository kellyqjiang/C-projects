#include <stdio.h>
#include <stdlib.h>

int get(int x, int n) {
	unsigned short temp = x;
	temp = temp >> n;
	if((temp&1) == 0) {
		return 0;
	} else {
		return 1;
	}
}

int main(int argc, char* argv[])
{
	int LSB;
	int MSB;
	char* temp = (char*)malloc(sizeof(char)*10);

	int i;
	for(i = 1; i < argc; i++) {
		if(argv[i] != NULL) {
			int j;
			for(j = 0; argv[i][j] != '\0'; j++) {
				temp[j] = argv[i][j];
			}
		}
	}

	int num = atoi(temp);
	unsigned short x = num;

	for(i = 0; i < 8; i++) {
		LSB = get(x, i);
		MSB = get(x, 16-i-1);

		if((LSB ^ MSB) == 1) {
			printf("Not-Palindrome\n");
			free(temp);
			return 0;
		}
	}

	printf("Is-Palindrome\n");
	free(temp);
	return 0;
}
