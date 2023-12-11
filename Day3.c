#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

int main() {
	FILE* input;
	errno_t err = fopen_s(&input, "input.txt", "r");
	if (err != 0) {
		puts("problem");
		exit(1);
	}
	char* ptr = NULL;
	char* ptr2 = NULL;
	char prevLine[142] = "";
	char currLine[142] = "";
	char nextLine[142] = "";
	int nums[1195] = { 0 };
	int index = 0;
	int pos = 0;
	int digitPos = 0;
	int size = 0;
	int valid = 0;
	int sum = 0;
	int offset = 0;
	int gearSum = 0;
	int found = 0;
	int num1 = 0, num2 = 0, currNum = 0;
	
	//fill array with all numbers in the text file, to look up later
	for (int i = 0; i < 140; ++i) {
		fgets(currLine, 142, input);
		ptr = strtok_s(currLine, ".*@/+$&=-#%\n", &ptr2);
		while (ptr != NULL) {
			nums[index] = atoi(ptr);
			index++;
			ptr = strtok_s(NULL, ".*@/+$&=-#%\n", &ptr2);
		}
	}
	rewind(input);
	index = 0;
	
	fgets(currLine, 142, input);
	fgets(nextLine, 142, input);

	ptr = strpbrk(currLine, "123456789");
	while (ptr != NULL) {
		pos = ptr - currLine;
		if ((nums[index] / 100) > 0) size = 3;
		else if ((nums[index] / 10) > 0) size = 2;
		else size = 1;
		if (currLine[pos - 1] != '.') valid = 1;
		else if (currLine[pos + size] != '.') valid = 1;
		else {
			pos--;
			for (int i = 0; i < size + 2; ++i) {
				if (nextLine[pos + i] != '.') valid = 1;
			}
		}
		if (valid == 1) {
			//printf("%d was deemed as valid and added to sum.\n", nums[index]);
			sum += nums[index];
			valid = 0;
		}
		ptr += size;
		index++;
		ptr = strpbrk(ptr, "123456789");
	}
	while (!feof(input)) {
		strcpy_s(prevLine, 142, currLine);
		strcpy_s(currLine, 142, nextLine);
		fgets(nextLine, 142, input);

		ptr = strpbrk(currLine, "123456789");
		while (ptr != NULL) {
			pos = ptr - currLine;
			if ((nums[index] / 100) > 0) size = 3;
			else if ((nums[index] / 10) > 0) size = 2;
			else size = 1;
			if ((pos != 0) && (currLine[pos - 1] != '.')) valid = 1;
			else if (((pos + size) < 140) && (currLine[pos + size] != '.')) valid = 1;
			else {
				if (pos == 0) {
					offset = 1;
				}
				else if ((pos + size) > 139) {
					offset = 1;
					pos--;
				}
				else pos--;
				for (int i = 0; i < size + 2 - offset; ++i) {
					if (nextLine[pos + i] != '.') valid = 1;
					else if (prevLine[pos + i] != '.') valid = 1;
				}
			}
			if (valid == 1) {
				//printf("%d was deemed as valid and added to sum.\n", nums[index]);
				sum += nums[index];
				valid = 0;
			}
			ptr += size;
			index++;
			offset = 0;
			ptr = strpbrk(ptr, "123456789");
		}
		ptr = strpbrk(currLine, "*");
		size = 0;
		while (ptr != NULL) {
			pos = ptr - currLine;
			pos--;
			for (int i = 0; i < 3; ++i) {
				if (isdigit(prevLine[pos + i])) {
					digitPos = pos + i;
					while ((digitPos > -1) && isdigit(prevLine[digitPos])) {
						digitPos--;
					}
					digitPos++;
					while ((digitPos < 140) && isdigit(prevLine[digitPos])) {
						size++;
						digitPos++;
					}
					digitPos -= size;
					while (size > 0) {
						currNum += (prevLine[digitPos] - 48) * pow(10, size - 1);
						size--;
						digitPos++;
					}
					if (found == 0) {
						//printf("stored %d as first number\n", currNum);
						num1 = currNum;
						found++;
					}
					else if (num1 != currNum) {
						//printf("stored %d as second number\n", currNum);
						num2 = currNum;
						found++;
					}
					currNum = 0;
				}
			}
			for (int i = 0; i < 3; ++i) {
				if ((found < 2) && isdigit(currLine[pos + i])) {
					digitPos = pos + i;
					while ((digitPos > -1) && isdigit(currLine[digitPos])) {
						digitPos--;
					}
					digitPos++;
					while ((digitPos < 140) && isdigit(currLine[digitPos])) {
						size++;
						digitPos++;
					}
					digitPos -= size;
					while (size > 0) {
						currNum += (currLine[digitPos] - 48) * pow(10, size - 1);
						size--;
						digitPos++;
					}
					if (found == 0) {
						//printf("stored %d as first number\n", currNum);
						num1 = currNum;
						found++;
					}
					else if (num1 != currNum) {
						//printf("stored %d as second number\n", currNum);
						num2 = currNum;
						found++;
					}
					currNum = 0;
				}
			}
			for (int i = 0; i < 3; ++i) {
				if ((found < 2) && isdigit(nextLine[pos + i])) {
					digitPos = pos + i;
					while ((digitPos > -1) && isdigit(nextLine[digitPos])) {
						digitPos--;
					}
					digitPos++;
					while ((digitPos < 140) && isdigit(nextLine[digitPos])) {
						size++;
						digitPos++;
					}
					digitPos -= size;
					while (size > 0) {
						currNum += (nextLine[digitPos] - 48) * pow(10, size - 1);
						size--;
						digitPos++;
					}
					if (found == 0) {
						//printf("stored %d as first number\n", currNum);
						num1 = currNum;
						found++;
					}
					else if (num1 != currNum) {
						//printf("stored %d as second number\n", currNum);
						num2 = currNum;
						found++;
					}
					currNum = 0;
				}
			}
			if (found == 2) {
				//printf("adding %i * %i to gearsum\n", num1, num2);
				gearSum += num1 * num2;
			}
			currNum = 0;
			found = 0;
			num1 = 0;
			num2 = 0;
			ptr = strpbrk(ptr + 1, "*");
		}
	}
	ptr = strpbrk(nextLine, "123456789");
	while (ptr != NULL) {
		pos = ptr - nextLine;
		if ((nums[index] / 100) > 0) size = 3;
		else if ((nums[index] / 10) > 0) size = 2;
		else size = 1;
		if (nextLine[pos - 1] != '.') valid = 1;
		else if (nextLine[pos + size] != '.') valid = 1;
		else {
			pos--;
			for (int i = 0; i < size + 2; ++i) {
				if (currLine[pos + i] != '.') valid = 1;
			}
		}
		if (valid == 1) {
			//printf("%d was deemed as valid and added to sum.\n", nums[index]);
			sum += nums[index];
			valid = 0;
		}
		ptr += size;
		index++;
		ptr = strpbrk(ptr, "123456789");
	}
	printf("sum is %i\n", sum);
	printf("gearsum is %i\n", gearSum);
}

/* Remarks:
* Haha oh man. When I was thinking about how to tackle part 1, I noted that no number is touched by more than one symbol.
* I thought "well, what if I searched for symbols, and then just captured each number that the symbol is touching?" However,
* I also thought "I don't know how to do that, really, I guess I would just check each adjacent character? But what if the
* same number has multiple digits touching the symbol? How do I not capture it repeatedly? Ughhhhh." So I didn't do that.
* Imagine my delight when I read part 2 and discovered I was going to have to search for a symbol and capture the numbers
* it's touching! The result is this program, in which we do a lot of strange and bad things. Here's what's going on:
* 1) Parse the input for numbers and store them in an array.
* 2) Parse the input again, and when we hit a digit, we found number n. look up number n in the array.
* 3) Determine how many digits that number is, so we know what our search space is going to be.
* 4) Scan every character that's adjacent to the number we found. If we hit a symbol, add our number to the sum.
* 5) This is accomplished by keeping three lines in memory at the same time, so we can look 'up' and 'down' from our number.
* 5) Oh god I have to do the gear thing now. Oh no. What a nightmare. Fine, search for *s.
* 6) When we find a *, search adjacent characters for digits.
* 7) Now we have to capture the number somehow. OK, track backwards from the digit till we hit a nondigit so we know where the first digit is.
* 8) Track forwards so we know how many digits the number is. Great, now string the number together, digit by digit.
* 9) If this is the first number we've captured, just save it. If it's not, see if we captured the same number already. If so, just discard this number.
* 10) Continue searching until we find a different number, then do the same thing to capture it. Wow. We did it. We are incredibly smart.
* 
* Incidentally, even though on the previous day I had decided "I gotta be smarter about input parsing," I still strung an integer together
* digit by digit in the part 2 code. I probably should have just gotten the pointer to the first digit and sscanf'd it, or something. Wowza.
* Anyways, I was still getting my feet wet here. This is a ridiculous method of solving the problem, but it did generate correct output,
* and surely I will be better in future days. Surely!
*/
