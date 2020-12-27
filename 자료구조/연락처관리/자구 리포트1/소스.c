//���� ���Ḯ��Ʈ�� �̿��� ����ó���� ���α׷�



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//strcmp �� strcpy_s ���̹����� �Լ� ����ϱ� ���ؼ�

typedef struct PhoneBook {	//   PhoneBook Ÿ��
	char name[10];
	char phone[20];
} PhoneBook;

typedef struct DListNode {	// ���߿��� ��� Ÿ��
	struct DListNode* llink;
	PhoneBook data;
	struct DListNode* rlink;
} DListNode;

// ���� ���� ����Ʈ�� �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// ���� ���� ����Ʈ�� ��带 ��� : �̸��� ��ȭ��ȣ ���
void dprint(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("�̸�: %s, ��ȭ��ȣ: %s\n", p->data.name, p->data.phone);
	}
	printf("\n");
}

// ���ο� ��� �̸������� ���ĵ� ��ġ�� ����
void dinsert(DListNode* phead, PhoneBook in)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	DListNode* p;
	p = phead;

	do {
		if (strncmp(in.name, p->data.name,10) > 0 && strncmp(p->rlink->data.name, in.name,10) > 0) // p�� �����Ͱ� in���� �տ� �ְ� p->rlink�� �����Ͱ� in���� �տ����� ��� 
		{																				
			break;
		}

		else if (strncmp(p->data.name, in.name,10) == 0) // p�� �����Ͱ� in�� �������� ���� ���
		{
			printf("����Ʈ�� �̹� �����մϴ�.\n");
			return 0;
		}

		else if (p->rlink == phead) {
			break;
		}
		p = p->rlink; // ������ �̵�
		
	} while (1);

	newnode->data = in;
	newnode->llink = p;
	newnode->rlink = p->rlink;
	p->rlink->llink = newnode;
	p->rlink = newnode;	//newnode�� p�� �����ʿ� ����

	// ������. ������� �������� �Է��ϸ� �տ� �Է��� �۰��ΰ� �з��ż� ������� ���� ����� �Ǳ� �մϴ�.
	// ù��° �Է��ѰŸ� �̸������� ������ ����� �ȵǴ°Ű����ϴ�.

}

// �־��� �̸��� ���� ��� ����
void ddelete(DListNode* phead, char* name)
{
	DListNode* removed;
	removed = phead;

	if (removed->rlink == phead) {
		printf("���� ����Ʈ�� ��������Դϴ�.\n");
		return 0;
	}

	while (1)
	{
		if (strcmp(removed->data.name, name) == 0)        // ��� �� �������� ã�������
		{
			removed->llink->rlink = removed->rlink;         // ������ �ڿ� �ִ� ��带 �տ��ִ� ���� ����
			removed->rlink->llink = removed->llink;			// ������ �տ� �ִ� ��带 �ڿ��ִ� ���� ����
			printf("%s�� ����Ʈ���� �����Ǿ����ϴ�. \n", removed->data.name);

			free(removed);   // �����Ҵ� ����
			return 0;
		}
		else if (removed->rlink == phead)       // ��� �� ���Ҵµ� ��ã�������
		{
			printf("%s�� ����Ʈ�� �������� �ʽ��ϴ�.\n",name);
			return 0;
		}
		removed = removed->rlink;  // �������̵�
	}

} 

// �־��� �̸��� ã�� �̸��� ��ȭ��ȣ�� ���
void dsearch(DListNode* phead, char* name)
{
	DListNode* search;
	search = phead;
	while (1)
	{
		if (strcmp(search->data.name, name) == 0)	// ��� �� �������� ã���� ���
		{
			printf("%s�� ��ȭ��ȣ�� %s�Դϴ�. \n", search->data.name, search->data.phone);
			return 0;
		}
		else if (search->rlink == phead) {	// ��� �� ���Ҵµ� ��ã���� ���
			printf("%s�� ����Ʈ�� �������� �ʽ��ϴ�.\n",name);
			return 0;
		}
		search = search->rlink; // ������ �̵�
	}
}

int main(void)
{
	int menu;		// �޴� ����
	char name[10]; 		// ����, �˻��� �Է¹��� �̸�
	PhoneBook in;		// ���Խ� �Է¹��� ����ó 
	DListNode* head = (DListNode*)malloc(sizeof(DListNode)); // ����� ����
	if (head == NULL) {
		printf("�޸� �Ҵ����\n");
		exit(1);
	}
	init(head);  // ����� �ʱ�ȭ

	for (;;) {
		printf("�޴��� �����Ͻÿ�.\n");
		printf("1. ���� 2. ����, 3, �˻�, 4. ���, 5. ���� : ");
		scanf_s("%d", &menu);
		switch (menu)
		{
		case 1:  // ����
			printf("�̸��� �Է��Ͻÿ�: ");
			scanf_s("%s", in.name, sizeof(in.name));
			printf("��ȭ��ȣ�� �Է��Ͻÿ�: ");
			scanf_s("%s", in.phone, sizeof(in.phone));
			dinsert(head, in);
			break;
		case 2: // ����
			printf("�̸��� �Է��Ͻÿ�: ");
			scanf_s("%s", name, sizeof(name));
			ddelete(head, name);
			break;
		
		case 3: // �˻�
			printf("�̸��� �Է��Ͻÿ�: ");
			scanf_s("%s", name, sizeof(name));
			dsearch(head, name);
			break;
		case 4: // ���
			dprint(head);
			break;
		default: // ����
			exit(0);
		}
	}
	return 0;
}