#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);

int main() {
	FILE* input;
	errno_t err;
	int winner[10] = { 0 };
	int nums[25] = { 0 };
	int cards[220] = { 0 };
	int card = 0;
	int matches = 0;
	char line[118] = "";
	char* ptr = NULL;

	err = fopen_s(&input, "input.txt", "r");
	if (err != 0) {
		puts("problem");
		exit(1);
	}

	while (!feof(input)) {
		fgets(line, 118, input);
		ptr = strchr(line, ':'); //pointing at :
		ptr++; //pointing at space after :
		for (int i = 0; i < 10; ++i) {
			sscanf_s(ptr, "%d", &winner[i]); //fill array with winning numbers
			ptr += 3; //pointing at space after last number (or out of bounds :D)
		}
		ptr = strchr(line, '|'); //pointing at |
		ptr++; //pointing at space after |
		for (int i = 0; i < 25; ++i) {
			sscanf_s(ptr, "%d", &nums[i]); //fill array with numbers to match with
			ptr += 3; //pointing at space after last number (or out of bounds :D)
		}
		quickSort(winner, 0, 9); 
		quickSort(nums, 0, 24); //sort arrays now to make finding matches more efficient later

		int n = 0, w = 0;
		while (w < 10 && n < 25) {
			if (winner[w] == nums[n]) { //match, so move onto next winner and next matcher
				matches++;
				w++;
				n++;
			}
			else if (winner[w] > nums[n]) n++; //still trying to find this winner, so move on to next matcher
			else w++; //winner couldn't be found, move on to next winner
		}
		if (matches != 0) {
			for (int i = 0; i < matches; ++i) {
				cards[card + 1 + i] += 1 + cards[card]; //add a card for this winning card, plus a card for all copies of this card we have
			}
			matches = 0;
		}
		card++;
	}

	card = 0;
	for (int i = 0; i < 220; ++i) card += cards[i] + 1; //sum all copies, plus the original cards we had
	printf("total cards %d", card);
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	int temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

/* Remarks:
I was actually happy with this one! I don't recall having any big problems when coding, and the part 2 twist was
handled cleanly. Not much to say other than that. Sometimes the code is not a disaster. */
