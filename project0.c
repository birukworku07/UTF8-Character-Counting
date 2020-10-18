#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <unistd.h>


// creating a struct list
struct list {
	unsigned char input[10];
	int count;
};

//This method returns the number of byte of a unicode character
int charToByte (unsigned char myBytes) {
	   
	   if ((myBytes & (1<<7)) == 0) {
	   	return 1;
	   }
	   else if ((myBytes & (1<<5)) == 0){
	   	return 2;
	   }
	   else if ((myBytes & (1<<4)) == 0) {
		   return 3;
	   }
	   else {
		   return 4;
	   }
 }
//compare method for the qsort
int compare(const void* left, const void* right){
	const struct list* a = (const struct list*)left;
	const struct list* b = (const struct list*)right;
	if (a->count > b->count) {
		return -1;
	}
	else if( a->count < b ->count) {
		return 1;
	}
	else {
		return &right - &left;
	}
}
int main (int argc, char** argv) {
	
	
	unsigned char  myChar[5];
	//dynamically creating an array of struct list with a specified size
       	struct list* myList = (struct list*) malloc (12000000*sizeof(char));
	int counter = 0;
	int length;
	myChar[0] = fgetc(stdin);
	
	//Looping it until the end of file
     while (!(feof(stdin))) {
     		
	     	_Bool found = 0;
		 length = charToByte(myChar[0]);
	       
		
	// Getting the rest of the bytes
	for (int i = 1; i < length; ++i) {
		myChar[i] = fgetc(stdin);
		
	}
	
	//setting the end of character at the end of the char array
	myChar[length] = '\0';
	(myList->input)[length] = '\0';	
	
	if (counter == 0) {
		//memcpy(myList[counter].input, myChar, 5*sizeof(char));
		strcpy(myList[counter].input, myChar);
		myList[counter].count += 1;
		++counter;
	}


	else {
		
          	// handling duplication
		for (int i = 0; i < (counter) && (!found); ++i) {
			if ((strcmp(myList[i].input, myChar)) == 0) {
				myList[i].count += 1;
				found = 1;
			
			}
			
		}
		//if duplicate is not found, add it to a the struct array
		if (!found){

			strcpy(myList[counter].input, myChar);
			myList[counter].count += 1;
			++counter;
			
		}	
	}
	//setting myChar to zero to read in the new character
	memset(myChar, 0, 5*sizeof(char));
	myChar[0] = fgetc(stdin);


     }

     //sorting based on frequency of apperance
    qsort(myList, counter, sizeof(struct list), compare);
	
    for (int i = 0; i < counter; ++i) {
    	printf("%s->%d\n", myList[i].input, myList[i].count);
    }    

	// freeing a dynamically declared array of struct list
	free(myList); 

	   
}
