#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void draw_rectangle(FILE *originFile, int xres, int yres, int xmin,  int ymin, int xmax, int ymax, FILE *outputFile) 
{
	unsigned char red, green, blue;
	int x = 0, y = 0;

	while (fscanf(originFile, "%c%c%c", &red, &green, &blue) != EOF) {
		if (x == xmin || x == xmin + 1 || x == xmax || x == xmax - 1) {
			if (y <= ymax && y >= ymin) {
				red = 255;
				green = 0;
				blue = 0;
			}
		}

		if (y == ymin || y == ymin - 1 || y == ymax || y == ymax - 1) {
			if (x <= xmax && x >= xmin) {
				red = 255;
				green = 0;
				blue = 0;
			}
		}

		fprintf(outputFile, "%c%c%c", red, green, blue);

		if (x == xres - 1) {
			x = 0;
			y++;
		} else {
			x++;
		}
	} 
}

int main(int argc, char *argv[])
{
	int xres, yres, i = 0;
	FILE *topSelected = fopen(argv[1], "r");
	char buf[256];
	unsigned long freq;

	FILE *world;
	FILE *outmap;
	while (fscanf(topSelected, "%s %lu", buf, &freq) != EOF) {
		char sh[5], sv[5], hv[20];
		memcpy(sh, &buf[9], 2);
		sh[2] = '\0';
		int h = atoi(sh);
		memcpy(sv, &buf[12], 2);
		sv[2] = '\0';
		int v = atoi(sv);
		memcpy(hv, &buf[8], 6);
		hv[6] = '\0';

		xres = 721;
		yres = 361;
		if (i == 0) {
			world = fopen("./bin/world.rgb", "r");
			i++;
		} else {
			world = fopen("outmap.step", "r");
		}
		outmap = fopen("outmap.tmp", "w");

		draw_rectangle(world, xres, yres, h * 20, v * 20, h * 20 + 20, v * 20 + 20, outmap);

		remove("outmap.step");
		rename("outmap.tmp", "outmap.step");
		fclose(world);
	}

	char cmd[128];
	system("chmod 777 ./bin/rgb_to_png.py");
	sprintf(cmd, "./bin/rgb_to_png.py outmap.step 721 361 %s", argv[2]);
	system(cmd);

	return 0;
}








