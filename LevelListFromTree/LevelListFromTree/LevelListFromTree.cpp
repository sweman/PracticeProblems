// LevelListFromTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <memory>
#include <string>

using namespace std;

class TreeNode{
public:
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int n) { val = n; left = nullptr; right = nullptr; }
	~TreeNode() { cout << "TreeNode Destructor for val = " << val << endl; }
	static void printPreorder(TreeNode *root);
	static void printDFS(TreeNode *root);
	static TreeNode * createSampleTree(int numNodes, int rootVal);

};

void TreeNode::printPreorder(TreeNode *root)
{
	if (root == nullptr)
		return;
	cout << root->val << " ";
	printPreorder(root->left);
	printPreorder(root->right);
}

void TreeNode::printDFS(TreeNode *root)
{
	if (root == nullptr)
		return;
	queue<TreeNode *> q;
	q.push(root);
	while (!q.empty()){
		TreeNode *p = q.front();
		q.pop();
		cout << p->val << " ";
		if (p->left != nullptr)
			q.push(p->left);
		if (p->right != nullptr)
			q.push(p->right);
	}
	cout << endl;
}
TreeNode * TreeNode::createSampleTree(int numNodes, int rootVal)
{
	if (numNodes <= 0)
		return nullptr;
	TreeNode *np = new TreeNode(rootVal);
	np->left = createSampleTree(numNodes / 2, rootVal - numNodes * 10);
	np->right = createSampleTree(numNodes / 2, rootVal + numNodes * 10);
	return np;

}
void printList(list<TreeNode *> &l)
{
	cout << "List: ";
	for (auto np : l) {
		cout << np->val << " ";
	}
	cout << endl;
}

void createLists(vector <list<TreeNode *> > &resultLists, TreeNode *root)
{
	if (root == nullptr) return;
	list<TreeNode *> *curList = new list<TreeNode *> ;
	curList->push_back(root);

	while (curList->size() > 0) {
		resultLists.push_back(*curList);
		list<TreeNode *> parentList = *curList;
		curList = new list < TreeNode * > ;
		for (auto np : parentList) {
			if (np->left != nullptr) curList->push_back(np->left);			
			if (np->right != nullptr) curList->push_back(np->right);
		}
	}
}

//bool findAncestor(TreeNode *root, TreeNode *n1, TreeNode *n2, TreeNode *&ancestor)
bool findAncestor(TreeNode *root, int n1, int n2, TreeNode *&ancestor)

{
	if (root == nullptr)   return false;
	//if (ancestor != nullptr) return true;
	

	bool leftResult = findAncestor(root->left, n1, n2, ancestor);
	bool rightResult = findAncestor(root->right, n1, n2, ancestor);

	if (leftResult && rightResult) {
		// we found the ancestor
		ancestor = root;
		cout << "(Internal) Found ancestor at " << ancestor->val << endl;
		return true;
	}
	
	//if (root->val == n1->val || root->val == n2->val)  return true;
	if (root->val == n1 || root->val == n2)  {
		if (leftResult || rightResult) {
			ancestor = root;
		}
		return true;

	}

	return leftResult || rightResult;
}

void printPaths(TreeNode *root, std::string path)
{
	if (root == nullptr)  return;
	path.append(std::to_string(root->val));
	if (root->left == nullptr && root->right == nullptr) {
		std::cout << path << endl;
	}
	else {
		if (root->left != nullptr) {
			printPaths(root->left, path);
		}
		if (root->right != nullptr) {
			printPaths(root->right, path);
		}
	}
}
int main(int argc, _TCHAR* argv[]) {
/*	TreeNode *tree = TreeNode::createSampleTree(15, 1000);
	cout << "Tree (preorder): " << endl;
	TreeNode::printPreorder(tree);
	cout << endl;
	cout << "Tree (Level order): " << endl;
	TreeNode::printDFS(tree);
	vector <list<TreeNode *> > resultLists;
	createLists(resultLists, tree);

	for (list <TreeNode *> lp : resultLists) {
		printList(lp);
	}
*/
	TreeNode *ancestor = nullptr;
	TreeNode tree2(1);
	tree2.left = new TreeNode(2);
	tree2.right = new TreeNode(3);
	tree2.left->left = new TreeNode(4);
	tree2.left->right = new TreeNode(5);
	tree2.right->left = new TreeNode(6);
	tree2.right->right = new TreeNode(7);
	tree2.left->left->left = new TreeNode(8);
	tree2.left->left->right = new TreeNode(9);
	tree2.left->right->left = new TreeNode(10);
	tree2.left->right->right = new TreeNode(11);
	
	cout << "Tree2 (Level order): " << endl;
	TreeNode::printDFS(&tree2);
	
	cout << "Tree2 paths: " << endl;
	std::string path;
	printPaths(&tree2, path);



/*	if (findAncestor(&tree2, 9, 4, ancestor))
	{
		cout << "findAncestor(&tree2, 9, 4, ancestor): " << endl;
		if (ancestor != nullptr)
			cout << "Found ancestor: " << ancestor->val << endl;
		else
			cout << "Found one node only. So no ancestor for you!" << endl;
	}
	else {
		cout << "You sure you have the right tree? None of the nodes found" << endl;
	}
	if (findAncestor(&tree2, 9, 11, ancestor))
	{
		cout << "findAncestor(&tree2, 9, 11, ancestor): " << endl;
		if (ancestor != nullptr)
			cout << "Found ancestor: " << ancestor->val << endl;
		else
			cout << "Found one node only. So no ancestor for you!" << endl;
	}
	else {
		cout << "You sure you have the right tree? None of the nodes found" << endl;
	}
	*/
	int n1, n2;
	while (1)
	{


		cout << "Enter first node to find common ancestor(-1 to quit): " << endl;
		cin >> n1;
		if (n1 == -1) break;

		cout << "Enter second node to find common ancestor (-1 to quit): " << endl;
		cin >> n2;
		if (n2 == -1) break;
		if (findAncestor(&tree2, n1, n2, ancestor))
		{
			if (ancestor != nullptr)
				cout << "Found ancestor: " << ancestor->val << endl;
			else
				cout << "Found one node only. So no ancestor for you!" << endl;
		}
		else {
			cout << "You sure you have the right tree? None of the nodes found" << endl;
		}
	}

	
}

