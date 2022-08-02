/*************************************************************
*	                                                         *
*		  A BINARY TREE PROGRAM BY JAMES WASHINGTON		     *
*															 *
*************************************************************/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct binaryTreeNode
{
    binaryTreeNode* leftSubtree;
    binaryTreeNode* rightSubtree;
    char key;
};
typedef binaryTreeNode* binaryTree;

void validateInput(string&);
void getPreorder(string&);
binaryTree newNode(char);
binaryTree buildTreeUtil(string, int&);
binaryTree buildTree(string);
void preorderTraversal(binaryTree, string&);
void inorderTraversal(binaryTree, string&);
void postorderTraversal(binaryTree, string&);
int height(binaryTree);
void getTreeLevel(binaryTree, int, string&);
void levelorderTraversal(binaryTree, string&);
bool isBSTUtil(binaryTree, binaryTree, binaryTree);
bool isBST(binaryTree);
int countNodes(binaryTree);
bool isFullBT(binaryTree);
bool isCompleteBT(binaryTree, unsigned int, unsigned int);
int pow(int, int);
void header();
void driver();

int main()
{
    header();
    driver();
}

/*************************************************************
*	    THIS FUNCTION VALIDATES THE INPUT OF THE USER	     *
*															 *
*************************************************************/

void validateInput(string& input)
{
    int size;
    bool isValid = false;
    bool check;
    char ch;
    string temp;

    while (!isValid)
    {
        temp = "";

        for (int i = 0; i < input.size(); i++)
        {
            if (input[i] != ' ')
            {
                temp += input[i];
            }
        }

        input = temp;
        check = true;
        size = input.size();

        for (int i = 0; (i < size) && check; i++)
        {
            ch = input[i];

            if ((ch < 'a' || ch > 'z') && (ch < 'A' || ch > 'Z') && (ch < '0' || ch > '9') && 
                (ch < '!' || ch > '.') && (ch < ':' ||  ch > '@') && (ch < '[' || ch > '`'))
            {
                cout << "Invalid input, please try again >> ";
                getline(cin, input);
                cout << endl;

                check = false;
                isValid = false;
            }
            else if (i == size - 1)
            {
                isValid = true;
            }
        }
    }
}

/*************************************************************
*	    THIS FUNCTION GETS THE INPUT FROM THE USER		     *
*															 *
*************************************************************/

void getPreorder(string& preorder)
{
    cout << "Please enter a preorder representation of a tree >> ";
    getline(cin, preorder);
    cout << endl;

    validateInput(preorder);
}

/*************************************************************
*	 THIS FUNCTION CREATES A NEW NODE FOR THE BINARY TREE	 *
*															 *
*************************************************************/

binaryTree newNode(char key)
{
    binaryTree node = new binaryTreeNode;

    node->key = key;
    node->leftSubtree= NULL;
    node->rightSubtree = NULL;

    if (key == '.')
    {
        return NULL;
    }

    return node;
}

/*************************************************************
* THIS FUNCTION BUILDS A BINARY TREE FROM PREORDER TRAVERSAL *
*															 *
*************************************************************/

binaryTree buildTreeUtil(string input, int& index)
{
    if (input.length() == index)
    {
        return NULL;
    }
    else
    {
        binaryTree node = newNode(input[index]);

        if (input[index] != '.' && input[index + 1] == '.' && input[index + 2] == '.' && (input.length() - index == 3))
        {
            index = input.length();
        }
        else if (input[index] != '.' && input[index + 1] == '.' && input[index + 2] == '.')
        {
            index += 3;
        }
        else if (input[index] == '.')
        {
            index++;
        }
        else if (input[index] != '.')
        {
            index++;
            node->leftSubtree = buildTreeUtil(input, index);
            node->rightSubtree = buildTreeUtil(input, index);
        }

        return node;
    }
}

/*************************************************************
* THIS FUNCTION USES THE UTILITY FUNCTIONT TO BUILD THE TREE *
*															 *
*************************************************************/

binaryTree buildTree(string input)
{
    int index = 0;

    return buildTreeUtil(input, index);
}

/*************************************************************
*	      THIS FUNCTION GETS THE PREORDER FOR A TREE		 *
*															 *
*************************************************************/

void preorderTraversal(binaryTree root, string& preorder)
{
    if (root == nullptr)
    {
        return;
    }

    preorder += root->key;
    preorderTraversal(root->leftSubtree, preorder);
    preorderTraversal(root->rightSubtree, preorder);
}

/*************************************************************
*	      THIS FUNCTION GETS THE INORDER FOR A TREE		     *
*															 *
*************************************************************/

void inorderTraversal(binaryTree root, string& inorder)
{
    if (root == nullptr)
    {
        return;
    }
        
    inorderTraversal(root->leftSubtree, inorder);
    inorder += root->key;
    inorderTraversal(root->rightSubtree, inorder);
}

/*************************************************************
*	      THIS FUNCTION GETS THE POSTORDER FOR A TREE		 *
*															 *
*************************************************************/

void postorderTraversal(binaryTree root, string& postorder)
{
    if (root == nullptr)
    {
        return;
    }

    postorderTraversal(root->leftSubtree, postorder);
    postorderTraversal(root->rightSubtree, postorder);
    postorder += root->key;
}

/*************************************************************
*	     THIS FUNCTION GETS THE LEVEL OF A GIVEN TREE		 *
*															 *
*************************************************************/

void getTreeLevel(binaryTree root, int level, string& levelorder)
{
    if (root == nullptr)
    {
        return;
    }
   
    if (level == 1)
    {
        levelorder += root->key;
    }
    else
    {
        getTreeLevel(root->leftSubtree, level - 1, levelorder);
        getTreeLevel(root->rightSubtree, level - 1, levelorder);
    }
}

/*************************************************************
*	       THIS FUNCTION GETS THE HEIGHT FOR A TREE		     *
*															 *
*************************************************************/

int height(binaryTree root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        int leftHeight = height(root->leftSubtree);
        int rightHeight = height(root->rightSubtree);

        if (leftHeight > rightHeight)
        {
            return (leftHeight + 1);
        }
        else
        {
            return (rightHeight + 1);
        }
    }
}

/*************************************************************
*	     THIS FUNCTION GETS THE LEVELORDER FOR A TREE		 *
*															 *
*************************************************************/

void levelorderTraversal(binaryTree root, string& levelorder)
{
    int numOfLevels = height(root);
    
    for (int i = 1; i <= numOfLevels; i++)
    {
        getTreeLevel(root, i, levelorder);
    }
}

/*************************************************************
*	       THIS FUNCTION DETERMINES IF A TREE IS A 	     	 *
*				      BINARY SEARCH TREE					 *
*************************************************************/

bool isBSTUtil(binaryTree root, binaryTree left, binaryTree right)
{
    if (root == NULL)
    {
        return true;
    }

    if (left != NULL && root->key <= left->key)
    {
        return false;
    }

    if (right != NULL && root->key >= right->key)
    {
        return false;
    }

    return isBSTUtil(root->leftSubtree, left, root) && isBSTUtil(root->rightSubtree, root, right);
}

/*************************************************************
*	       THIS FUNCTION DETERMINES IF A TREE IS A 	     	 *
*		 BINARY SEARCH TREE USING THE UTILITY FUNCTION		 *
*************************************************************/

bool isBST(binaryTree root)
{
    return isBSTUtil(root, nullptr, nullptr);
}

/*************************************************************
*	   THIS FUNCTION GETS THE NUMBER OF NODES IN A TREE		 *
*															 *
*************************************************************/

int countNodes(binaryTree root)
{
    if (root == nullptr)
    {
        return 0;
    }
    else
    {
        return (countNodes(root->leftSubtree) + 1 + countNodes(root->rightSubtree));
    }
}

/*************************************************************
*	       THIS FUNCTION DETERMINES IF A TREE IS A 	     	 *
*				      FULL BINARY TREE					     *
*************************************************************/

bool isFullBT(binaryTree root)
{
    int h = height(root);
    int numOfNodes = countNodes(root);

    return (numOfNodes == (pow(2, h) - 1));
}

/*************************************************************
*	       THIS FUNCTION DETERMINES IF A TREE IS A 	     	 *
*				     COMPLETE BINARY TREE					 *
*************************************************************/

bool isCompleteBT(binaryTree root, unsigned int index, unsigned int numOfNodes)
{
    if (root == NULL)
    {
        return true;
    }

    if (index >= numOfNodes)
    {
        return false;
    }

    return (isCompleteBT(root->leftSubtree, 2 * index + 1, numOfNodes) && 
            isCompleteBT(root->rightSubtree, 2 * index + 2, numOfNodes));
}

/*************************************************************
*	     THIS FUNCTION WORKS AS AN EXPONENT FUNCTION		 *
*															 *
*************************************************************/

int pow(int base, int exp)
{
    int ans = 1;

    for (int i = 0; i < exp; i++)
    {
        ans *= base;
    }

    return ans;
}

/*************************************************************
*	 THIS FUNCTION PRINTS OUT THE HEADER FOR THE PROGRAM	 *
*															 *
*************************************************************/

void header()
{
    cout << "/************************************************************** " << endl;
    cout << "*                                                             * " << endl;
    cout << "*                       BINARY TREE                           * " << endl;
    cout << "*                                                             * " << endl;
    cout << "**************************************************************/ " << endl << endl;

    cout << "WELCOME USER!" << endl << endl;
    cout << "# TO GET STARTED, ENTER A PREORDER REPRESENTATION OF A BINARY TREE." << endl;
    cout << "# THE COMPUTER WILL THEN OUTPUT INFO ON THE TREE." << endl;
    cout << "ENJOY THE PROGRAM!!!" << endl << endl;
}

/*************************************************************
*	  THIS FUNCTION WORKS AS THE DRIVER FOR THE PROGRAM	     *
*															 *
*************************************************************/

void driver()
{
    string preorder;
    string inorder;
    string postorder;
    string levelorder;
    string input;
    binaryTree tree;
    bool isBst;
    int numOfNodes;
    int treeHeight;
    bool isFull;
    unsigned int index = 0;
    bool isComplete;


    getPreorder(input);
    tree = buildTree(input);

    preorderTraversal(tree, preorder);
    inorderTraversal(tree, inorder);
    postorderTraversal(tree, postorder);
    levelorderTraversal(tree, levelorder);

    isBst = isBST(tree);
    numOfNodes = countNodes(tree);
    treeHeight = height(tree);
    isFull = isFullBT(tree);
    isComplete = isCompleteBT(tree, index, numOfNodes);

    cout << "TRAVERSALS" << endl << endl;
    cout << "Preorder: " << preorder << endl << endl;
    cout << "Inorder: " << inorder << endl << endl;
    cout << "Postorder: " << postorder << endl << endl;
    cout << "Levelorder: " << levelorder << endl << endl << endl;

    cout << "GENERAL INFO" << endl << endl;
    if (isBst)
    {
        cout << "This tree is a binary search tree." << endl << endl;
    }
    else
    {
        cout << "This tree is not a binary search tree." << endl << endl;
    }

    cout << "This tree has " << numOfNodes << " nodes." << endl << endl;
    cout << "This tree has a height of " << treeHeight << "." << endl << endl;

    if (isFull)
    {
        cout << "This tree is a full binary tree." << endl << endl;
    }
    else
    {
        cout << "This tree is not a full binary tree." << endl << endl;
    }

    if (isComplete)
    {
        cout << "This tree is a complete binary tree." << endl << endl;
    }
    else
    {
        cout << "This tree is not a complete binary tree." << endl << endl;
    }
}