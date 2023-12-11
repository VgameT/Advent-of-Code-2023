#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define SIZE 160
#define REDMAX 12
#define BLUEMAX 14
#define GREENMAX 13

void reset(int* red, int* blue, int* green);
char* tally(char* ptr, int* red, int* blue, int* green, int* digit1, int* digit2);

int main() {
	int game = 1, red = 0, blue = 0, green = 0, digit1 = 0, digit2 = 0;
	int blueMax = 0, redMax = 0, greenMax = 0;
	int impossible = 0, done = 0, total = 0, power = 0;
	char line[SIZE] = "";
	char* ptr = NULL;
	FILE* input;
	errno_t err;

	err = fopen_s(&input, "input.txt", "r");
	if (err != 0) {
		puts("Unable to open file.");
		exit(1);
	}

	while (!feof(input)) {
		fgets(line, SIZE, input);
		//printf("%s\n", line);
		ptr = strchr(line, ':'); //seek to the colon
		ptr += 2; //seek to first digit
		while (done == 0) {
			ptr = tally(ptr, &red, &blue, &green, &digit1, &digit2);
			//printf("After first tally, red = %d, blue = %d, green = %d\n", red, blue, green);
			if (*ptr == ',') {
				ptr += 2; //point to next digit after comma
				ptr = tally(ptr, &red, &blue, &green, &digit1, &digit2);
				//printf("After second tally, red = %d, blue = %d, green = %d\n", red, blue, green);
			}
			if (*ptr == ',') {
				ptr += 2; //point to next digit after comma
				ptr = tally(ptr, &red, &blue, &green, &digit1, &digit2);
				//printf("After third tally, red = %d, blue = %d, green = %d\n", red, blue, green);
			}
			if ((blue > BLUEMAX) || (red > REDMAX) || (green > GREENMAX)) {
				//printf("This game was deemed impossible.\n");
				impossible = 1;
			}
			if (blue > blueMax) blueMax = blue;
			if (green > greenMax) greenMax = green;
			if (red > redMax) redMax = red;
			if (*ptr == ';') {
				//printf("Semicolon encountered, resetting counts.\n");
				reset(&red, &blue, &green);
				ptr += 2; //point to next digit after semicolon
			}
			else done = 1; //if not pointing to semicolon, we hit the end of the string
		}
		if (impossible == 0) total += game;
		reset(&red, &blue, &green);
		power += redMax * blueMax * greenMax;
		printf("redMax: %d, blueMax: %d, greenMax: %d. Power of set is %d. Running total of powers is %d.\n", redMax, blueMax, greenMax, redMax * blueMax * greenMax, power);
		printf("After game %d, total is %d.\n", game, total);
		game++;
		redMax = 0;
		blueMax = 0;
		greenMax = 0;
		done = 0;
		impossible = 0;
	}
}

void reset(int* red, int* blue, int* green) {
	*red = 0;
	*blue = 0;
	*green = 0;
}

char* tally(char* ptr, int* red, int* blue, int* green, int* digit1, int* digit2) {
	if (isdigit(*(ptr + 1))) { //if two-digit number, store accordingly
		*digit1 = *ptr - 48;
		ptr++; //move to next digit
		*digit2 = *ptr - 48;
	}
	else *digit2 = *ptr - 48; //else store single digit in the ones place

	ptr += 2; //move pointer to first character of color
	if (*ptr == 'b') {
		*blue = (*digit1 * 10) + *digit2;
		ptr += 4; //move pointer to first character past color
	}
	else if (*ptr == 'r') {
		*red = (*digit1 * 10) + *digit2;
		ptr += 3;
	}
	else {
		*green = (*digit1 * 10) + *digit2;
		ptr += 5;
	}
	*digit1 = 0; //reset digits for next tally
	*digit2 = 0;
	return ptr;
}

/* Remarks:
This program does a lot of unnecessary and/or roundabout things. It does work! However, there were a few things I learned from
looking at other solutions after I finished my own. One such thing was: there's no need to differentiate between different games,
you only care about the highest value found for each color cube. In other words, the input is just Game X: X color* repeated some
number of times, where * is a comma, or semicolon, or newline, or null character. There's no need tally games separately. Also, my
method of parsing the input is obviously not great here. Another thing I learned was that scanning for %d will ignore leading spaces,
so I can just point to a space and then grab the number directly without doing weird pointer and character -> integer conversions.
After this day, I resolved to try and be smarter about understanding the problem, and also to try and be smarter about the way I
parsed the input files.
*/
