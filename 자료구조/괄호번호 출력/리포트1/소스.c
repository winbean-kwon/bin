//입력받은 문자열에서 괄호의 번호를 출력하는 프로그램
//왼쪽 괄호가 나올 때 마다 괄호번호가 하나씩 증가한다. 
//오른쪽 괄호가 나오면 매칭되는 왼쪽 괄호번호를 출력한다.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ===== 스택 코드의 시작 ===== 
#define MAX_STACK_SIZE 100
typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init_stack(StackType* s)
{
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s)
{
	return (s->top == -1);
}
// 포화 상태 검출 함수
int is_full(StackType* s)
{
	return (s->top == (MAX_STACK_SIZE - 1));
}
// 삽입함수
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else s->data[++(s->top)] = item;
}
// 삭제함수
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[(s->top)--];
}
// 피크함수
element peek(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else return s->data[s->top];
}
// ===== 스택 코드의 끝 ===== 

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
	printf("수식 : ");
	gets_s(line, 100);
	printf("괄호수: ");
	check_matching(line);
	return 0;
}