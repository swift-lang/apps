#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct land {
	unsigned long freq;
	int index;
} land;

int main(int argc, char *argv[])
{
	FILE *fp = fopen(argv[1], "r");
	land *a = malloc(sizeof(land) * 256);
	for (int i = 0; i < 256; i++) {
		a[i].freq = 0;
		a[i].index = i;
	}
	
	int c;
	while ((c = fgetc(fp)) != EOF) {
		a[c].freq++;
	}

	land *temp = malloc(sizeof(land));
	for (int i = 0; i < 256; i++) {
		for (int j = i + 1; j < 256; j++) {
			if (a[i].freq > a[j].freq) {
				*temp = a[i];
				a[i] = a[j];
				a[j] = *temp;
			}
		}
	}

	for (int i = 0; i < 256; i++) {
		if (a[i].freq != 0) {
			printf("%lu %d %02X\n", a[i].freq, a[i].index, a[i].index);
		}
	}

	return 0;
}