#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;
// 포인터는 주소값 저장 (*)
// 포인터가 가르키는 곳의 값 (&)

class Node
{
public:
	Node() {
		value;
		leftNode = nullptr;
		rightNode = nullptr;
	}
	int value;
	Node* leftNode;
	Node* rightNode;

};

class BST
{
public:
	BST() {
		rootNode = nullptr;
	}

	Node* rootNode;

};

Node* getNode()
{
	return new Node();
}

BST* getBST()
{
	return new BST();
}

int height(BST T);
Node* maxNode(BST& T);
Node* minNode(BST& T);
int noNodes(BST& T);

void insertBST(BST& T, int newKey)
{

	if (T.rootNode == nullptr)
	{
		Node* temp = getNode();
		temp->value = newKey;

		T.rootNode = temp;
		return;
	}

	if (T.rootNode->value > newKey)
	{
		BST* tempBST = getBST();
		tempBST->rootNode = T.rootNode->leftNode;

		insertBST(*tempBST, newKey);
		T.rootNode->leftNode = tempBST->rootNode;
	}
	else if (T.rootNode->value < newKey)
	{
		BST* tempBST = getBST();
		tempBST->rootNode = T.rootNode->rightNode;

		insertBST(*tempBST, newKey);
		T.rootNode->rightNode = tempBST->rootNode;
	}
}

void deleteBST(BST& T, int deleteKey)
{
	// 빈 트리일 경우 return nothing
	if (T.rootNode == nullptr)
		return;

	// key값이 rootNode의 value보다 작은 경우
	if (T.rootNode->value > deleteKey)
	{
		BST* tempBST = getBST();
		tempBST->rootNode = T.rootNode->leftNode;

		deleteBST(*tempBST, deleteKey);

		T.rootNode->leftNode = tempBST->rootNode;
	}
	// key 값이 rootNode의 value보다 큰 경우
	else if (T.rootNode->value < deleteKey)
	{
		BST* tempBST = getBST();
		tempBST->rootNode = T.rootNode->rightNode;

		deleteBST(*tempBST, deleteKey);

		T.rootNode->rightNode = tempBST->rootNode;
	}
	else {
		// 자식이 0개인 경우
		if ((T.rootNode->leftNode == nullptr) && (T.rootNode->rightNode == nullptr))
		{
			T.rootNode = nullptr;
		}
		//자식이 2개인 경우 -- error!
		else if ((T.rootNode->leftNode != nullptr) && (T.rootNode->rightNode != nullptr))
		{
			
			// 높이 비교를 위한 전처리과정
			BST* leftBST = getBST();
			leftBST->rootNode = T.rootNode->leftNode;
			BST* rightBST = getBST();
			rightBST->rootNode = T.rootNode->rightNode;
			// "

			Node* tempNode = getNode();

			// 왼쪽의 높이가 큰 경우
			if (height(*leftBST) >= height(*rightBST))
			{
				tempNode = maxNode(*leftBST);
				deleteBST(T, tempNode->value);

				T.rootNode->value = tempNode->value;
			}
			// 오른쪽의 높이가 큰 경우
			else if(height(*leftBST) < height(*rightBST))
			{
				tempNode = minNode(*rightBST);
				deleteBST(T, tempNode->value);

				T.rootNode->value = tempNode->value;
			}
			// 왼쪽의 높이 = 오른쪽의 높이
			else {
				// 왼쪽 노드의 갯수가 큰 경우
				if (noNodes(*leftBST) > noNodes(*rightBST))
				{
					tempNode = maxNode(*leftBST);
					deleteBST(T, tempNode->value);

					T.rootNode->value = tempNode->value;
				}
				else {
					tempNode = minNode(*rightBST);
					deleteBST(T, tempNode->value);

					T.rootNode->value = tempNode->value;
				}
			}
			
		}
		// 자식이 1개인 경우
		else {
			if (T.rootNode->leftNode != nullptr)
			{
				T.rootNode = T.rootNode->leftNode;
			}
			else {
				T.rootNode = T.rootNode->rightNode;
			}
		}
	}

}


// T의 높이를 반환하는 함수
int height(BST T)
{
	if (T.rootNode == nullptr)
		return -1;

	BST* leftBST = getBST();
	BST* rightBST = getBST();
	leftBST->rootNode = T.rootNode->leftNode;
	rightBST->rootNode = T.rootNode->rightNode;

	return 1 + max(height(*leftBST), height(*rightBST));
}

// BST T의 최대값을 가지는 Node
Node* maxNode(BST &T)
{
	if (T.rootNode->rightNode == nullptr)
		return T.rootNode;

	BST* tempBST = getBST();
	tempBST->rootNode = T.rootNode->rightNode;
	maxNode(*tempBST);
}

// BST T의 최소값을 가지는 Node
Node* minNode(BST& T)
{
	if (T.rootNode->leftNode == nullptr)
		return T.rootNode;

	BST* tempBST = getBST();
	tempBST->rootNode = T.rootNode->leftNode;
	minNode(*tempBST);
}


int noNodes(BST &T) // 트리 노드의 개수
{
	if (T.rootNode == nullptr)
		return 0;

	BST* leftBST = getBST();
	leftBST->rootNode = T.rootNode->leftNode;
	BST* rightBST = getBST();
	rightBST->rootNode = T.rootNode->rightNode;

	return 1 + noNodes(*leftBST) + noNodes(*rightBST);
}

void inorderBST(BST &T)
{
	if (T.rootNode == nullptr)
		return;

	BST leftTree;
	leftTree.rootNode = T.rootNode->leftNode;
	BST rightTree;
	rightTree.rootNode = T.rootNode->rightNode;

	inorderBST(leftTree);
	cout << T.rootNode->value << " ";
	inorderBST(rightTree);

}

void insert(BST &T, int list[], int n)
{
	cout << "start insert" << endl;
	for (int i = 0; i < n; i++)
	{
		insertBST(T, list[i]);
		inorderBST(T);
		cout << endl;
	}
}

void del(BST& T, int list[], int n)
{
	cout << "start delete" << endl;
	for (int i = 0; i < n; i++)
	{
		deleteBST(T, list[i]);
		inorderBST(T);
		cout << endl;
	}
}

int main()
{
	BST T = BST();
	int list[] = { 25,500,33,49,17,403,29,105,39,66,305,44,19,441,390,12,81,50,100,999 };
	int reverseList[] = { 999,100,50,81,12,390,441,19,44,305,66,39,105,29,403,17,49,33,500,25 };
	insert(T, list, (sizeof(list)/sizeof(*list)));

	del(T, list, (sizeof(list) / sizeof(*list)));

	insert(T, list, (sizeof(list) / sizeof(*list)));

	del(T, reverseList, (sizeof(list) / sizeof(*list)));

	
	return 0;
}