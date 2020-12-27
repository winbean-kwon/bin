//교재에 있는 단어들을 AVL 트리에 넣고 화면에 찍는 과제
// + 각 노드의 균형인수도 같이 찍는 과제
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>

// AVL 트리 노드 정의

typedef const char element[100];
typedef struct AVLNode
{
	char *key;
	struct AVLNode* left;
	struct AVLNode* right;
} AVLNode;

int max(int x, int y)
{
	if (x >= y)
		return x;
	else return y;
}
// 트리의 높이를 반환
int get_height(AVLNode* node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left),
			get_height(node->right));

	return height;
}
// 노드의 균형인수를 반환
int get_balance(AVLNode* node)
{
	if (node == NULL) return 0;

	return get_height(node->left)
		- get_height(node->right);
}

// 노드를 동적으로 생성하는 함수
AVLNode* create_node(element key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	node->key = (char*)malloc(sizeof(char));
	strcpy((char*)node->key, key);
	node->left = NULL;
	node->right = NULL;
	return(node);
}

// 오른쪽으로 회전시키는 함수
AVLNode* rotate_right(AVLNode* parent)
{
	AVLNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	// 새로운 루트를 반환
	return child;
}

// 왼쪽으로 회전시키는 함수
AVLNode* rotate_left(AVLNode* parent)
{
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	// 새로운 루트 반환
	return child;
}

// AVL 트리에 새로운 노드 추가 함수
// 새로운 루트를 반환한다. 
AVLNode* insert(AVLNode* node, element key)
{
	// 이진 탐색 트리의 노드 추가 수행
	if (node == NULL)
		return(create_node(key));

	if (strcmp(key, (char*)node->key)<0)
		node->left = insert(node->left, key);
	else if (strcmp(key,(char*)node->key)>0)
		node->right = insert(node->right, key);
	else	// 동일한 키는 허용되지 않음
		return node;

	// 노드들의 균형인수 재계산
	int balance = get_balance(node);

	// LL 타입 처리
	if (balance > 1 && strcmp(key, (char*)node->left->key)<0)
		return rotate_right(node);

	// RR 타입 처리
	if (balance < -1 && strcmp(key, (char*)node->right->key)>0)
		return rotate_left(node);

	// LR 타입 처리
	if (balance > 1 && strcmp(key, (char*)node->left->key)>0)
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	// RL 타입 처리
	if (balance < -1 && strcmp(key,(char*)node->right->key)<0)
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

// 중위 순회 함수
void inorder(AVLNode* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("[%s] ,%d ", root->key, get_balance(root));

		inorder(root->right);
	}
}

//전위순회함수
void preorder(AVLNode* root)
{
	if (root != NULL)
	{

		printf("[%s] ,%d ", root->key, get_balance(root));
		preorder(root->left);
		preorder(root->right);
	}

}
int main(void)
{
	AVLNode* root = NULL;

	// 예제 트리 구축
	root = insert(root, "Dec");
	root = insert(root, "Jan");
	root = insert(root, "Apr");
	root = insert(root, "July");
	root = insert(root, "Aug");
	root = insert(root, "Oct");
	root = insert(root, "Feb");
	root = insert(root, "Sept");
	root = insert(root, "Nov");
	root = insert(root, "June");
	root = insert(root, "May");

	printf("중위 순회 결과 \n");
	inorder(root);
	printf("\n\n");
	printf("전위 순회 결과 \n");
	preorder(root);



	return 0;
}
