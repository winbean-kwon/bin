//2���� �ܼ� ���Ḯ��Ʈ�� �����ϴ� �Լ�
//������������ ������ ���ĵǾ� �ִ� ���, �̷��� ���Ļ��¸� �����ϸ鼭 �պ��� �Ͽ� ���ο� ���Ḯ��Ʈ�� ����

#include <stdio.h>
#include <stdlib.h>

typedef int   element;
typedef struct ListNode {    // ��� Ÿ��
	element data;
	struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("(%d)->", p->data);
	printf("NULL \n");
}

ListNode* insert_last(ListNode* head, element value)
{
	ListNode* p;
	ListNode* temp = 
		(ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL) error("�޸� �Ҵ� ����");
	temp->link = NULL;
	temp->data = value;

	if (head == NULL)
		head = temp;

	else
	{
		for (p = head; p->link != NULL; p = p->link);
		p->link = temp;
	}


	return head;
}

ListNode* merge(ListNode* list1, ListNode* list2)
{
	ListNode* head = NULL;
	ListNode* a = list1;  ListNode* b = list2;
	while (a && b)
	{

		if (a->data > b->data)
		{
			head = insert_last(head, b->data);
			b = b->link;
		}

		else {
			head = insert_last(head, a->data);
			a = a->link;
		}
	}

	

	return head;
}

int main(void)
{
	ListNode* head1 = NULL;
	head1 = insert_last(head1, 1);
	head1 = insert_last(head1, 2);
	head1 = insert_last(head1, 3);
	head1 = insert_last(head1, 7);
	print_list(head1);


	ListNode* head2 = NULL;
	head2 = insert_last(head2, 0);
	head2 = insert_last(head2, 4);
	head2 = insert_last(head2, 5);
	head2 = insert_last(head2, 6);
	print_list(head2);

	ListNode* head3 = NULL;
	head3 = merge(head1, head2);
	print_list(head3);
	return 0;
}
