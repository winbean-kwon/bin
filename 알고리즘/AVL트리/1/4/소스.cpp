//���翡 �ִ� �ܾ���� AVL Ʈ���� �ְ� ȭ�鿡 ��� ����
// + �� ����� �����μ��� ���� ��� ����
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h> 
#include<stdlib.h> 
#include <string.h>

// AVL Ʈ�� ��� ����

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
// Ʈ���� ���̸� ��ȯ
int get_height(AVLNode* node)
{
	int height = 0;

	if (node != NULL)
		height = 1 + max(get_height(node->left),
			get_height(node->right));

	return height;
}
// ����� �����μ��� ��ȯ
int get_balance(AVLNode* node)
{
	if (node == NULL) return 0;

	return get_height(node->left)
		- get_height(node->right);
}

// ��带 �������� �����ϴ� �Լ�
AVLNode* create_node(element key)
{
	AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
	node->key = (char*)malloc(sizeof(char));
	strcpy((char*)node->key, key);
	node->left = NULL;
	node->right = NULL;
	return(node);
}

// ���������� ȸ����Ű�� �Լ�
AVLNode* rotate_right(AVLNode* parent)
{
	AVLNode* child = parent->left;
	parent->left = child->right;
	child->right = parent;

	// ���ο� ��Ʈ�� ��ȯ
	return child;
}

// �������� ȸ����Ű�� �Լ�
AVLNode* rotate_left(AVLNode* parent)
{
	AVLNode* child = parent->right;
	parent->right = child->left;
	child->left = parent;

	// ���ο� ��Ʈ ��ȯ
	return child;
}

// AVL Ʈ���� ���ο� ��� �߰� �Լ�
// ���ο� ��Ʈ�� ��ȯ�Ѵ�. 
AVLNode* insert(AVLNode* node, element key)
{
	// ���� Ž�� Ʈ���� ��� �߰� ����
	if (node == NULL)
		return(create_node(key));

	if (strcmp(key, (char*)node->key)<0)
		node->left = insert(node->left, key);
	else if (strcmp(key,(char*)node->key)>0)
		node->right = insert(node->right, key);
	else	// ������ Ű�� ������ ����
		return node;

	// ������ �����μ� ����
	int balance = get_balance(node);

	// LL Ÿ�� ó��
	if (balance > 1 && strcmp(key, (char*)node->left->key)<0)
		return rotate_right(node);

	// RR Ÿ�� ó��
	if (balance < -1 && strcmp(key, (char*)node->right->key)>0)
		return rotate_left(node);

	// LR Ÿ�� ó��
	if (balance > 1 && strcmp(key, (char*)node->left->key)>0)
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	// RL Ÿ�� ó��
	if (balance < -1 && strcmp(key,(char*)node->right->key)<0)
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

// ���� ��ȸ �Լ�
void inorder(AVLNode* root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("[%s] ,%d ", root->key, get_balance(root));

		inorder(root->right);
	}
}

//������ȸ�Լ�
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

	// ���� Ʈ�� ����
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

	printf("���� ��ȸ ��� \n");
	inorder(root);
	printf("\n\n");
	printf("���� ��ȸ ��� \n");
	preorder(root);



	return 0;
}
