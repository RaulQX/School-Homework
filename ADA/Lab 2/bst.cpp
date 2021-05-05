#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
#include <queue>

using namespace std;

struct node 
{
	int key;
	struct node* left;
	struct node* right;
	struct node* p;

};

typedef struct node* Node;

Node newNode (int key)
{

	Node add = new node;
	
	add -> key = key;
	add -> left = NULL;
	add -> right = NULL;
	add -> p = NULL;

	return add;
}

void insert(Node* root, Node z) {
	Node x, y;

	y = NULL;
	x = *root;

	while (x != NULL) {

		y = x;

		if (x -> key < z -> key)
			x = x -> right;
		else
			x = x -> left;

	}

	z -> p = y;

	if (y == NULL) 
		*root = z;

	else 

		if (z -> key <= y -> key)
			y -> left = z;

		else y -> right = z;

}

void inorder (Node x) {

	if (x != NULL){

		inorder(x -> left);

		cout << x -> key << " ";
		
		inorder(x -> right);
	}

}

void preorder (Node x) {

	if (x != NULL){

		cout << x -> key << " ";

		preorder(x -> left);
		preorder(x -> right);
	}

}
void postorder (Node x) {

	if (x != NULL){

		postorder(x -> left);
		postorder(x -> right);

		cout << x -> key << " ";
		
	}
}

int height (Node x) {

	int parent = 0;

	int child_left = -1;
	int child_right = -1;

	if (x -> left) 
		child_left = height(x -> left);

	if (x -> right) 
		child_right = height(x -> right);
		
	parent = max(child_left, child_right) + 1;

	return parent;	
}

Node search (Node x, int n) {

	if (x == NULL)
		return NULL;

	if (x -> key == n)
		return x;

	if (n < x -> key)
		return search (x -> left, n);
	else 
		return search (x -> right, n);

}

Node tree_minimum (Node x) {

	while (x -> left)
		x = x -> left;

	return x;
}

Node successor (Node x) {

	if (x -> right)
		return tree_minimum(x -> right);

	Node y = x -> p;

	while ( (y != NULL) && (x == y -> right) ) {

		x = y;
		y = y -> p;

	}

	return y;
}

int getNodesInSubtrees(Node x) {

	int parent = 1;

	int child_left = 0;
	int child_right = 0;

	if (x -> left) {
		child_left = getNodesInSubtrees(x -> left);
		parent += child_left;
	}

	if (x -> right) {
		child_right = getNodesInSubtrees(x -> right);
		parent += child_right;
	}

	if ( (child_right < 0) || (child_left < 0) || (abs(child_left - child_right) > 1) )
		return INT_MIN;

	return parent;
}

bool isPerfectlyBalanced (Node root) {

	if (getNodesInSubtrees(root) < 0)
		return false;

	return true;
}

void SearchClosestK(Node x, int k, int minDiff, Node &nodeMinDiff) {

	if  (x -> key == k) {
		minDiff = 0;
		nodeMinDiff = x;
	}

	int diffLeft = INT_MAX;
	int diffRight = INT_MAX;

	int currDiff = abs(x -> key - k);

	if (x -> left)
		diffLeft = abs(x -> left -> key - k);
	if (x -> right)
		diffRight = abs(x -> right -> key - k);

	if (currDiff < minDiff) {
		minDiff = currDiff;
		nodeMinDiff = x;
	}

	if (diffLeft == diffRight && diffLeft == INT_MAX)
		return;

	if (diffLeft < diffRight)
		SearchClosestK(x -> left, k, minDiff, nodeMinDiff);
	else 
		SearchClosestK(x -> right, k, minDiff, nodeMinDiff);

}

void createInOrderVector (Node x, vector <int> &v) {

	if (x != NULL){

		createInOrderVector(x -> left, v);

		v.push_back(x -> key);
		
		createInOrderVector(x -> right, v);
	}

}

bool CheckExistTwoNodesWithSum(Node root, int sum) {

	vector <int> inorderVect;

	createInOrderVector(root, inorderVect);

	int i = 0;
	int j = inorderVect.size() - 1;

	while (i < j) {

		if (inorderVect[i] + inorderVect[j] == sum){

			cout << inorderVect[i] << " + " << inorderVect[j] << " = " << sum << " -> ";
			return true;
		
		}

		if (inorderVect[i] + inorderVect[j] < sum)
			i++;

		if (inorderVect[i] + inorderVect[j] > sum)
			j--;
	}

	return false;
} 

bool get_full_path(Node curr, Node x, vector <int> &path) {

	if (curr == NULL)
		return false;

	path.push_back(curr -> key);

	if (curr -> key == x -> key) {
		return true;
	}

	if (get_full_path(curr -> left, x, path) || get_full_path(curr -> right, x, path))
		return true;
	
	path.pop_back();
	return false;
}

void printPathFromTo(Node root, int key1, int key2) {

	Node x = new node;
	Node y = new node;

	x = search(root, key1);
	y = search(root, key2);

	vector <int> pathX, pathY, shortPath; 
	//pathx path from root -> x
	//pathy path from root -> y
	//shortpath -> path from x to common ancestor and common ancestor to y 

	get_full_path(root, x, pathX);
	get_full_path(root, y, pathY);
 
	int commonAnc = 0;

	for (int i = pathX.size() - 1; i >= 0 && commonAnc == 0; i--) {
		for (int j = pathY.size() - 1; j >= 0 && commonAnc == 0; j--) {

			if (pathY[j] == pathX[i]) { // find lowest common ancestor
				commonAnc = pathX[i];
				break;

			}
		}
	}

	for (int i = pathX.size() - 1; pathX[i] != commonAnc; i--)
		shortPath.push_back(pathX[i]);

	int sw = 0;

	for (size_t j = 0; j < pathY.size(); j++) {
		if (pathY[j] == commonAnc)
			sw = 1;
		if (sw)
			shortPath.push_back(pathY[j]);
	}

	for (size_t i = 0; i < shortPath.size(); i++)
		cout << shortPath[i] << " ";

	cout << endl;
}

void dfs_sum(Node curr, int s, int currentSum, vector<int> &path) {

	if (curr == NULL)
		return;
	
	path.push_back(curr -> key);
	currentSum += curr -> key;

	if (currentSum == s) {
		for (size_t i = 0; i < path.size(); i++)
			cout << path[i] << " ";

		cout << endl;
	}

	if (curr -> left)
		dfs_sum(curr -> left, s, currentSum, path);

	if (curr -> right)
		dfs_sum(curr -> right, s, currentSum, path);

	path.pop_back();	
}

void printPathsWithSum(Node root, int s) {

	vector <int> path;

	dfs_sum(root, s, 0, path);

}

void printLevels(Node x) {

	queue<Node> bfs;

	bfs.push(x);

	while ( bfs.empty() == 0 ) {

		Node current = bfs.front();

		cout << current -> key << " ";

		if ( current -> left )	
			bfs.push(current -> left);

		if ( current -> right )
			bfs.push(current -> right);
		
		bfs.pop();
	}

}

int main(int argc, char const *argv[])
{

	Node tree = NULL;
	Node balancedTree = NULL;

    insert(&tree,newNode(10));
    insert(&tree,newNode(4));
    insert(&tree,newNode(15));
    insert(&tree,newNode(1));
    insert(&tree,newNode(6));

    insert(&tree,newNode(20));
    insert(&tree,newNode(2));
    insert(&tree,newNode(5));
    insert(&tree,newNode(8));
    insert(&tree,newNode(18));
    insert(&tree,newNode(23));

    cout << "Inorder: ";
	inorder(tree);
	cout << endl;

	cout << "Preorder: ";
	preorder(tree);
	cout << endl;

	cout << "Postorder: ";
	postorder(tree);
	cout << endl;

	// cout << "Height: " << height(tree) << endl;

	// cout << "Search for 3: " << search(tree, 3) << endl;
	// cout << "Search for -2: " << search(tree, -2) << endl;	

	// cout << "Successor of 3: " << successor(tree -> left) -> key << endl;

	// insert(&balancedTree, newNode(10));
	// insert(&balancedTree, newNode(1));
	// insert(&balancedTree, newNode(20));

	// cout << "Preorder: ";
	// preorder(tree);
	// cout << endl;

	// cout<<"Is this tree balanced?: " << isPerfectlyBalanced(tree)<<endl;
	
	// cout << "Preorder: ";
	// preorder(balancedTree);
	// cout << endl;

	// cout<<"Is this tree balanced?: " << isPerfectlyBalanced(balancedTree)<<endl;

	// Node unbalancedTree = NULL;
	// insert(&unbalancedTree,newNode(1));
	// insert(&unbalancedTree,newNode(2));
	// insert(&unbalancedTree,newNode(3));
	// insert(&unbalancedTree,newNode(4));
	// insert(&unbalancedTree,newNode(5));
	// insert(&unbalancedTree,newNode(6));

	// cout << "Preorder: ";
	// preorder(unbalancedTree);
	// cout << endl;

	// cout<<"Is this tree balanced?: " << isPerfectlyBalanced(unbalancedTree)<<endl;

	// Node nodeWithClosestK = new node;

	// SearchClosestK(tree, 12, INT_MAX, nodeWithClosestK);
	// cout<< "Closest k found: " << nodeWithClosestK -> key << endl;

	// cout<<"2 nodes with sum 22 in first tree: "<< CheckExistTwoNodesWithSum(tree, 22) << endl; 
	// cout<<"2 nodes with sum 222 in first tree: "<< CheckExistTwoNodesWithSum(tree, 222) << endl; 

	// cout << "Path from 3 to 10: "; printPathFromTo(tree, 3, 10);

	// cout << "Path with sum 32: "; printPathsWithSum(tree, 32);

	// cout << "Levels: "; printLevels(tree);
	// cout << endl;

	return 0;
}