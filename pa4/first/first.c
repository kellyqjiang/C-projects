#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
	int data;
	char* name;
	//should have no collision
}Node;

Node* vars[2001];

int hashCode(int val) {
	val = val % 2001;
	if(val < 0)
		val += 2001;
	return val;
}

void insert(int key, int data, char* s) {
	Node* in = (Node*)malloc(sizeof(Node));
	in->data = data;
	in->name = s;

	//should not encounter a collision, so just put into hash table
	vars[key] = in;
}

void convert(int num, int size, char** inArray) {
	int i = 0;
	int* arr = (int*)malloc(sizeof(int)*size);
	for(i = 0; i < size; i++) {
		int va = (int)(inArray[i]);
		int v = hashCode(va);
		vars[v]->data = 0;
		arr[i] = 0;
	}//sets all data to 0
	i = 0;
	while(num > 0) {
		arr[i] = num%2;
		num = num/2;
		i+=1;
	}
	for(i = 0; i < size; i++) {
		int va = (int)(inArray[i]);
		int v = hashCode(va);
		vars[v]->data = arr[size-i-1];
	}

}

int main(int argc, char* argv[])
{
	FILE* f = fopen(argv[1], "r");

	if(f == NULL) {
		printf("File not found\n");
		return 0;
	}

	char* throwAway = (char*)malloc(sizeof(char*)*10);
	fscanf(f, "%s", throwAway);

	int col;
	fscanf(f, "%d", &col);
	int c = col;
	char** array = malloc(c*sizeof(char*)); //input variables

	int row = (int)pow((double)2, (double)col);

	int i;
	for(i = 0; i < col; i++) { //this is the default, makes every variable 0 automatically
		char* varName = (char*)malloc(sizeof(char)*10);
		fscanf(f, "%s", varName);
		array[i] = varName;
		int va = (int)varName;
		int n =	hashCode(va);
		insert(n, 0, varName);
	}

	fscanf(f, "%s", throwAway);

	free(throwAway);

	int t;
	fscanf(f, "%d", &t);
	col = col+t;

	char** array2 = (char**)malloc(sizeof(char*)*t); //output variables

	for(i = 0; i < t; i++) { //this is the default, makes every variable 0 automatically
  	char* varName = (char*)malloc(sizeof(char*)*10);
    fscanf(f, "%s", varName);
    array2[i] = varName;
		int va = (int)varName;
    int n = hashCode(va);
    insert(n, 0, varName);
  }

	char** ops = (char**)malloc(sizeof(char*)*20);

	char** stores = (char**)malloc(sizeof(char*)*20);
	char** names = (char**)malloc(sizeof(char*)*200);

	int** out = (int**)malloc(sizeof(int*)*row);

	int count = 0;
	int a = 0; //counter to add ops
	int h = 0; //counter to add names
	int m = 0; //counter to add stores
	char* type = (char*)malloc(sizeof(char*)*5);
	int j = 0; //counter for ops
	int e = 0; //counter for names
	int d = 0; //counter for stores

	//STILL READING FILE
	while(fscanf(f, "%s", type) == 1) { //row 0, no matter what
		out[0] = (int*)malloc(sizeof(int)*col);
		char* name = (char*)malloc(sizeof(char)*10);
		char* name2 = (char*)malloc(sizeof(char)*10);
		if(strcmp(type, "NOT") == 0) {
			ops[a] = "NOT";
			a+=1;
			fscanf(f, "%s", name);
			names[h] = name;
			h+=1;
			int v1 = 0;
			int k;
			for(k = 0; k < c; k++) {
				if(strcmp(name, array[k]) == 0) {
					int u = hashCode((int)array[k]);
					v1 = vars[u]->data;
					break;
				}
			}

			for(k = 0; k < m; k++) { //for temps
				if(strcmp(name, stores[k]) == 0) {
					int u = hashCode((int)stores[k]);
					v1 = vars[u]->data;
					break;
				}
			}

			char* store = (char*)malloc(sizeof(char)*10);
			fscanf(f, "%s", store);

			bool last = false;
			for(k = 0; k < t; k++) {
				if(strcmp(store, array2[k]) == 0) {
					stores[m] = store;
					m+=1;
					int u = hashCode((int)array2[k]);
					if(v1 == 1) {
						vars[u]->data = 0;
					} else if(v1 == 0) {
							vars[u]->data = 1;
					}
					last = true;
					break;
				}
			}
			if(!last) {
				char** temp = &store;
				stores[m] = *temp;
				m+=1;
				if(v1 == 1) {
					int va = (int)(store);
					int n = hashCode(va);
					insert (n, 0, store);
				} else if(v1 == 0) {
						int va = (int)(store);
						int n = hashCode(va);
						insert (n, 1, store);
				}
			}
		} else {
				fscanf(f, "%s", name);
				int v1 = 0;
				int k;
				for(k = 0; k < c; k++) {
					if(strcmp(name, array[k]) == 0) {
						names[h] = array[k];
						h+=1;
						int u = hashCode((int)array[k]);
						v1 = vars[u]->data;
						break;
					}
				}

				for(k = 0; k < m; k++) { //for temps
					if(strcmp(name, stores[k]) == 0) {
						names[h] = stores[k];
						h+=1;
						int u = hashCode((int)stores[k]);
						v1 = vars[u]->data;
						break;
					}
				}

				fscanf(f, "%s", name2);
				int v2 = 0;
				for(k = 0; k < c; k++) {
					if(strcmp(name2, array[k]) == 0) {
						names[h] = array[k];
						h+=1;
						int u = hashCode((int)array[k]);
						v2 = vars[u]->data;
						break;
					}
				}

				for(k = 0; k < m; k++) { //for temps
					if(strcmp(name2, stores[k]) == 0) {
						names[h] = stores[k];
						h+=1;
						int u = hashCode((int)stores[k]);
						v2 = vars[u]->data;
						break;
					}
				}

				char* store = (char*)malloc(sizeof(char)*10);
				fscanf(f, "%s", store);

				if(strcmp(type, "AND") == 0) {
					ops[a] = "AND";
					a+=1;
					int r = v1 & v2;
					bool last = false;
					for(k = 0; k < t; k++) {
						if(strcmp(store, array2[k]) == 0) {
							stores[m] = array2[k];
							m+=1;
							int u = hashCode((int)array2[k]);
							vars[u]->data = r;
							last = true;
						}
					}
					if(!last) {
						stores[m] = store;
						m+=1;
						int va = (int)(store);
						int n = hashCode(va);
						insert (n, r, store);
					}
				} else if(strcmp(type, "OR") == 0) {
						ops[a] = "OR";
						a+=1;
						int r = v1 | v2;
						bool last = false;
						for(k = 0; k < t; k++) {
							if(strcmp(store, array2[k]) == 0) {
								stores[m] = array2[k];
								m+=1;
								int u = hashCode((int)array2[k]);
								vars[u]->data = r;
								last = true;
							}
						}
						if(!last) {
							stores[m] = store;
							m+=1;
							int va = (int)(store);
							int n = hashCode(va);
							insert (n, r, store);
						}
				} else if(strcmp(type, "NAND") == 0) {
						ops[a] = "NAND";
						a+=1;
						int r = v1 & v2;
						bool last = false;
						for(k = 0; k < t; k++) {
							if(strcmp(store, array2[k]) == 0) {
								stores[m] = array2[k];
								m+=1;
								int u = hashCode((int)array2[k]);
								vars[u]->data = r;
								if(r == 1)
				      		vars[u]->data = 0; //just the opposite, so we know what it is
				        else if(r == 0)
				        	vars[u]->data = 1;
								last = true;
							}
						}
						if(!last) {
							stores[m] = store;
							m+=1;
							int va = (int)(store);
							int n = hashCode(va);
							if(r == 1)
								insert (n, 0, store); //just the opposite, so we know what it is
							else if (r == 0)
								insert(n, 1, store);
						}
				} else if(strcmp(type, "NOR") == 0) {
						ops[a] = "NOR";
						a+=1;
						int r = v1 | v2;
						bool last = false;
						for(k = 0; k < t; k++) {
							if(strcmp(store, array2[k]) == 0) {
								stores[m] = array2[k];
								m+=1;
								int u = hashCode((int)array2[k]);
								vars[u]->data = r;
								if(r == 1)
				      		vars[u]->data = 0; //just the opposite, so we know what it is
				        else if(r == 0)
				        	vars[u]->data = 1;
								last = true;
							}
						}
						if(!last) {
							char** temp = &store;
							stores[m] = *temp;
							m+=1;
							int va = (int)(store);
							int n = hashCode(va);
							if(r == 1)
								insert (n, 0, store); //just the opposite, so we know what it is
							else if(r == 0)
								insert(n, 1, store);
						}
				} else if(strcmp(type, "XOR") == 0) {
						ops[a] = "XOR";
						a+=1;
						int r = v1 ^ v2;
						bool last = false;
						for(k = 0; k < t; k++) {
							if(strcmp(store, array2[k]) == 0) {
								stores[m] = array2[k];
								m+=1;
								int u = hashCode((int)array2[k]);
								vars[u]->data = r;
								last = true;
							}
						}
						if(!last) {
							char** temp = &store;
							stores[m] = *temp;
							m+=1;
							int va = (int)(store);
							int n = hashCode(va);
							insert (n, r, store);
						}
				}
		}
	}

	j = 0;
	for(i = 0; i < col; i++) {
		if(i >= c) {
			int va = (int)(array2[j]);
			int v = hashCode(va);
			out[0][i] = vars[v]->data;
			j+=1;
		}
		else{
			int va = (int)(array[i]);
			int v = hashCode(va);
			out[0][i] = vars[v]->data; //puts variable name at array[i]'s value into first row
		}
	}

	/*for(int k = 0; k < h; k++) {
		printf("NAMES %s\n", names[k]);
	}
	for(int k = 0; k < m; k++) {
		printf("STORES %s\n", stores[k]);
	}*/

	//AFTER FILE, EVERYTHING STORED IN SOMETHING ELSE
	for(i = 1; i < row; i++) {
		count += 1;
		convert(count, c, array);
		out[i] = (int*)malloc(sizeof(int)*col);
		int j = 0;
		e = 0;
		for(j = 0; j < a; j++) {
			if(strcmp(ops[j], "NOT") == 0) {
				int v1 = 0;
				int k;
				for(k = 0; k < c; k++) {
					if(strcmp(names[e], array[k]) == 0) {
						int u = hashCode((int)array[k]);
						v1 = vars[u]->data;
						break;
					}
				}

				for(k = 0; k < m; k++) { //for temps
					if(strcmp(names[e], stores[k]) == 0) {
						int u = hashCode((int)stores[k]);
						v1 = vars[u]->data;
						break;
					}
				}

				e+=1;

				bool last = false;
				for(k = 0; k < t; k++) {
					if(strcmp(stores[d], array2[k]) == 0) {
						d+=1;
						int u = hashCode((int)array2[k]);
						if(v1 == 1) {
							vars[u]->data = 0;
						} else if(v1 == 0) {
								vars[u]->data = 1;
						}
						last = true;
						if(d >= m) {
  						d = 0;
						}
						break;
					}
				}
				if(!last) {
					if(v1 == 1) {
						int va = (int)(stores[d]);
						d+=1;
						int n = hashCode(va);
						vars[n]->data = 0;
					} else if(v1 == 0) {
							int va = (int)(stores[d]);
							d+=1;
							int n = hashCode(va);
							vars[n]->data = 1;
					}
				}
			} else {
					int v1 = 0;
					int k;
					for(k = 0; k < c; k++) {
						if(strcmp(names[e], array[k]) == 0) {
							int va = (int)array[k];
							int u = hashCode(va);
							v1 = vars[u]->data;
							break;
						}
					}

					for(k = 0; k < m; k++) { //for temps
						if(strcmp(names[e], stores[k]) == 0) {
							int u = hashCode((int)stores[k]);
							v1 = vars[u]->data;
							break;
						}
					}

					e+=1;

					int v2 = 0;
					for(k = 0; k < c; k++) {
						if(strcmp(names[e], array[k]) == 0) {
							int u = hashCode((int)array[k]);
							v2 = vars[u]->data;
							break;
						}
					}

					for(k = 0; k < m; k++) { //for temps
						if(strcmp(names[e], stores[k]) == 0) {
							int u = hashCode((int)stores[k]);
							v2 = vars[u]->data;
							break;
						}
					}
					e+=1;

					if(strcmp(ops[j],"AND") == 0) {
							int r = v1 & v2;
							bool last = false;
							for(k = 0; k < t; k++) {
								if(strcmp(stores[d], array2[k]) == 0) {
									d+=1;
									int u = hashCode((int)array2[k]);
									vars[u]->data = r;
									last = true;
									if(d >= m) {
  									d = 0;
									}
									break;
								}
							}
							if(!last) {
								int va = (int)(stores[d]);
								d+=1;
								int n = hashCode(va);
								vars[n]->data = r;
							}
					} else if(strcmp(ops[j], "OR") == 0) {
							int r = v1 | v2;
							bool last = false;
							for(k = 0; k < t; k++) {
								if(strcmp(stores[d], array2[k]) == 0) {
									d+=1;
									int u = hashCode((int)array2[k]);
									vars[u]->data = r;
									last = true;
									if(d >= m) {
  									d = 0;
									}
									break;
								}
							}
							if(!last) {
								int va = (int)(stores[d]);
								d+=1;
								int n = hashCode(va);
								vars[n]->data = r;
							}
					} else if(strcmp(ops[j],"NAND") == 0) {
							int r = v1 & v2;
							bool last = false;
							for(k = 0; k < t; k++) {
								if(strcmp(stores[d], array2[k]) == 0) {
									d+=1;
									int u = hashCode((int)array2[k]);
									vars[u]->data = r;
									if(r == 1)
					      		vars[u]->data = 0; //just the opposite, so we know what it is
					        else if(r == 0)
					        	vars[u]->data = 1;
									last = true;
									if(d >= m) {
	  								d = 0;
									}
									break;
								}
							}
							if(!last) {
								int va = (int)(stores[d]);
								d+=1;
								int n = hashCode(va);
								if(r == 1)
					      	vars[n]->data = 0; //just the opposite, so we know what it is
								else if (r == 0)
									vars[n]->data = 1;
							}
					} else if(strcmp(ops[j], "NOR") == 0) {
							int r = v1 | v2;
							bool last = false;
							for(k = 0; k < t; k++) {
								if(strcmp(stores[d], array2[k]) == 0) {
									d+=1;
									int u = hashCode((int)array2[k]);
									vars[u]->data = r;
									if(r == 1)
					      		vars[u]->data = 0; //just the opposite, so we know what it is
					        else if(r == 0)
					        	vars[u]->data = 1;
									last = true;
									if(d >= m) {
  									d = 0;
									}
									break;
								}
							}
							if(!last) {
								int va = (int)(stores[d]);
								d+=1;
								int n = hashCode(va);
				        if(r == 1)
				      		vars[n]->data = 0; //just the opposite, so we know what it is
				        else if(r == 0)
				        	vars[n]->data = 1;
							}
					} else if(strcmp(ops[j], "XOR") == 0) {
							int r = v1 ^ v2;
							bool last = false;
							for(k = 0; k < t; k++) {
								if(strcmp(stores[d], array2[k]) == 0) {
									d+=1;
									int u = hashCode((int)array2[k]);
									vars[u]->data = r;
									last = true;
									if(d >= m) {
  									d = 0;
									}
									break;
								}
							}
							if(!last) {
								int va = (int)(stores[d]);
								d+=1;
								int n = hashCode(va);
				        vars[n]->data = r;
							}
					}
				}
			}
			int k = 0;
			for(j = 0; j < col; j++) {
				if(j >= c) {
					int va = (int)(array2[k]);
					int v = hashCode(va);
					out[i][j] = vars[v]->data;
					k+=1;
				}
				else{
					int va = (int)(array[j]);
					int v = hashCode(va);
					out[i][j] = vars[v]->data; //puts variable name at array[i]'s value into first row
				}
			}
	}


	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			printf("%d ", out[i][j]);
		}
		printf("\n");
	}

	free(array);
	free(array2);
	free(ops);
	free(out);
}
