
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct charInfo {
	int character;
	int count;
} charInfo;

void newChar(const void** head, int insert)
{
	if(*head == NULL) {
		//struct charInto* newOne = (struct charInfo*) malloc(sizeof(struct charInfo));
		struct charInfo* newOne = malloc(sizeof(struct charInfo));
		newOne->character = insert;
		newOne->next = NULL;
		newOne->count = 1;
		*head = newOne;
		return;
	}
	else if(head->character == insert) {
		head->count +=1;
		return;
		
	}
	else {
		newChar(head->next, insert);
	}


}

void printlist(charInfo** head)
{
	while(head != NULL) {
		printf("%c->%d", head->character, head->count);
		head = head->next;

	}
}

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

int main(int argc, char** argv)
{
	int limit = 2000;
	struct charInfo list[limit];
	
	int byte;
		
	while((byte = getchar()) != EOF) 
	{
		// test prints	
		printf("Original byte = %d\n", byte);
		printf("Hex byte = %x\n", byte);
		printf("Bin byte = %d\n", intBin(byte));
		// done
		
		if(byte & (1<<7)) {
			//TODO
		}
		if(byte & (1<<6)) {
			printf("has 7 bits");
			newChar(list, byte);

		}

	}
	printlist(list);


	return 0;
}

