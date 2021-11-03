#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

int comp(int x, int n) {
  return (x ^ (int)(pow(2, n)));
}

int main(int argc, char* argv[])
{
	FILE* f = fopen(argv[1], "r");

	if(f == NULL) {
		printf("error\n");
		return 0;
	}

	int temp;
	fscanf(f, "%d", &temp);
	unsigned short x = temp;

	char* type = (char*)malloc(sizeof(char)*1000); //type String
	int n;
	int v;

	while(fscanf(f, "%s", type) == 1){
		if(strcmp(type, "get") == 0) {
			fscanf(f, "%d", &n);
			printf("%u\n", get(x, n));
			fscanf(f, "%d", &v); //for the extra 0 we don't need
		} else if(strcmp(type, "set") == 0) {
			fscanf(f, "%d", &n);
			fscanf(f, "%d", &v);
			x = set(x, n, v);
			printf("%u\n", x);
		} else if(strcmp(type, "comp") == 0) {
			fscanf(f, "%d", &n);
			x = comp(x, n);
			printf("%u\n", x);
			fscanf(f, "%d", &v); //for extra 0 we don't need
		}
	}

	free(type);
	return 0;


}
