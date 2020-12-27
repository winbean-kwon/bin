//이중 연결리스트를 이용한 연락처관리 프로그램



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	//strcmp 및 strcpy_s 라이버러리 함수 사용하기 위해서

typedef struct PhoneBook {	//   PhoneBook 타입
	char name[10];
	char phone[20];
} PhoneBook;

typedef struct DListNode {	// 이중연결 노드 타입
	struct DListNode* llink;
	PhoneBook data;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력 : 이름과 전화번호 출력
void dprint(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("이름: %s, 전화번호: %s\n", p->data.name, p->data.phone);
	}
	printf("\n");
}

// 새로운 노드 이름순으로 정렬된 위치에 삽입
void dinsert(DListNode* phead, PhoneBook in)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	DListNode* p;
	p = phead;

	do {
		if (strncmp(in.name, p->data.name,10) > 0 && strncmp(p->rlink->data.name, in.name,10) > 0) // p의 데이터가 in보다 앞에 있고 p->rlink의 데이터가 in보다 앞에있을 경우 
		{																				
			break;
		}

		else if (strncmp(p->data.name, in.name,10) == 0) // p의 데이터가 in을 비교했을때 같을 경우
		{
			printf("리스트에 이미 존재합니다.\n");
			return 0;
		}

		else if (p->rlink == phead) {
			break;
		}
		p = p->rlink; // 포인터 이동
		
	} while (1);

	newnode->data = in;
	newnode->llink = p;
	newnode->rlink = p->rlink;
	p->rlink->llink = newnode;
	p->rlink = newnode;	//newnode를 p의 오른쪽에 삽입

	// 교수님. 손흥민을 마지막에 입력하면 앞에 입력한 송가인과 분류돼서 손흥민이 먼저 출력이 되긴 합니다.
	// 첫번째 입력한거만 이름순으로 정렬이 제대로 안되는거같습니다.

}

// 주어진 이름을 갖는 노드 삭제
void ddelete(DListNode* phead, char* name)
{
	DListNode* removed;
	removed = phead;

	if (removed->rlink == phead) {
		printf("현재 리스트는 공백상태입니다.\n");
		return 0;
	}

	while (1)
	{
		if (strcmp(removed->data.name, name) == 0)        // 노드 다 돌기전에 찾았을경우
		{
			removed->llink->rlink = removed->rlink;         // 지울노드 뒤에 있는 노드를 앞에있는 노드와 연결
			removed->rlink->llink = removed->llink;			// 지울노드 앞에 있는 노드를 뒤에있는 노드와 연결
			printf("%s이 리스트에서 삭제되었습니다. \n", removed->data.name);

			free(removed);   // 동적할당 해제
			return 0;
		}
		else if (removed->rlink == phead)       // 노드 다 돌았는데 못찾았을경우
		{
			printf("%s이 리스트에 존재하지 않습니다.\n",name);
			return 0;
		}
		removed = removed->rlink;  // 포인터이동
	}

} 

// 주어진 이름을 찾아 이름과 전화번호를 출력
void dsearch(DListNode* phead, char* name)
{
	DListNode* search;
	search = phead;
	while (1)
	{
		if (strcmp(search->data.name, name) == 0)	// 노드 다 돌기전에 찾았을 경우
		{
			printf("%s의 전화번호는 %s입니다. \n", search->data.name, search->data.phone);
			return 0;
		}
		else if (search->rlink == phead) {	// 노드 다 돌았는데 못찾았을 경우
			printf("%s이 리스트에 존재하지 않습니다.\n",name);
			return 0;
		}
		search = search->rlink; // 포인터 이동
	}
}

int main(void)
{
	int menu;		// 메뉴 선택
	char name[10]; 		// 삭제, 검색시 입력받을 이름
	PhoneBook in;		// 삽입시 입력받을 연락처 
	DListNode* head = (DListNode*)malloc(sizeof(DListNode)); // 헤드노드 생성
	if (head == NULL) {
		printf("메모리 할당실패\n");
		exit(1);
	}
	init(head);  // 헤드노드 초기화

	for (;;) {
		printf("메뉴를 선택하시오.\n");
		printf("1. 삽입 2. 삭제, 3, 검색, 4. 출력, 5. 종료 : ");
		scanf_s("%d", &menu);
		switch (menu)
		{
		case 1:  // 삽입
			printf("이름을 입력하시오: ");
			scanf_s("%s", in.name, sizeof(in.name));
			printf("전화번호를 입력하시오: ");
			scanf_s("%s", in.phone, sizeof(in.phone));
			dinsert(head, in);
			break;
		case 2: // 삭제
			printf("이름을 입력하시오: ");
			scanf_s("%s", name, sizeof(name));
			ddelete(head, name);
			break;
		
		case 3: // 검색
			printf("이름을 입력하시오: ");
			scanf_s("%s", name, sizeof(name));
			dsearch(head, name);
			break;
		case 4: // 출력
			dprint(head);
			break;
		default: // 종료
			exit(0);
		}
	}
	return 0;
}