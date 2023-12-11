#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXSIZE 60

void search(char line[], char word[], char** firstPtr, char** lastPtr, int digit, int* first, int* last);

int main() {
	FILE* input;
	errno_t err;
	char nums[10] = "123456789";
	char line[MAXSIZE] = "";
	char *digitPtr1 = NULL, *digitPtr2 = NULL, *tempDigitPtr = NULL;
	int sum = 0;
	int digit1 = 0, digit2 = 0;

	err = fopen_s(&input, "input.txt", "r"); //attempt to open input file
	if (err != 0) {
		puts("Unable to open file.");
		exit(1);
	}

	while(fscanf_s(input, "%s", line, MAXSIZE) != EOF) { //loop until all lines have been read from input file
		digitPtr1 = strpbrk(line, nums); //search for occurrences of digits in string
		digit1 = *digitPtr1 - 48; //char value of 49 corresponds to 1, 50 corresponds to 2, etc
		digit2 = digit1; //if we don't find another digit, the first digit is also the last digit
		tempDigitPtr = digitPtr1; //don't mess with original pointer, so we can compare with it later
		digitPtr2 = digitPtr1; //if we don't find another digit, our pointer to the last digit is also the pointer to the first digit
		while (tempDigitPtr != NULL) {
			tempDigitPtr = strpbrk(tempDigitPtr + 1, nums); //search for later occurrences of digits, starting from the next character after the first digit found
			if (tempDigitPtr != NULL) {
				digit2 = *tempDigitPtr - 48; //if we found another digit, that's our new 'last' digit
				digitPtr2 = tempDigitPtr; //save pointer for later
			}
		}
		//printf("Before searches, string %s was determined to have first digit %d and last digit %d\n", line, digit1, digit2);
		search(line, "one", &digitPtr1, &digitPtr2, 1, &digit1, &digit2); //search string for "one" and update pointers and digits accordingly
		search(line, "two", &digitPtr1, &digitPtr2, 2, &digit1, &digit2); //search string for "two" and etc
		search(line, "three", &digitPtr1, &digitPtr2, 3, &digit1, &digit2); //etc
		search(line, "four", &digitPtr1, &digitPtr2, 4, &digit1, &digit2);
		search(line, "five", &digitPtr1, &digitPtr2, 5, &digit1, &digit2);
		search(line, "six", &digitPtr1, &digitPtr2, 6, &digit1, &digit2);
		search(line, "seven", &digitPtr1, &digitPtr2, 7, &digit1, &digit2);
		search(line, "eight", &digitPtr1, &digitPtr2, 8, &digit1, &digit2);
		search(line, "nine", &digitPtr1, &digitPtr2, 9, &digit1, &digit2);
		//printf("After searches, string %s was determined to have first digit %d and last digit %d\n", line, digit1, digit2);
		sum += (digit1 * 10) + digit2;
	}

	printf("Final sum is %d", sum);
	fclose(input);
}

void search(char line[], char word[], char** firstPtr, char** lastPtr, int digit, int* first, int* last) {
	char* wordPtr = strstr(line, word);
	if (wordPtr == NULL) return; //no instance of word found, no changes needed
	if (wordPtr < *firstPtr) { //if word occurs earlier than first numerical digit found,
		*firstPtr = wordPtr; //update pointer to first 'digit' found in string
		*first = digit; //update first digit
	}
	char* tempPtr = wordPtr;
	while (wordPtr != NULL) {
		tempPtr = wordPtr;
		wordPtr = strstr(wordPtr + 1, word);
	}
	if (tempPtr > *lastPtr) { //if word occurs later than last numerical digit found, 
		*lastPtr = tempPtr; //update pointer to last 'digit' found in string
		*last = digit; //update last digit
	}
}

/* Remarks:
* Not elegant. Not clever. But it worked! Amateur that I am, I don't know anything other than basic tools like "search a string for a character"
* or "search a string for another string," so that's what I did. I remember thinking that it would be nice if there was a way to strpbrk from the
* end of a string going backwards, but since that didn't seem to be possible (could be wrong!) I just repeatedly searched until we hit the last digit.
* Part 2 led to the even uglier search() function being created, and the hamfisted technique of "just search for all nine possible strings." The
* joke's on the clever people, though, because this worked immediately. My head is full of meat, so it has no room for fear of "nineight"s and "twone"s.
*/
