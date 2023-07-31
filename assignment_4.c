#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

#define MAX(l, r) l > r ? l : r


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r) {
    int Left = m - l + 1;
    int Right = r - m;

    int* L = (void*) calloc(Left, sizeof(int));
    int* R = (void*) calloc(Right, sizeof(int));
    extraMemoryAllocated += (Left * sizeof(int)) + (Right * sizeof(int));

    for (int i = 0; i < Left; ++i) L[i] = pData[l + i];
    for (int j = 0; j < Right; ++j) R[j] = pData[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < Left && j < Right)
    {
        if (L[i] <= R[j])
        {
            pData[k] = L[i];
            ++i;
        }
        else
        {
            pData[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < Left)
    {
        pData[k] = L[i];
        ++i; ++k;
    }

    while (j < Right)
    {
        pData[k] = R[j];
        ++j; ++k;
    }

    free(L);
    free(R);
}

void mergeSort(int pData[], int l, int r) {
    if (l >= r) return;

    int m = l + (r - l) / 2;
    mergeSort(pData, l, m);
    mergeSort(pData, m + 1, r);

    merge(pData, l, m, r);
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, item;
	for (int i = 1; i<n; i++){
		item=pData[i];
		j=i-1;

		while (j>=0 && pData[j] > item){
			pData[j+1]=pData[j];
			--j;
	}
	pData[j+1]= item;
	}


}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated

void swap (int *first, int *second){
	int tmp=*first;
	*first=*second;
	*second=tmp;
}
void bubbleSort(int* pData, int n)
{
	int i,j;
	for (i=0; i <n-1; i++){
		for (j=0;j<n-i-1;j++){
			if(pData[j]>pData[j+1]){
				swap(&pData[j],&pData[j+1]);
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	for (int i=0; i<n-1;i++){
		int min =i;

		for (int j=i+1; j<n;j++){
			if (pData[j]<pData[min])
			min = j;
		}
		swap(&pData[i],&pData[min]);
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        for (int i = 0; i < dataSz; ++i) fscanf(inFile, "%d", &(*ppData)[i]);

        fclose(inFile);
    }

    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    printf("\tData:\n\t");
    for (int i = 0; i < (dataSz > 100 ? 100 : dataSz); ++i) printf("%d ", pData[i]);

    printf("\n\t");
    for (int i = MAX(dataSz - 100, 0); i < dataSz; ++i) printf("%d ", pData[i]);

    printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}