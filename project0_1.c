
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct charInfo {
	int character;
	int count;
} charInfo;

int compare(const void* left, const void* right) 
{
	const charInfo* a = (const charInfo *) left;
	const charInfo* b = (const charInfo *) right; 

	if(a -> count > b -> count) {
		return -1;
	}
	else if (a -> count < b -> count) {
		return 1;
	}
	else {
		return &right - &left;
	}
}

int intBin(int start)
{
	if(start == 0) {
		return 0;
	}
	else if(start == 1) {
		return 1;
	}
	return (start % 2) + 10 * intBin(start / 2);
}

charInfo add(int byte) 
{
	struct charInfo addMe;
	addMe.character = byte;
	addMe.count = 1;

	printf("In add character = %x\n", byte);
	return addMe;
}

int previous(struct charInfo* list, int byte, int spot)
{

	int i = 0;
	while(i < spot + 1) {
		if(list[i].character == byte) {
			printf("list[i] = %hx, byte = %hx\n", list[i].character, byte);
			return i;
		}
		else if (i == spot) {
			return 0;
		}
		else {
			i++;
		}
	}
	return -1;
}

void printlist(struct charInfo* list, int spot)
{
	for(int i = 0; i < spot + 1; ++i)
	{
		printf("Char = %x, Count = %d\n", list[i].character, list[i].count);
	}
}

int main(int argc, char** argv)
{
	int limit = 2000;
	int spot = 0;
	struct charInfo list[limit];
	int yesNo;
	int byte;
		
	while((byte = getchar()) != EOF) 
	{
		printf("START - byte = %hx\n", byte);
		if(byte & (1<<7)) {
			//TODO
			printf("How did you get here?\n");
		}
		if(byte & (1<<6)) {
			// Does it exist?
			yesNo = previous(list, byte, spot);
			if(yesNo == -1) {
				printf("something went wrong at previous it returned -1\n");
			}
			if(yesNo == 0) {
				list[spot] = add(byte);
				printf("added\n");
			}
			else {
				list[yesNo].count +=1;
				printf("upped\n");
			}
			spot++;

		}

	}
	printlist(list, spot);


	return 0;
}

