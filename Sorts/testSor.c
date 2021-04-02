#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <assert.h>
#include "D:\visualProjects\ForTraning\SOR\SOR\SOR.h" // Need to write a path
#define MIN_SIZE 10
#define MAX_SIZE 16000
#define SIZE_STEP 1000
#define REPEAT_COUNT 5
#define NDEBUG

int cmp(const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

void PrintFunction(int *array, int size)
{
	int j = 0;
	for (j = 0; j < size; j++)
	{
		printf("%d ", array[j]);
	}
	printf("\n");
}

void RevriteArray(int *array, int *temp, int size)
{
	int i = 0;
	for (i = 0; i < size; i++)
	{
		temp[i] = array[i];
	}
}

void MassRand(int *array, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		array[i] = rand() % 20 - 10;
	}
}

int main(void)
{
	HINSTANCE h;
	sort_info_t *sorts = NULL;
	LARGE_INTEGER tps;

#ifdef NDEBUG
	LARGE_INTEGER start, end;
	double dt = 0;
	int k = 0;
#endif

	int size = 0, i = 0, j = 0;
	int numArray[MAX_SIZE], tempArray[MAX_SIZE];
	FILE *file = NULL;
	errno_t err;

	sort_info_t*(*DllFunc) (int *count);

	h = LoadLibrary("SOR.dll");

	if (!h)
	{
		printf("Something gona wrong\n");
		system("pause");
		return -1;
	}
	else
		printf("Library loads success\n");

	DllFunc = (sort_info_t*(*) (int *count))
		GetProcAddress(h, "GetSortList");

	if (!DllFunc)
	{
		printf("Error! The function is not exist\n");
		system("pause");
		return -1;
	}
	else
		printf("Function load success\n");

	err = fopen_s(&file, "reserchResults2.csv", "w");

	if (err != 0)
	{
		printf("file open error\n");
		system("pause");
		return -1;
	}
	else
		printf("File open success\n");

	sorts = DllFunc(&size);
	printf("%d\n", size);

	QueryPerformanceFrequency(&tps);
	for (i = 0; i < size; i++)
	{
		srand(1);
		printf("%s\n", sorts[i].name);
		fprintf(file, "%s\n", sorts[i].name);

		for (j = MIN_SIZE; j <= MAX_SIZE; j += SIZE_STEP)
		{
			MassRand(numArray, j);

            #ifdef DEBUG
			RevriteArray(numArray, tempArray, j);
            PrintFunction(numArray, j);
			printf("QSORT standart result\n");
			qsort(tempArray, j, sizeof(int), cmp);
			PrintFunction(tempArray, j);
			RevriteArray(numArray, tempArray, j);
			printf("Mysort result\n");
			sorts[i].sort(tempArray, j);
			PrintFunction(tempArray, j);
			printf("\n");
            #endif

            #ifdef NDEBUG
			for (k = 0; k < REPEAT_COUNT; k++)
			{
				RevriteArray(numArray, tempArray, j);
				QueryPerformanceCounter(&start);
				sorts[i].sort(tempArray, j);
				QueryPerformanceCounter(&end);
				dt += ((double)(end.QuadPart - start.QuadPart) / tps.QuadPart * 1000);
			}
			printf("%lf ", dt/REPEAT_COUNT);
			fprintf(file, "%lf\n", dt);
			dt = 0;
            #endif
		}
		fprintf(file, "\n");
		printf("\n");
	}

	FreeLibrary(h);
	err = fclose(file);
	system("pause");
	return 0;
}