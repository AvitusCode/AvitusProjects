#include "SOR.h"
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

void insertionSort(int *array, int N);

void Swap(void *a, void *b, size_t size)
{
	char temp;
	size_t i = 0;

	for (i = 0; i < size; i++)
	{
		temp = *((char*)b + i);
		*((char*)b + i) = *((char*)a + i);
		*((char*)a + i) = temp;
	}
}

//Lomuto's partition. We are using right elem

int partitionLomuto(int *array, int low, int high)
{
	int pivot = array[high];
	int j, i = low - 1; 

	for (j = low; j <= high - 1; j++)
	{
		if (array[j] <= pivot)
		{
			i++;
			if (array[i] != array[j])
				Swap(&array[i], &array[j], sizeof(int));
		}
	}

	Swap(array[i + 1], array[high], sizeof(int));
	
	return (i + 1);
}

void quicksortLomuto(int *array, int low, int high)
{
	int pi;
	if (low < high)
	{
		pi = partitionLomuto(array, low, high);

		quicksortLomuto(array, low, pi - 1);
		quicksortLomuto(array, pi + 1, high);
	}
}

static void _quickSortLomuto(int *array, int size)
{
	int low = 0, high = size - 1;
	quicksortLomuto(array, low, high);
}

//QuickSort using Hoare's. We are using the central element

int partitionHoare(int *array, int low, int high)
{
	int pivot = array[(low+high)/2];
	int i = low - 1, j = high + 1;

	while (true)
	{
		do{
			i++;
		} while (array[i] < pivot);

		do{
			j--;
		} while (array[j] > pivot);

		if (i >= j)
			return j;

		Swap(&array[i], &array[j], sizeof(int));
	}
}

void quicksortHoare(int *array, int low, int high)
{
	int pi;
	if (low < high)
	{
		pi = partitionHoare(array, low, high);

		quicksortHoare(array, low, pi);
		quicksortHoare(array, pi + 1, high);
	}
}

static void _quickSortHoare(int *array, int size)
{
	int low = 0, high = size - 1;
	quicksortHoare(array, low, high);
}

//Random Quicksort. we are use a random pos

int RANDOM(int first,int second)
{
	int pi;
	srand((unsigned int)time(0));
	pi = first + rand() % (second - first);
	return pi;
}

int RandomisedPartition(int *array, int low, int high)
{
	int i = RANDOM(low, high);

	Swap(&array[(low + high) / 2], &array[i], sizeof(int));

	return partitionHoare(array, low, high);
}

void randomQuiqsort(int *array, int low, int high)
{
	int pi;
	if (low < high)
	{
		pi = RandomisedPartition(array, low, high);
		randomQuiqsort(array, low, pi);
		randomQuiqsort(array, pi + 1, high);
	}
}

static void _randomizedQuiqsort(int *array, int size)
{
	int low = 0, high = size - 1;
	randomQuiqsort(array, low, high);
}

//Median of three Quicksort. 

int partitionHorareMid(int *array, int low, int high, int pivot)
{
	int i = low, j = high - 1;

	while (true)
	{
		do{
			i++;
		} while (array[i] < pivot);

		do{
			j--;
		} while (array[j] > pivot);

		if (i >= j)
			break;
		else
			Swap(&array[i], &array[j], sizeof(int));
	}
	
	Swap(&array[i], &array[high - 1], sizeof(int));
	return i;
}


int MedianOfThree(int *array, int low, int high)
{
	int mid;

	mid = (low + high) / 2;

	if (array[low] > array[mid])
		Swap(&array[low], &array[mid], sizeof(int));
	if (array[low] > array[high])
		Swap(&array[low], &array[high], sizeof(int));
	if (array[mid] > array[high])
		Swap(&array[mid], &array[high], sizeof(int));

	Swap(&array[mid], &array[high - 1], sizeof(int));
	return partitionHorareMid(array, low, high, array[high - 1]);
}

void mediaQuickSort(int *array, int low, int high)
{
	int pi;
	if (low < high)
	{
		pi = MedianOfThree(array, low, high);

		mediaQuickSort(array, low, pi - 1);
		mediaQuickSort(array, pi + 1, high);
	}
}

static void _medianQuickSort(int *array, int size)
{
	int low = 0, high = size - 1;
	mediaQuickSort(array, low, high);
	insertionSort(array, size);
}

//Quicksort with Insertion algoritm

void insertionSort(int *array, int N)
{
	int i, key, j;

	for (i = 1; i < N; i++) 
	{
		key = array[i];
		j = i - 1;
		while (j >= 0 && array[j] > key) 
		{
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}

void quickSortInsertion(int *array, int N)
{
	int i = 0, j = N - 1, pi;
	int const MAX = 25;
	pi = array[j / 2];

	do 
	{
		while (array[i] < pi)
			i++;
		while (array[j] > pi) 
			j--;

		if (i <= j) 
		{
			Swap(&array[i], &array[j], sizeof(int));
			i++; 
			j--;
		}

	} while (i <= j);

	if (j > MAX) quickSortInsertion(array, j);
	if (N > i + MAX) quickSortInsertion(array + i, N - i);

}

static void _quickSortMinwithInsertion(int* array, int size)
{
	quickSortInsertion(array, size);
	insertionSort(array, size);
}

//Standart Heapsort

void siftDown(int *array, int root, int bottom)
{
	int maxChild; // индекс максимального потомка
	bool flag = false; // флаг того, что куча сформирована
	// Пока не дошли до последнего ряда
	while ((root * 2 <= bottom) && (!flag))
	{
		if (root * 2 == bottom)    // если мы в последнем ряду, 
			maxChild = root * 2;    // запоминаем левого потомка
		  // иначе запоминаем большего потомока из двух
		else if (array[root * 2] > array[root * 2 + 1])
			maxChild = root * 2;
		else
			maxChild = root * 2 + 1;
		// если элемент вершины меньше максимального потомка
		if (array[root] < array[maxChild])
		{
			Swap(&array[root], &array[maxChild], sizeof(int));
			root = maxChild;
		}
		else
			flag = true; // пирамида сформирована
	}
}

static void _heapSort(int *array, int size)
{
	int i;
	// Формируем нижний ряд пирамиды в итоге наименьший элемент будет на вершине массива
	for (i = (size / 2) - 1; i >= 0; i--)
		siftDown(array, i, size - 1);
	// Просеиваем через пирамиду остальные элементы
	for (i = size - 1; i >= 1; i--)
	{
		Swap(&array[0], &array[i], sizeof(int));
		siftDown(array, 0, i - 1);
	}
}

//Bottom-up heapsort instead finds the path of largest children to the leaf level of the tree using only one comparison per level.

int leafSearch(int *array, int start, int end)
{
	int j = start;

	while ((2 * j + 2) <= end)
	{
		//Определяем, какой из двоих детей j больший
		if (array[2 * j + 2] > array[2 * j + 1])
			j = 2 * j + 2;
		else
			j = 2 * j + 1;
	}
	//На последнем уровне может быть только один ребенок
	if ((2 * j + 1) <= end)
		j = 2 * j + 1;

	return j;
}

void siftDown2(int *array, int start, int end)
{
	int j = leafSearch(array, start, end);
	int temp;

	while (array[start] > array[j])
		j = (j - 1) / 2;
	
	temp = array[j];
	array[j] = array[start];
	while (j > start)
	{
		Swap(&array[(j - 1) / 2], &temp, sizeof(int));
		j = (j - 1) / 2;
	}
}

static void _HeapSortBottomUp(int *array, int size)
{
	int i;
	//Формируем пирамиду
	for (i = (size / 2) - 1; i >= 0; i--)
		siftDown2(array, i, size - 1);
	// Просеиваем через пирамиду остальные элементы
	for (i = size - 1; i > 0; i--)
	{
		Swap(&array[i], &array[0], sizeof(int));
		siftDown2(array, 0, i - 1);
	}
}

// New Sorts
static void _BubleSort(int* array, int size)
{
	int i, j;
	bool flag = false;

	do {
		flag = false;
		for (i = 1; i < size; i++)
			if (array[i] < array[i - 1])
			{
				Swap(&array[i], &array[i - 1], sizeof(int));
				flag = true;
			}

	} while (flag);
}

static void _ShellSort(int* array, int size)
{
	int i, j, step, temp;

	for (step = size / 2; step > 0; step >>= 1)
		for (i = step; i < size; i++)
		{
			temp = array[i];
			for (j = i; j >= step; j -= step)
			{
				if (temp < array[j - step])
					array[j] = array[j - step];
				else
					break;
			}

			array[j] = temp;
		}
}

static void _CombSort(int* array, int size)
{
	double factor = 1.2473309;
	int step = size - 1, i;

	while (step >= 1)
	{
		for (i = 0; i + step < size; i++)
		{
			if (array[i] > array[i + step])
				Swap(&array[i], &array[i + step], sizeof(int));
		}

		step /= factor;
	}
}

static sort_info_t s_sortList[] =
{
  {_quickSortLomuto, SORT_QUICK, SORT_SUBQUADRATIC, "Lomuto" },
  {_quickSortHoare, SORT_QUICK, SORT_SUBQUADRATIC, "Hoare" },
  {_quickSortMinwithInsertion, SORT_QUICK, SORT_SUBQUADRATIC, "WithInsert" },
  {_randomizedQuiqsort, SORT_QUICK, SORT_SUBQUADRATIC, "RandomQuicksort" },
  {_medianQuickSort, SORT_QUICK, SORT_SUBQUADRATIC, "MedianSort" },
  {_heapSort, SORT_HEAP, SORT_QUASILINEAR, "HeapsortFromHigh" },
  {_HeapSortBottomUp, SORT_HEAP, SORT_QUASILINEAR, "HeapsortBottomUp" },
  {_BubleSort, SORT_BUBBLE, SORT_QUADRATIC, "BubleSort" },
  {_ShellSort, SORT_SHELL, SORT_QUADRATIC, "ShellSort" },
  {_CombSort, SORT_COMB, SORT_QUADRATIC, "CombSort" }
};

__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
	*count = sizeof(s_sortList) / sizeof(s_sortList[0]);
	return s_sortList;
}