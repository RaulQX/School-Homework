#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <random>
#include <queue>

using namespace std;
using namespace std::chrono;

#define bigN 8 //Constant for number of elements
bool comprehension = true; // Make true if you want to see the first exercise (where do rotations happen when inserting)

struct node {// Normal BST node without height
	int key;
	struct node* left;
	struct node* right;
	struct node* p;
};

typedef struct node* Node;

Node newNode (int key) {
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

long height (Node x) {

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

int iterativeHeight (Node x) {

    int height = -1;
    int nodesOnThisLevel = 0;
    
    queue<Node> q;

    if (x != NULL) {
        q.push(x);
        nodesOnThisLevel++;
    }

    while (!q.empty()) {

        Node parent = q.front();
        q.pop();
        nodesOnThisLevel--;

        if (parent -> left)
            q.push(parent -> left);

        if (parent -> right)
            q.push(parent -> right);
        
        if (nodesOnThisLevel == 0) {
            height++;
            nodesOnThisLevel = q.size();
        }

    }

    return height;
}

struct avlNode { 

    int key;
    
    struct avlNode* left;
    struct avlNode* right;
    struct avlNode* parent;

    int height;
};

typedef struct avlNode* AvlNode;

AvlNode newavlNode (int key) {

	AvlNode add =(AvlNode) malloc (sizeof(struct avlNode));
	
	add -> key = key;
    add -> height = 0;

	add -> left = NULL;
	add -> right = NULL;
	add -> parent = NULL;

	return add;
}

int getHeight (AvlNode x) {

    if (x == NULL)
        return -1;
    
    return x -> height;
}

//Rotate, balance and insert functions were adapted from course pptx but I also added the height update

AvlNode rotate_Left (AvlNode x) {
    
    AvlNode y = x -> right;

    x -> right = y -> left;

    if (y -> left != NULL) 
        y -> left -> parent = x;

    y -> parent = x -> parent;

    if (x -> parent != NULL) {

        if (x == x -> parent -> left) 
            x -> parent -> left = y;
        else x -> parent -> right = y;

    }

    y -> left = x;
    x -> parent = y;

    x -> height = max(getHeight(x -> left), getHeight(x -> right)) + 1;
    y -> height = max(getHeight(y -> left), getHeight(y -> right)) + 1;

    return y;
}

AvlNode rotate_Right (AvlNode y) {

    AvlNode x = y -> left;

    y -> left = x -> right;

    if (x -> right != NULL)
        x -> right -> parent = y;

    x -> parent = y -> parent;

    if (y -> parent != NULL) {

        if (y == y -> parent -> right)
            y -> parent -> right = x;
        else y -> parent -> left = x;

    }

    x -> right = y;
    y -> parent = x;

    x -> height = max(getHeight(x -> left), getHeight(x -> right)) + 1;
    y -> height = max(getHeight(y -> left), getHeight(y -> right)) + 1;

    return x;
}

AvlNode balance (AvlNode x) {

    int height_Left = getHeight(x -> left);
    int height_Right = getHeight(x -> right);

    if (abs(height_Left - height_Right) <= 1) {

        if (comprehension)
            cout << "Do nothing: " << height_Left - height_Right << endl;

        return x;
    }

    else if (height_Left > height_Right) {

        AvlNode y = x -> left;

        if (getHeight(y -> left) < getHeight(y -> right)) {

            if (comprehension)
                cout << "Left right and ";

            rotate_Left(y);
        }

        if (comprehension)
            cout << "Left left " << endl;

        return rotate_Right(x);
    }

    else {

        AvlNode y = x -> right;

        if (getHeight(y -> left) > getHeight(y -> right)) {

            if (comprehension)
                cout << "Right left and ";

            rotate_Right(y);
        }

        if (comprehension)
            cout << "Right right " <<endl;

        return rotate_Left(x);
    }

}

AvlNode insertAvl (AvlNode &x, AvlNode z) {

    if (x == NULL) {

        z -> height = 0;

        return z;
    }

    if (z -> key <= x -> key) {

        AvlNode y = insertAvl(x -> left, z);

        x -> left = y;
        y -> parent = x;
        x -> height = y -> height + 1;

    }

    else {

        AvlNode y = insertAvl (x -> right, z);

        x -> right = y;
        y -> parent = x;
        x -> height = y -> height + 1;

    }

    x = balance(x);

    x -> height = max(getHeight(x -> left), getHeight(x -> right)) + 1;

    return x;
}

void printPreorder (AvlNode x) {

    if (x == NULL)
        return;

    cout << x -> key << " ";

    printPreorder(x -> left);
    printPreorder(x -> right);
}

// Function used for comprehension exercise
void printAfterInsert(AvlNode &root, int key) {

    root = insertAvl(root, newavlNode(key));
    printPreorder(root); cout << endl << endl;
}

int main () {

    if (comprehension) {
        AvlNode comprehensionTree = NULL;

        int arr[] = {4, 23, 11, 89, 34, 2, 7, 14, 75, 69, 99, 80};
        int n = sizeof(arr)/sizeof(arr[0]);

        comprehensionTree = insertAvl(comprehensionTree, newavlNode(arr[0]));
        printPreorder(comprehensionTree); cout << endl;

        for (int i = 1; i < n; i++)
            printAfterInsert(comprehensionTree, arr[i]);

    }
    else {
        
        // We put the random numbers in an array so that we insert the same random numbers in both trees
        int *arr = (int *) malloc (sizeof(int) * bigN); 
        if (!arr) {
            cout << "Not enough memory!";
            exit(1);
        }

        AvlNode avlTree = NULL;
        Node normalBST = NULL;
        AvlNode avlTreeIncreasing = NULL;
        Node normalBSTIncreasing = NULL;

        cout << "Building table: (if it takes too long make bigN constant smaller) \n";
        //cout << "Make sure there's enough space on the stack for recursivity on a linked list of " << bigN << " elements! (by command line) \n";

        unsigned seed = system_clock::now().time_since_epoch().count();
        minstd_rand0 generator (seed); //This is a random number generator
        
        for (int i = 0; i < bigN; i++) 
            arr[i] = generator(); //We fill the array

        //high_resolution_clock::now is used to get the time and we use stop - start to get the total time for insertions in each tree

        auto startAvlRandom = high_resolution_clock::now();
        for (int i = 0; i < bigN; i++)
            avlTree = insertAvl(avlTree, newavlNode(arr[i]));
        auto stopAvlRandom = high_resolution_clock::now();

        auto startNormalBSTRandom = high_resolution_clock::now();
        for (int i = 0; i < bigN; i++)
            insert(&normalBST, newNode(arr[i]));
        auto stopNormalBSTRandom = high_resolution_clock::now();

        auto startIncreasingAvl = high_resolution_clock::now();
        for (int i = 0; i < bigN; i++) 
            avlTreeIncreasing = insertAvl(avlTreeIncreasing, newavlNode(i));
        auto stopIncreasingAvl = high_resolution_clock::now();

        auto startIncreasingNormalBST = high_resolution_clock::now();
        for (int i = 0; i < bigN; i++) 
            insert(&normalBSTIncreasing, newNode(i));
        auto stopIncreasingNormalBST = high_resolution_clock::now();
        
        auto durationAVLRand = duration_cast<microseconds>(stopAvlRandom - startAvlRandom);
        auto durationNBSTRand = duration_cast<microseconds>(stopNormalBSTRandom - startNormalBSTRandom); 
        auto durationAVLIncreaasing = duration_cast<microseconds>(stopIncreasingAvl - startIncreasingAvl);
        auto durationNBSTIncreasing = duration_cast<seconds>(stopIncreasingNormalBST - startIncreasingNormalBST); 

        cout << "Avl Random: height = " << getHeight(avlTree) << "; time = " << durationAVLRand.count() << " microseconds" << endl;
        cout << "Simple BST Random: height = " << iterativeHeight(normalBST) << "; time = " << durationNBSTRand.count() << " microseconds" << endl; 
        cout << "Avl increasing: height = " << getHeight(avlTreeIncreasing) << "; time = " << durationAVLIncreaasing.count() << " microseconds" << endl; 
        cout << "Simple BST Increasing order: height = " << iterativeHeight(normalBSTIncreasing) << "; time = " << durationNBSTIncreasing.count() << " seconds" << endl;

        printPreorder(avlTreeIncreasing);
        
        free(arr);
    }

// FOR 1 MILLION NODES
//     Avl Random: height = 23; time = 1002036 microseconds          
// Simple BST Random: height = 50; time = 698838 microseconds     
// Avl increasing: height = 19; time = 556089 microseconds        
// Simple BST Increasing order: height = 999999; time = 2188 seconds

    return 0;
}