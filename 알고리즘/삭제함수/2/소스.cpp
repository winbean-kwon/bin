//임의의 원소를 삭제하는 함수

#include <stdio.h>
#define MAX_ELEMENT 100

typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType* h)
{
	h->heap_size = 0;
}
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}

element delete_max_heap(HeapType * h)
	{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드 중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) 
			break;
		// 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void print_heap(HeapType * h)
{
	for (int i = 1; i <= h->heap_size; i++)
		printf("<%d >", h->heap[i].key);
	printf("\n");
}


element delete_element(HeapType * h, int number)
{ // number를 key로 갖는 element를 삭제한다. 삭제 후에 max heap이 유지되어야 한다
	element item, temp;
	int parent, child;
	parent = 1;
	child = 2;
	item = h->heap[parent], temp = h->heap[(h->heap_size)--];
	for (int i = 1; i <= h->heap_size; i++) //40을 찾아서 삭제
		if (h->heap[i].key == number) {
			parent = i;
			child = 2 * i;
			break;
		}

	
	while (child <= h->heap_size) {
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key))
			child++;
		if (temp.key >= h->heap[child].key)
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

int main()
{
	element e[9] = { {10},{40},{30},{5},{12},{6},{15},{9},{60} };
	HeapType heap1;
	int i;
	

	init(&heap1);
	for (i = 0; i < 9; i++)
		insert_max_heap(&heap1, e[i]);
	print_heap(&heap1);
	int num = 40;
	delete_element(&heap1, num);
	//40이  삭제되었는지 체크한다 
	print_heap(&heap1);
	//max heap인지 체크하는 과정   값이 큰 순서대로 출력되어야 한다
	
	for (i = 0; i < 8; ++i) {
		
		e[i]=delete_max_heap(&heap1);
		printf("<%d >", e[i].key);
	}
}