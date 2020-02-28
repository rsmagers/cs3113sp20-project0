
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


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

	return addMe;
}

int previous(struct charInfo* list, int byte, int spot)
{

	int i = 0;
	int testMe;
	while(i < spot + 1) {
		testMe = (byte & list[i].character);
		// if = increment
		if(byte == testMe) {
			list[i].count +=1;
			return 1;
		}
		// if does not exist
		if(i == spot) 
		{
			return 0;
		}
		// next
		i++;	
	}
	return -1;
}

void printlist(struct charInfo* list, int spot)
{
	for(int i = 0; i < spot + 1; ++i)
	{
		dprintf(STDOUT_FILENO, "Char = %hx, Count = %d\n", list[i].character, list[i].count);
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
		
		if(byte & (1<<7)) 
		{
			//TODO
			printf("How did you get here?\n");
		}
		if(byte & (1<<6)) 
		{
			// Does it exist?
			yesNo = previous(list, byte, spot);
			if(yesNo == -1) 
			{
				printf("something went wrong at previous it returned -1\n");
				printf("Char = %x, Count = %d\n", list[spot].character, list[spot].count);
			}
			if(yesNo == 0) 
			{
				list[spot] = add(byte);
				
			}
			
			spot++;

		}

	}
	printlist(list, spot);


	return 0;
}

