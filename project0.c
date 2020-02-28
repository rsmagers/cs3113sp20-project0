
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct charInfo {
	char character[4];
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

int addNew(struct charInfo* list, int spot, int depth, int* byte)
{
	// change int to char
	char temp[depth];

	for(int x = 0; x < depth + 1; ++x) 
	{
		temp[x] = byte[x];
		//printf("byte[%d} = %d, temp[%d] = %s\n", x, byte[x], x, temp);
		//list[spot].character[x] = temp[x];
	}
	// do we already have it?
	//printf("Temp: %s\n", temp);

	//int copy = iscopy(list, spot, temp);
	for(int y = 0; y < spot + 2; ++y)
	{
		// if y == spot + 1 then there are no dupes
		if(y == spot + 1)
		{
			struct charInfo newOne;
			newOne.count = 1;
			list[spot] = newOne;

			for(int i = 0; i < depth + 1; ++i)
			{
				list[spot].character[i] = temp[i];
			}	
			return 0;
		}
	
		if(strcmp(list[y].character, temp) == 0)
		{
			list[y].count +=1;
			//printf("================ Plus ONE\n");
			return 1;
		}
	}
	return -1;
}

void printlist(struct charInfo* list, int spot)
{
	for(int i = 0; i < spot + 1; ++i)
	{
		//printf("Spot: %d -> ", spot);
		if(list[i].count > 0)
		{
			dprintf(STDOUT_FILENO,"Spot: %d -> ", spot);
			dprintf(STDOUT_FILENO,"Char = %s, Count = %d\n",list[i].character,list[i].count);
		}
	}
}

int main(int argc, char** argv)
{
	int limit = 99999;
	int spot = 0;
	struct charInfo list[limit];
	int byte[4];
	int depth;
	int success;
		
	while((byte[0] = getchar()) != EOF) 
	{
		depth = 0;
		if(byte[0] & (1<<7)) 
		{
			// pull another byte
			byte[1] = getchar();
			depth++;
			if(byte[0] & (1<<6)) 
			{
				//pull another byte
				byte[2] = getchar();
				depth++;
				if(byte[0] & (1<<5)) 
				{
					//pull another
					byte[3] = getchar();
					depth++;
					success = addNew(list, spot, depth, byte);
				}
				else {
				 	success = addNew(list, spot, depth, byte);
				}

			}
			else {
				success = addNew(list, spot, depth, byte);			
			}
			
		}
		else {
			success = addNew(list, spot, depth, byte);	
		}
		printf("success = %d\n", success);
		spot++;
	}

	printlist(list, spot);
	printf("============================\n");
//	int length = sizeof(list) / sizeof(list[0]);
	//trying spot instead of length;
	qsort(list, spot, sizeof(struct charInfo), compare);
	printlist(list, spot);

	return 0;
}

