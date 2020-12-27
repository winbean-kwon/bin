//�Է¹��� ���ڿ����� ��ȣ�� ��ȣ�� ����ϴ� ���α׷�
//���� ��ȣ�� ���� �� ���� ��ȣ��ȣ�� �ϳ��� �����Ѵ�. 
//������ ��ȣ�� ������ ��Ī�Ǵ� ���� ��ȣ��ȣ�� ����Ѵ�.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ===== ���� �ڵ��� ���� ===== 
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// ���� �ʱ�ȭ �Լ�
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� ���� �Լ�
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// ��ȭ ���� ���� �Լ�
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// �����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// ��ũ�Լ�
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== ���� �ڵ��� �� ===== 

int check_matching(char* in)
{
	StackType s;
	int i, n = strlen(in);
	char ch, show;

	init_stack(&s);

	for (i = 0; i < n; i++) {
		ch = in[i];

		switch (ch) {
		case '(':
			push(&s, ch);
			printf("%d ", s.top + 1);
			break;

		case ')':
			if (is_empty(&s)) printf("%d ", s.top + 1);
			else {
				printf("%d ", s.top + 1);
				show = pop(&s);
			}

			break;
		}
	}

	if (!is_empty(&s)) 
		return 0;
	
}

int main(void)
{
	char line[100];
	printf("���� : ");
	gets_s(line, 100);
	printf("��ȣ��: ");
	check_matching(line);
	return 0;
}