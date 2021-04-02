#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <vld.h> // Для проверки утечек памяти
#pragma warning(disable: 4996)

#define ASSERT(text) warning(text, #text, __FILE__, __LINE__)

static bool warning(bool cond, char* error, char* file, int line)
{
	if (!cond)
		fprintf(stderr, "%s have an error messege in file"
			"%s at line %d\n", error, file, line);

	return cond;
}

static const size_t DEFAULT = 8;  //Начальное значение для node array
static const double CONST = 0.438; //Примерное значение логарифмированного числа пи
typedef int type;

// Структура кучи
typedef struct node_t
{
	size_t degree;
	bool mark; // В данной реализации – не используется

	struct node_t* left;
	struct node_t* right;
	struct node_t* parent;
	struct node_t* child;

	void* key;
	void* value;
}fib_t;

// Храним указатель на минимыльный объект, массив указателей для функции consolidate, его размер, количество элементом, а также функцию сравнения
typedef struct
{
	fib_t* min;
	fib_t** node_array;
	size_t  node_arr;
	size_t  node_count;
	int(*key_compare)(void*, void*);
}heap_t;

heap_t* FibAlloc(int(*key_compare)(void*, void*))
{
	heap_t* heap;

	heap = (heap_t*)malloc(sizeof(heap_t));

	if (!heap)
		return NULL;

	heap->node_array = (fib_t**)malloc(sizeof(fib_t*) * DEFAULT);

	if (!heap->node_array)
	{
		free(heap);
		return NULL;
	}
	heap->node_arr = DEFAULT;
	heap->node_count = 0;
	heap->min = NULL;
	heap->key_compare = key_compare;

	return heap;
}

static fib_t* Fib_Heap_Alloc(void* key, void* val)
{
	fib_t* node = (fib_t*)malloc(sizeof(fib_t));

	if (!node)
		return NULL;

	node->value = val;
	node->key = key;
	node->child = node->parent = NULL;
	node->right = node->left = node;
	node->degree = 0U;
	node->mark = false;

	return node;
}

bool FibAdd(heap_t* heap, void* key, void* val)
{
	fib_t* node;

	if (!heap)
		return false;

	node = Fib_Heap_Alloc(key, val);

	if (!node)
		return false;

	if (heap->min)
	{
		node->left = heap->min;
		node->right = heap->min->right;
		heap->min->right = node;
		node->right->left = node;

		if (heap->key_compare(key, heap->min->key) < 0)
			heap->min = node;
	}
	else
		heap->min = node;

	heap->node_count++;
	return true;
}

static bool array_status(heap_t* heap, size_t size)
{
	if (heap->node_arr < size)
	{
		free(heap->node_array);
		heap->node_array = (fib_t**)malloc(sizeof(fib_t*) * size);

		if (!heap->node_array)
			return false;

		heap->node_arr = size;

		return true;
	}
	else
		return true;
}

static void link(fib_t* y, fib_t* x)
{
	y->left->right = y->right;
	y->right->left = y->left;

	y->parent = x;

	if (!x->child)
	{
		x->child = y;
		y->right = y;
		y->left = y;
	}
	else
	{
		y->left = x->child;
		y->right = x->child->right;
		x->child->right = y;
		y->right->left = y;
	}

	x->degree++;
	y->mark = false;
}

static void FibConsolidate(heap_t* heap)
{
	size_t array_size = (size_t)(floor(log(heap->node_count) / CONST)) + 1; // Оценка сверху размера массива
	size_t count = 0;
	size_t degree = 0;
	size_t i = 0;
	fib_t* x, * y, * temp, * next;
	x = y = temp = next = NULL;

	array_status(heap, array_size);

	/* Set the internal node array components to NULL. */
	for (i = 0; i < heap->node_arr; i++)
		heap->node_array[i] = NULL;

	count = 0;
	x = heap->min;

	//Сначала считаем потомков, потом производим соответствующие вычисления
	if (x)
	{
		count++;
		x = x->right;

		while (x != heap->min)
		{
			count++;
			x = x->right;
		}
	}

	while (count > 0)
	{
		degree = x->degree;
		next = x->right;

		while (true)
		{
			y = heap->node_array[degree];

			if (y == NULL)
				break;

			if (heap->key_compare(x->key, y->key) > 0)
			{
				temp = y;
				y = x;
				x = temp;
			}

			link(y, x);
			heap->node_array[degree] = NULL;
			degree++;
		}

		heap->node_array[degree] = x;
		x = next;
		count--;
	}

	heap->min = NULL;

	for (i = 0; i < array_size; i++)
	{
		y = heap->node_array[i];

		if (!y)
			continue;

		if (heap->min)
		{
			y->left->right = y->right;
			y->right->left = y->left;

			y->left = heap->min;
			y->right = heap->min->right;
			heap->min->right = y;
			y->right->left = y;

			if (heap->key_compare(y->key, heap->min->key) < 0)
				heap->min = y;
		}
		else
			heap->min = y;
	}
}

void* FibExtractMin(heap_t* heap)
{
	fib_t* z, * x, * temp, * to_free;
	void* ptr;
	size_t count = 0;
	ptr = z = x = temp = to_free = NULL;

	if (!heap)
		return NULL;
	if (!heap->min)
		return NULL;

	z = heap->min;

	count = z->degree;
	x = z->child;

	//Проходим по всем потомкам
	while (count > 0)
	{
		temp = x->right;

		x->left->right = x->right;
		x->right->left = x->left;

		x->left = heap->min;
		x->right = heap->min->right;
		heap->min->right = x;
		x->right->left = x;

		x->parent = NULL;
		x = temp;
		count--;
	}

	z->left->right = z->right;
	z->right->left = z->left;

	ptr = heap->min->value;

	if (z == z->right)
	{
		to_free = heap->min;
		heap->min = NULL;
	}
	else
	{
		to_free = heap->min;
		heap->min = z->right;
		FibConsolidate(heap);
	}

	heap->node_count--;
	free(to_free);
	return ptr;
}

//Посмотреть минимум
void* FibMin(heap_t* heap)
{
	if (!heap)
		return NULL;

	if (heap->min)
		return heap->min->value;

	return NULL;
}

//Объединяем две кучи
heap_t* FibUnion(heap_t** h1, heap_t** h2)
{
	heap_t* h = (heap_t*)malloc(sizeof(heap_t));
	size_t i = 0;

	if (!h)
		return NULL;
	if ((!*h1 || !*h2) || ((*h1)->key_compare != (*h2)->key_compare)) //Нет совпадения по функциям сравнения или есть указатель на нуль
	{
		free(h);
		return NULL;
	}

	h->min = (*h1)->min;
	h->node_count = (*h1)->node_count + (*h2)->node_count;
	h->key_compare = (*h1)->key_compare;
	link((*h1)->min, (*h2)->min);

	if (((*h1)->min == NULL) || (((*h2)->min != NULL) && ((*h2)->min->key < (*h1)->min->key)))
		h->min = (*h2)->min;

	h->node_arr = (*h1)->node_arr + (*h2)->node_arr;
	h->node_array = (fib_t**)malloc(sizeof(fib_t*) * h->node_arr);
	if (!h)
		exit(-1);

	//Освобождение памяти для двух предыдущих указателей
	if ((*h1)->node_array)
		free((*h1)->node_array);
	if ((*h2)->node_array)
		free((*h2)->node_array);

	free((*h1)); free((*h2));
	(*h1) = (*h2) = NULL;
	return h;
}

// Процедуры удаления кучи (освобождение памяти)

static void FibFree(fib_t* node)
{
	fib_t* child;
	fib_t* first_child;
	fib_t* sibling;

	child = node->child;

	if (!child)
	{
		free(node);
		return;
	}

	first_child = child;

	while (true)
	{
		sibling = child->right;
		FibFree(child);
		child = sibling;

		if (child == first_child)
			break;
	}

	free(node);
}

void FibHeapClear(heap_t* heap)
{
	fib_t* current, * sibling, * first_root;

	if (!heap)
		return;
	if (!heap->min)
		return;

	current = heap->min;
	first_root = current;

	while (true)
	{
		sibling = current->right;
		FibFree(current);
		current = sibling;

		if (current == first_root)
			break;
	}

	heap->node_count = 0;
	heap->min = NULL;
}

void FibHeapFree(heap_t* heap)
{
	if (!heap)
		return;

	if (heap->node_array)
		free(heap->node_array);

	FibHeapClear(heap);

	free(heap);
}

//Всякие тесты на работоспособность
int key_cmp(const void* a, const void* b)
{
	return ((int)a) - ((int)b);
}

void FibTests_correct()
{
	heap_t* p_heap, * h1, * h2;
	size_t i, res;
	p_heap = FibAlloc(&key_cmp);

	//Проверки на добавление, выдачу минимума, очистку кучи
	for (i = 0; i < 30; ++i)
	{
		ASSERT(FibAdd(p_heap, i, 30 - i));
	}
	printf("[TEST 1 - complete]\n");

	for (i = 30; i != (size_t)-1; --i)
	{
		res = (size_t)FibExtractMin(p_heap);
		ASSERT(res == i);
	}
	printf("[TEST 2 - complete]\n");

	ASSERT(p_heap->node_count == 0);

	for (i = 10; i < 100; ++i)
	{
		ASSERT(FibAdd(p_heap, i, i));
	}
	printf("[TEST 3 - complete]\n");

	for (i = 10; i < 50; ++i)
	{
		ASSERT((size_t)FibMin(p_heap) == i);
		ASSERT((size_t)FibExtractMin(p_heap) == i);
	}
	printf("[TEST 4 - complete]\n");

	for (i = 50; i < 100; ++i)
	{
		ASSERT((size_t)FibMin(p_heap) == i);
		ASSERT((size_t)FibExtractMin(p_heap) == i);
	}
	printf("[TEST 5 - complete]\n");

	ASSERT(FibMin(p_heap) == NULL);
	ASSERT(FibExtractMin(p_heap) == 0);

	for (i = 20; i < 40; ++i)
	{
		ASSERT(FibAdd(p_heap, i, i));
	}
	FibHeapFree(p_heap);
	printf("[TEST 6 - complete]\n");

	//Последний тест на корректность объединения
	h1 = FibAlloc(&key_cmp);
	h2 = FibAlloc(&key_cmp);

	FibAdd(h1, 12, 12);
	FibAdd(h1, 27, 27);
	FibAdd(h1, 13, 13);
	FibAdd(h1, 7, 7);
	FibAdd(h1, 11, 11);
	FibAdd(h1, 81, 81);
	FibExtractMin(h1);


	FibAdd(h2, 3, 3);
	FibAdd(h2, 5, 5);
	FibAdd(h2, 99, 99);
	FibAdd(h2, 15, 15);
	FibAdd(h2, 8, 8);
	FibExtractMin(h2);


	p_heap = FibUnion(&h1, &h2);
	ASSERT(FibExtractMin(p_heap) == 5);
	ASSERT(FibExtractMin(p_heap) == 8);

	FibHeapFree(p_heap);
	printf("[TEST 7 - complete]\n");
}

int main(void)
{
	FibTests_correct();

	system("pause");
	return 0;
}
