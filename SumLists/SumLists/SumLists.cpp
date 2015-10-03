// SumLists.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

class Node
{
public:
	Node(int n) { val = n; next = nullptr; }
	~Node() { std::cout << "Destructing Node with val = " << val << std::endl; }
	//int  getValue() const { return val; }
	//void setValue(int n) { val = n; }
	//Node *getNext() const { return next; }
	//void setNext(Node *nxt){ next = nxt; }

	//private:
	int val;
	Node *next;
};

class LinkedList
{
public:
	LinkedList() { head = nullptr; }
	LinkedList(Node *np) { head = np; }
	~LinkedList();

	void addNodeFront(int val);
	void addNodeBack(int val);
	void deleteNode(int val) { /*TBD*/ }
	void printList() const;
	bool empty() const { return head == nullptr; }
	static LinkedList addListsIterative(const LinkedList &list1, const LinkedList &list2);
	static Node *addListsRecursive(LinkedList &list1, LinkedList &list2);
	static Node *addListsRecursiveMSDFirst(LinkedList &list1, LinkedList &list2);

private:
	static Node *addListsRecursive(Node * const p1, Node * constp2, int carry);
	static Node *addListsRecursiveMSDFirst(Node * const p1, Node * constp2, int &carry);


	Node *head;
};

LinkedList::~LinkedList() {
	std::cout << "LinkedList destructor" << std::endl;
	while (head != nullptr) {
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}
}
void LinkedList::addNodeFront(int n) {
	if (head == nullptr) {
		head = new Node(n);
	}
	else {
		Node *p = head;
		head = new Node(n);
        head->next = p;
	}
}
void LinkedList::addNodeBack(int n) {
	if (head == nullptr) {
		head = new Node(n);
	}
	else {
		Node *p = head;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = new Node(n);
	}
}
void LinkedList::printList() const {
	Node *p = head;
	while (p != nullptr) {
		std::cout << p->val << "->";
		p = p->next;
	}
    std::cout << std::endl;
}

LinkedList LinkedList::addListsIterative(const LinkedList &l1, const LinkedList &l2) {
	LinkedList sum;
	Node *sumNode = nullptr;
	int digitSum = 0;
	int carry = 0;
	Node *p1 = l1.head, *p2 = l2.head;

	while (p1 || p2 || carry > 0) {
		int n1 = p1 ? p1->val : 0;
		int n2 = p2 ? p2->val : 0;
		digitSum = n1 + n2 + carry;
		carry = digitSum / 10;
		digitSum = digitSum % 10;
		if (sum.empty()) {
			sum.addNodeBack(digitSum);
			sumNode = sum.head;
		}
		else {
			sumNode->next = new Node(digitSum);
			sumNode = sumNode->next;
		}
		if (p1 != nullptr) p1 = p1->next;
		if (p2 != nullptr) p2 = p2->next;
	}
	return sum;
}
Node * LinkedList::addListsRecursive(LinkedList &list1, LinkedList &list2) {
	return addListsRecursive(list1.head, list2.head, 0);
}
Node * LinkedList::addListsRecursive(Node * const p1, Node * const p2, int carry) {
	if (p1 == nullptr && p2 == nullptr && carry == 0)
		return nullptr;
	int n1 = p1 ? p1->val : 0;
	int n2 = p2 ? p2->val : 0;
	int sum = n1 + n2 + carry;
	Node *node = new Node(sum % 10);
	
	node->next = addListsRecursive(p1 ? p1->next : nullptr,
		p2 ? p2->next : nullptr,
		(sum > 10) ? 1 : 0);
	return node;
}
Node * LinkedList::addListsRecursiveMSDFirst(LinkedList &list1, LinkedList &list2) {
	return addListsRecursive(list1.head, list2.head, 0);
}
Node * LinkedList::addListsRecursiveMSDFirst(Node * const p1, Node * const p2, int &carry) {
	if (p1 == nullptr && p2 == nullptr)
	{
		carry = 0;
		return nullptr;
	}
	Node *nn = addListsRecursiveMSDFirst(p1->next, p2->next, carry);
	
	int sum = p1->val + p2->val + carry;
	Node *node = new Node(sum % 10);

	node->next = nn;

	return node;
}
int main(int argc, _TCHAR* argv[])
{
	LinkedList list1, list2;
	list1.addNodeFront(9);
	list1.addNodeFront(1);
	list1.addNodeFront(7);

	std::cout << "List 1: ";
	list1.printList();
	
	list2.addNodeFront(2);
	list2.addNodeFront(9);
	list2.addNodeFront(5);
	std::cout << "List 2: ";
	list2.printList();

	LinkedList sumList = LinkedList::addListsIterative(list1, list2);
	std::cout << "Sum List (iterative): ";
	sumList.printList(); 

	LinkedList sumList2 = LinkedList::addListsRecursive(list1, list2);
	std::cout << "Sum List (Recursive): ";
	sumList2.printList();

	LinkedList sumList3 = LinkedList::addListsRecursiveMSDFirst(list1, list2);
	std::cout << "Sum List (Recursive, MSD First): ";
	sumList3.printList();
	return 0;
}

