#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>

typedef struct typeFreq {
	char *filename;
	unsigned long freq;
} typeFreq;

int main(int argc, char *argv[])
{

	FILE *topselected = fopen(argv[1], "a");
	FILE *selectedtiles = fopen(argv[2], "a");

	int t;

	char *usetype = argv[3];
	if (strcmp(usetype, "water") == 0) {
		t = 0;
	} else if (strcmp(usetype, "evergreenneedle") == 0) {
		t = 1;
	} else if (strcmp(usetype, "evergreenlead") == 0) {
		t = 2;
	} else if (strcmp(usetype, "deciduousneedle") == 0) {
		t = 3;
	} else if (strcmp(usetype, "deciduousleaf") == 0) {
		t = 4;
	} else if (strcmp(usetype, "mixedforest") == 0) {
		t = 5;
	} else if (strcmp(usetype, "closedshrub") == 0) {
		t = 6;
	} else if (strcmp(usetype, "openshrub") == 0) {
		t = 7;
	} else if (strcmp(usetype, "woody") == 0) {
		t = 8;
	} else if (strcmp(usetype, "savanna") == 0) {
		t = 9;
	} else if (strcmp(usetype, "grassland") == 0) {
		t = 10;
	} else if (strcmp(usetype, "wetland") == 0) {
		t = 11;
	} else if (strcmp(usetype, "cropland") == 0) {
		t = 12;
	} else if (strcmp(usetype, "urban") == 0) {
		t = 13;
	} else if (strcmp(usetype, "vegetartion") == 0) {
		t = 14;
	} else if (strcmp(usetype, "ice") == 0) {
		t = 15;
	} else if (strcmp(usetype, "barren") == 0) {
		t = 16;
	} else {
		t = 17;
	}

	char **fname = malloc(1000 * sizeof(char *));
	int i = 0;

	fname[0] = malloc(sizeof(char) * 30);
	fname[0] = strtok(argv[5], " ") ;

	while (fname[i] != NULL) {
		i++;
		fname[i] = malloc(sizeof(char) * 30);
		fname[i] = strtok(NULL, " ");
	}

	int j = 0, k = 0;
	unsigned long freq;
	int index, hexIndex;
	typeFreq *s = malloc(sizeof(typeFreq) * 1000);
	while (fname[j] != NULL) {
		FILE *fp = fopen(fname[j], "r");
		while (fscanf(fp, "%lu %d %02x", &freq, &index, &hexIndex) != EOF) {
			if (index == t) {
				s[k].filename = fname[j];
				s[k].freq = freq;
				k++;
			}
		}
		j++;
	}

	typeFreq *temp = malloc(sizeof(typeFreq));
	for (int i = 0; i < atoi(argv[4]); i++) {
		for (int j = i + 1; j < k; j++) {
			if (s[j].freq > s[i].freq) {
				*temp = s[i];
				s[i] = s[j];
				s[j] = *temp;
			}
		}
	}

	for (int i = (atoi(argv[4]) - 1); i >= 0; i--) {
		fprintf(topselected, "%s %lu\n", s[i].filename, s[i].freq);
        char *foo = basename(s[i].filename);
        printf("DEBUG: %s\n", &s[i].filename[8]);
        printf("DEBUG: dirname : %s", dirname(s[i].filename));
        printf("DEBUG: basename : %s", basename(s[i].filename));
        printf("DEBUG: dir(dir) name : %s", dirname(dirname(s[i].filename)));

        fprintf(selectedtiles, "modis-2002/%c%c%c%c%c%c.modis\n", foo[0], foo[1], foo[2], foo[3], foo[4], foo[5]);
	}
	return 0;
}


