#include <stdio.h>
#include <stdlib.h>
#define PAGE_ENTRIES 256
#define BIN "BACKING_STORE.bin"
#define TLB_MAX 16

typedef struct tlb{
	struct tlb *next;
	int pageNumber;
	int frameNumber;	
} tlb_t;

int pageTable[PAGE_ENTRIES];

int maskPageNumber(int data){ //masks out the smallest 8 bits and shifts 8 bits to the right
	return (data & 0xFF00) >> 8;	
}
int maskPageOffset(int data){ //masks out all exept the smallest 8 bits
	return data & 0xFF;
}
int getFrameN(tlb_t *TLB, int pageNumber);
tlb_t *addToTLB(tlb_t *TLB, int pageNumber, int frameNumber);
void printTLB(tlb_t *TLB);
void resize(tlb_t *TLB, int c){
	if (TLB == NULL)
	{
		return;
	}
	if (c == TLB_MAX -1 && TLB -> next != NULL)
	{
		free(TLB -> next);
		TLB -> next = NULL;
	}
	return resize(TLB -> next, c++);	
}
tlb_t *addToTLB(tlb_t *TLB, int pageNumber, int frameNumber){
	tlb_t *new = malloc(sizeof(tlb_t));
	new -> pageNumber = pageNumber;
	new -> frameNumber = frameNumber;
	new -> next = TLB;
	resize(new, 0);
	return new;
}
int getFrameN(tlb_t *TLB, int pageNum){
	if (TLB == NULL)
	{
		return -1;
	}
	if (TLB -> pageNumber == pageNum)
	{
		return TLB -> frameNumber;
	}
	return getFrameN(TLB -> next, pageNum);	
}
void printTLB(tlb_t *TLB){
	if (TLB == NULL)
	{
		return;
	}
	printf("Page: %d, frame: %d\n", TLB -> pageNumber, TLB -> frameNumber);
	printTLB(TLB -> next);	
}
tlb_t *TLBMiss(int *pageNum, int *counter, int *pageFailC, tlb_t *TLB, int *pageTable){
	printf("Pagenum: %d, counter: %d, missCounter: %d, PageTable: %d\n", *pageNum, *counter, *pageFailC, *pageTable);
	if (*pageTable == -1){
				*pageTable = *counter * 256;
				printf("%d\n", *pageTable);
				*counter = *counter + 1;
				return addToTLB(TLB, *pageNum, *counter * 256);
	}
	else{
		printf("asfkasflkjasdfnasflansf,ajsbnflasjfn");
		*pageFailC = *pageFailC + 1;
		return addToTLB(TLB, *pageNum, *pageTable);
	}
}
void test(int *t){
	printf("pointer: %d, val: %d\n", t, *t);
}
int main(int argc,char *argv[]){
	//int test[] = {1, 256, 32768, 32769, 128, 65534, 33153};
	FILE *addresses, *storage;
	int pageNumber, frameNumber, pageOffset, pyshicalNumber, inputCounter = 0, pageT;
	unsigned int counter = 0, missCounter = 0, address, pageFCounter = 0, TLBHit = 0;
	tlb_t *TLB = NULL;
	if (argc < 2 || !(addresses = fopen(argv[1], "r")))
	{
		return 1;
	}
	for (int i = 0; i < PAGE_ENTRIES; i++)
		pageTable[i] = -1;
	storage = fopen(BIN, "rb");
	while (fscanf(addresses, "%d", &address) > 0)
	{
		pageNumber = maskPageNumber(address);
		frameNumber = getFrameN(TLB, pageNumber);
		printf("0: %d\n", frameNumber);
		if (frameNumber == -1)
		{
			printf("1: %d\n", pageTable[pageNumber]);
			TLB = TLBMiss(&pageNumber, &counter, &pageFCounter, TLB, &pageTable[pageNumber]);
			printf("2: %d\n", pageTable[pageNumber]);
			missCounter++;
		}
		else
			TLBHit++;		
		pyshicalNumber = pageTable[pageNumber] | maskPageOffset(address);
		char read = 0;
		fseek(storage, address, SEEK_SET);
		fread(&read, sizeof(read), 1, storage);
		printf("Counter: %d, Pagenumber: %d, PageTable: %d, Pageoffset: %d, Physical: %d\n", counter-1, pageNumber, pageTable[pageNumber], maskPageOffset(address), pyshicalNumber);
	}
	printf("TLB miss rate: %d\n", missCounter);
	printf("TLB hit rate: %d\n", TLBHit);
	printf("Page faoult rate: %d\n", pageFCounter);
	fclose(addresses);
	return 0;
}