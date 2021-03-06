
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

typedef struct charInfo {
	char character[6];
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

int addNew(struct charInfo* list, int spot, int depth, int* byte, int* cap)
{
	if(spot > *cap) 
	{
		list = realloc(list, sizeof(list) * 2);
		*cap = sizeof(list) * 2;
	}

	// change int to char
	char temp[depth];

	for(int x = 0; x < depth + 1; ++x) 
	{
		//thsi might need fixed... do we go to depth or depth+1
		temp[x] = byte[x];
	}
	
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
			// trying 5 but might be 6
			list[spot].character[5] = '\0';
			return 0;
		}
	
		//if(strcmp(list[y].character, temp) == 0)
		for(int z = 0; z < depth + 1; ++z)
		{
			if(list[y].character[z] == temp[z])
			{
				list[y].count +=1;
				return 1;
			}
		}
	}
	return -1;
}

void printlist(struct charInfo* list, int spot)
{
	// took off +1 from spot
	for(int i = 0; i < spot + 1; ++i)
	{
		//if(list[i].count > 0)
		//{
			//printf("Spot: %d\n", i);
			if(i == spot)
			{
				dprintf(STDOUT_FILENO,"%s->%d",list[i].character,list[i].count);
			}
			else 
			{
				dprintf(STDOUT_FILENO,"%s->%d\n",list[i].character,list[i].count);
			}
		//}
		//printf("Spot: %d\n", i);
	}
}

int main(int argc, char** argv)
{
	int spot = 0;
	int cap = 1000000;
	//struct charInfo list[99999];
	struct charInfo* list = malloc(cap * sizeof(struct charInfo));
	int byte[5];
	int depth;
	int success;
		// took out = getchar()
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
					if(byte[0] & (1<<4))
					{
						byte[4] = getchar();
						depth++;
						success = addNew(list, spot, depth, byte, &cap);
					}
					else
				       	{
						success = addNew(list, spot, depth, byte, &cap);
					}
				}
				else {
				 	success = addNew(list, spot, depth, byte, &cap);
				}

			}
			else {
				success = addNew(list, spot, depth, byte, &cap);			
			}
			
		}
		else {
			success = addNew(list, spot, depth, byte, &cap);	
						
		}
		if(success == -1) 
		{
			printf("success has failed at spot %d\n", spot);
		}
		if(success == 1)
		{
			// do nothing
		}
		else
		{
			spot++;
		}

	}

	// ditch last byte
	//printf("before sort: \n");
	//printlist(list, spot - 1);
	//printf("after sort: =================================\n");

	qsort(list, spot, sizeof(struct charInfo), compare);
	printlist(list, spot - 2);

	return 0;
}

