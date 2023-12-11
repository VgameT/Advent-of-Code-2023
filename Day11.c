#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define LINESIZE 142 //size of a text line, including newline and null characters
#define FIELDSIZE 140 //size of our input field, 140 x 140

struct galaxy {
	int x;
	int y;
};

typedef struct galaxy Galaxy;

int main() {
	FILE* input;
	errno_t err;
	int horiz[FIELDSIZE] = { 0 }; //array for tracking which x coords have a galaxy
	int expX[15] = { 0 }; //array to store coordinates that will expand
	int expY[15] = { 0 }; //my input has 12 expansions max, but others may have more
	int xExpansions = 0, yExpansions = 0; //used to track how many expansions we have total, so we don't compare beyond our actual data later
	int found = 0; //used to track how many galaxies we've found
	long long int sum = 0;
	char line[LINESIZE] = "";
	char* ptr = NULL;
	Galaxy universe[500]; //my input has 433 galaxies, but others may have more

	err = fopen_s(&input, "input.txt", "r");
	if (err != 0) exit(1);

	for (int i = 0; i < FIELDSIZE; ++i) {
		fgets(line, LINESIZE, input);
		ptr = strchr(line, '#');
		if (ptr == NULL) { //no #s in a line means expand this line vertically
			expY[yExpansions] = i;
			yExpansions++;
		}
		else {
			while (ptr != NULL) {
				horiz[ptr - line] = 1; //mark this x coord as having a #
				ptr = strchr(ptr + 1, '#'); //find next # in line
			}
		}
	}

	for (int i = 0; i < FIELDSIZE; ++i) { //fill array with x coords that must expand
		if (horiz[i] == 0) { //no #s in a column means we expand
			expX[xExpansions] = i;
			xExpansions++;
		}
	}

	rewind(input);
	for (int i = 0; i < FIELDSIZE; ++i) {
		fgets(line, LINESIZE, input);
		ptr = strchr(line, '#'); //find a galaxy
		while (ptr != NULL) {
			universe[found].x = ptr - line; //pointer in string - string = index in the char array the pointer is pointing to
			universe[found].y = i;
			int offset = 0;
			while ((offset < xExpansions) && (universe[found].x > expX[offset])) offset++; //for each expansion we're located past, offset our coords
			universe[found].x += offset * 999999;
			offset = 0;
			while ((offset < yExpansions) && (universe[found].y > expY[offset])) offset++;
			universe[found].y += offset * 999999;
			found++;
			ptr = strchr(ptr + 1, '#');
		}
	}
	for (int i = 0; i < found; ++i) { //for each galaxy
		//find path length to each other galaxy with a higher index (because we only want to measure each path once)
		for (int j = i + 1; j < found; ++j) sum += abs(universe[i].x - universe[j].x) + abs(universe[i].y - universe[j].y);
		//path length is just difference in vertical coords plus difference in horizontal coords
	}

	printf("sum is %lli", sum);
}

/* Remarks:
Straightforward day. I twigged to the path length immediately, and also discarded the idea of expanding the input data lines immediately.
I pretty much just settled on the method (scan through the input to figure out expansions, then scan again to make galaxies, and increment
their coordinates based on the expansion data) and then coded it, and it worked. My only issue was multiplying offset by one million initially,
which was obviously an easy fix once I thought about it more.*/
