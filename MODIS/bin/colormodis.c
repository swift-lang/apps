#include <stdio.h>
#include <stdlib.h>

typedef struct rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} rgb;

rgb *assignValue(char r, char g, char b)
{
	rgb *new = malloc(sizeof(rgb));
	new->r = r;
	new->g = g;
	new->b = b;
	return new;
}

// TODO: read the buffer into integer arrays and convert them to corresponding integer arrays: do a lookup
int main(int argc, char *argv[])
{
	unsigned long size = 2400 * 2400;
	//char *buffer = malloc(size * sizeof(char));
	FILE *inputFile = fopen(argv[1], "rb");
	FILE *outFile = fopen(argv[2], "w");
	//fread(buffer, size, 1, inputFile);
	//fclose(inputFile);
	unsigned char modis;
	
	rgb *rgbNew = malloc(sizeof(rgb));

	for (int i = 0; i < size; i++) {
		fscanf(inputFile, "%c", &modis);
		switch (modis) {
			case 0:
			rgbNew = assignValue(0x2b, 0x30, 0x41);
			break;
			case 1:
			rgbNew = assignValue(0x00, 0x6a, 0x0f);
			break;
			case 2:
			rgbNew = assignValue(0x00, 0x7c, 0x25);
			break;
			case 3:
			rgbNew = assignValue(0x00, 0xa2, 0x5b);
			break;
			case 4:
			rgbNew = assignValue(0x00, 0xa1, 0x25);
			break;
			case 5:
			rgbNew = assignValue(0x06, 0x92, 0x28);
			break;
			case 6:
			rgbNew = assignValue(0x9e, 0x96, 0x68);
			break;
			case 7:
			rgbNew = assignValue(0xc1, 0xc4, 0x8f);
			break;
			case 8:
			rgbNew = assignValue(0x85, 0xaa, 0x5b);
			break;
			case 9:
			rgbNew = assignValue(0xb1, 0xb7, 0x41);
			break;
			case 10:
			rgbNew = assignValue(0xa4, 0xd0, 0x7e);
			break;
			case 11:
			rgbNew = assignValue(0x73, 0xab, 0xae);
			break;
			case 12:
			rgbNew = assignValue(0xcc, 0xd2, 0x53);
			break;
			case 13:
			rgbNew = assignValue(0xd9, 0x00, 0x00);
			break;
			case 14:
			rgbNew = assignValue(0x9d, 0xe3, 0x6e);
			break;
			case 15:
			rgbNew = assignValue(0xb6, 0xb5, 0xc2);
			break;
			case 16:
			rgbNew = assignValue(0x94, 0x94, 0x94);
			break;
			default:
			rgbNew = NULL;
		}

		if (rgbNew != NULL) {
			fprintf(outFile, "%c%c%c", rgbNew->r, rgbNew->g, rgbNew->b);
		} else {
			fprintf(outFile, "%c%c%c", modis, modis, modis);
		}
	}
	fclose(outFile);
	return 0;
}



