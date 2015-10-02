#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <stack>
#include <stdio.h>

using namespace std;
using namespace System; 
 
//Represents a node of the binary tree with three peculiarities
including the data stored in the node, left and right pointer of the
node

struct TreeNode             
{
 int data;
 struct TreeNode *pLNext;
 struct TreeNode *pRNext;
};

//Represents binary tree class, which has all the functions that can
be performed on a binary tree
 
class MyBTree
{

public:

//Created an instance of node, representing the root node 
TreeNode *pRoot;     

//Default constructor, initializing the root node with null values
 MyBTree()
 {
  pRoot = NULL;

  cout << "Memory Allocated" << endl;
 }
//Destructor which will free the allocated the memory
 ~MyBTree()
 {
  cout << "Memory Freed" << endl;
 }

 bool InsertNode(int value);
 bool SearchBTree(const int value);
 TreeNode * SearchBTreeReturnAddr(int value);
 int HeightOfBTree(TreeNode *pTree);
 int numberofleaf(TreeNode *pTree);
 int numberofnodes(TreeNode *pTree);

// Operator Overloading: (=) makes exact copy of Binary Search Tree
from right to left

 MyBTree& operator = (const MyBTree& srcBTree);   
void PreOrderReturn(TreeNode *pTree);


 // Refer:
http://www.algolist.net/Data_structures/Binary_search_tree/Removal
  
void DeleteNode(const int delData);
 void DeleteNode(TreeNode *pSubRoot, const int delData);

 void PreOrderPrint(TreeNode *pTree);
 void InOrderPrint(TreeNode *pTree);
 void PostOrderPrint(TreeNode *pTree);
 
 void nonRecursiveInOrder(TreeNode *pTree);
 void nonRecursivePreOrder(TreeNode* pTree);
 void nonRecursivePostOrder(TreeNode* pTree);

};

 void MyBTree::DeleteNode(const int delData)
{
 if (pRoot == NULL)
 {
  cout << "Empty: Delete" << endl;
 }
 else
 {
  DeleteNode(pRoot, delData);
 }
}

void MyBTree::DeleteNode(TreeNode *pSubRoot, const int delData)
{
 TreeNode *pDelNode = pSubRoot;
 TreeNode *pDelNodeParent = pSubRoot;

 while (1)
 {
  if (pDelNode) // Searching for the same value
  {
   if (pDelNode->data == delData)
   {
    break;
   }

   pDelNodeParent = pDelNode;   // Parent Node of Removing Node   
   if (delData < pDelNode->data)
   {
    pDelNode = pDelNode->pLNext; // Left Search
   }
   else
   {
    pDelNode = pDelNode->pRNext; // Right Search
   }
  }
  else
  {
   break; // No Value found
  }
 }

 if (pDelNode) // Search Found
 {
  // CASE 1: If this is Leaf, just delete
  if ((pDelNode->pLNext == NULL) && (pDelNode->pRNext ==NULL))
  {
   cout << "Leaf" << endl;

   // Delete Left if target is left of parent node  
   
   if (pDelNodeParent->pLNext == pDelNode)
   {
    pDelNodeParent->pLNext = NULL;
   }
   else
   {
    pDelNodeParent->pRNext = NULL;
   }
   delete pDelNode;
  }
  // CASE 2: if there are childre in both sub tree
  else if ((pDelNode->pLNext != NULL) && (pDelNode->pRNext != NULL))
  {
   cout << "Sub Trees Exist in Both" << endl;

   TreeNode *pLmaxSubTree = pDelNode->pLNext; // Max Value Node in Left sub-tree
   TreeNode *pLmaxSubTreeParent = pDelNode->pLNext; // Parent of Max Value Node in Left sub-tree

   // Looping to find the MAX
   while (pLmaxSubTree->pRNext != NULL)
   {
    pLmaxSubTreeParent = pLmaxSubTree;
    pLmaxSubTree = pLmaxSubTree->pRNext;
   }
   pDelNode->data = pLmaxSubTree->data;

   // Left Child only
   if (pLmaxSubTree->pLNext != NULL)
   {
    pLmaxSubTree->data = pLmaxSubTree->pLNext->data;
    pLmaxSubTree->pLNext = NULL;
   }

   // No Right child in the left node which will be removed
   // Attach the MAX value Node to left child of deleting node
   if (pLmaxSubTree == pLmaxSubTreeParent)
   {
    pDelNode->pLNext = pLmaxSubTree->pLNext;
   }
   else // Right child exist in the left of deleting node
   {
    pLmaxSubTreeParent->pRNext = pLmaxSubTreeParent>pLNext;



  }
   delete pLmaxSubTree;
  }
  // CASE 3: Left child only in deleting node  
    else if (pDelNode->pLNext != NULL)
  {
   cout << "Left Child Only" << endl;

   pDelNodeParent->pLNext = pDelNode->pLNext;

   delete pDelNode;
  }
  // CASE 4: Right Child only in deleting node
  else if (pDelNode->pRNext != NULL)
  {
   cout << "Right Child Only" << endl;

   if (pDelNode == pSubRoot)
   {
    pSubRoot = pDelNode->pRNext;
   }
   else
   {
    pDelNodeParent->pRNext = pDelNode->pRNext;
   }

   delete pDelNode;
  }
  // No CASE
  else
  {
   cout << "ERROR" << endl;
  }

  cout << delData << " is deleted" << endl;
 }
 else
 {
  cout << "No Such Data: " << delData << " Found" << endl;
 }
}

MyBTree& MyBTree::operator = (const MyBTree& srcBTree) // make it constant not to change the source list
{
 TreeNode *pTempNode = srcBTree.pRoot;

 if (pTempNode == NULL)
 {
  cout << "Empty : Copy" << endl;
 }
 else
 {
  this->PreOrderReturn(pTempNode);
 } 
  
 return (*this);
}

void MyBTree::PreOrderReturn(TreeNode *pTree)
{
 if (pTree == NULL)
 {
  cout << "Empty: PreOderPrint" << endl;
 }
 else
 {
  //cout << " " << pTree->data;
  //return (pTree->data);
  this->InsertNode(pTree->data);
  PreOrderReturn(pTree->pLNext);
  PreOrderReturn(pTree->pRNext);
 }
}

int MyBTree::HeightOfBTree(TreeNode *pTree)
{
 int lcnt = 0;
 int rcnt = 0;

 if (pTree == NULL)
 {
  //cout << "Empty: Height" << endl;
 }
 else
 {
  lcnt = 1 + HeightOfBTree(pTree->pLNext);  //calculating height of left tree 
  rcnt = 1 + HeightOfBTree(pTree->pRNext);  //calculating height of roght tree 
 }

 if (lcnt > rcnt)   //the larger one from both of the baove will be the height of the binary tree
  return (lcnt);
 else
  return (rcnt);
}

TreeNode * MyBTree::SearchBTreeReturnAddr(int value)         
//searching for the value in the binary tree and returning the address in response 
{
 TreeNode *pCurrentNode = pRoot;

 while (pCurrentNode)
 { 
   if (value == pCurrentNode->data)            //if value if
equal to root node, then return the address of root node
  {
   return (pCurrentNode);
   //return (true);
  }
  else if (value < pCurrentNode->data)          //if value is
smaller then root node, search in left sub-tree 
  {
   pCurrentNode = pCurrentNode->pLNext;
  }
  else                                            //if value
is greater then root node, search in right sub-tree
  {
   pCurrentNode = pCurrentNode->pRNext;
  }
 }

 return (NULL);          //if value is not found then return null
}

bool MyBTree::SearchBTree(int value)     //search whether a value is
present or not in the binary tree, returns true or false
{
 TreeNode *pCurrentNode = pRoot;

 while (pCurrentNode)
 {
  if (value == pCurrentNode->data)
  {
   //return (pCurrent);
   return (true);
  }
  else if (value < pCurrentNode->data)
  {
   pCurrentNode = pCurrentNode->pLNext;
  }
  else
  {
   pCurrentNode = pCurrentNode->pRNext;
  }
 }

 return (false);
}

/*
* InsertNode will insert the new node in tree. It is optimized that it
* will automatically balance and sort the tree when new node is
* inserted.
*/
bool MyBTree::InsertNode(int value)
{
 TreeNode *pCurrentNode = pRoot; 
  TreeNode *pParentNode = NULL;

 while (pCurrentNode)
 {
  pParentNode = pCurrentNode;
  if (value < pCurrentNode->data)
  {
   pCurrentNode = pCurrentNode->pLNext;
  }
  else
  {
   pCurrentNode = pCurrentNode->pRNext;
  }
 }

 pCurrentNode = new TreeNode;
 pCurrentNode->pLNext = pCurrentNode->pRNext = NULL;
 pCurrentNode->data = value;

 if (pRoot == NULL)
 {
  pRoot = pCurrentNode;

  cout << "Root" << endl;
 }
 else if (value < pParentNode->data)
 {
  pParentNode->pLNext = pCurrentNode;
 }
 else
 {
  pParentNode->pRNext = pCurrentNode;
 }

 return (true);
}


int MyBTree::numberofnodes(TreeNode *pTree)
{
 // checking for tree with no branches
 if (pTree == NULL)
  return 0;
 else
  // recursively calling funct to count no. of nodes in left
and right branch + 1 for root 
  return (numberofnodes(pTree->pLNext) + numberofnodes(pTree>pRNext)
+ 1);

}

int MyBTree::numberofleaf(TreeNode *pTree)
{
 if (pTree == NULL)
  return 0;
 // checking for leaves in left and right branch
 else if (pTree->pLNext == NULL && pTree->pRNext == NULL)
  return 1;
 else
  // recursively calling func to count numberof leaf
  return (numberofleaf(pTree->pLNext) + numberofleaf(pTree>pRNext));

}

bool
isheightbalanced(TreeNode
*pTree,
int
height)
{

if (pTree == NULL) {

  height = 0;
  return true;
 }

 int lh = 0, rh =0;
 int l = 0, r = 0;
 

 l = isheightbalanced(pTree->pLNext, lh);
 r = isheightbalanced(pTree->pRNext, rh);

 height = max(lh, rh) + 1;

 if (((lh - rh < 2) || (rh - lh < 2)))
  return true;

 return false;
}


// data in left sub-tress -> root -> data in right sub-tress
void MyBTree::InOrderPrint(TreeNode *pTree)
{
 if (pTree == NULL)
 {
  //cout << "Empty: InOderPrint" << endl;
 }
 else
 {
  InOrderPrint(pTree->pLNext);
  cout << " " << pTree->data;
  InOrderPrint(pTree->pRNext);
 }
}

// root -> data in left sub-tress -> data in right sub-trees 
void MyBTree::PreOrderPrint(TreeNode *pTree)
{
 if (pTree == NULL)
 {
  //cout << "Empty: PreOderPrint" << endl;
 }
 else
 {
  cout << " " << pTree->data;
  PreOrderPrint(pTree->pLNext);
  PreOrderPrint(pTree->pRNext);
 }
}

// data in left sub-tress -> data in right sub-trees -> root
void MyBTree::PostOrderPrint(TreeNode *pTree)
{
 if (pTree == NULL)
 {
  //cout << "Empty: PostOderPrint" << endl;
 }
 else
 {
  PostOrderPrint(pTree->pLNext);
  PostOrderPrint(pTree->pRNext);
  cout << " " << pTree->data;
 }
}
// data in left sub-tress -> root -> data in right sub-tress, NonRecursively using Stack
void MyBTree::nonRecursiveInOrder(TreeNode *pTree)
{
 stack<TreeNode *> stack;

 TreeNode *pCurrent;

 pCurrent = pRoot;

 while ((pCurrent != NULL) || (!stack.empty()))

  if (pCurrent != NULL)
  {
   stack.push(pCurrent);
   pCurrent = pCurrent->pLNext;
  }
  else
  {
   pCurrent = stack.top();
   stack.pop();
   cout << " " << pCurrent->data;
   pCurrent = pCurrent->pRNext;
  } 
  cout << endl;
}

// root -> data in left sub-tress -> data in right sub-trees, NonRecursively using Stack
void MyBTree::nonRecursivePreOrder(TreeNode* pTree)
{
 stack<TreeNode* > stack;
 TreeNode *pCurrent;

 pCurrent = pRoot;

 while ((pCurrent != NULL) || (!stack.empty()))

  if (pCurrent != NULL)
  {
   cout << " " << pCurrent->data;
   stack.push(pCurrent);
   pCurrent = pCurrent->pLNext;
  }
  else
  {
   pCurrent = stack.top();
   stack.pop();
   pCurrent = pCurrent->pRNext;
  }
 cout << endl;

}

// data in left sub-tress -> data in right sub-trees -> root, NonRecursively using two Stacks
void MyBTree::nonRecursivePostOrder(TreeNode* pRoot)
{
stack<TreeNode* > stack1;
 stack<TreeNode* > output;

 stack1.push(pRoot);
 while (!stack1.empty())
 {
  TreeNode *pCurrent = stack1.top();
  output.push(pCurrent);
  stack1.pop();

  if (pCurrent->pLNext)
   stack1.push(pCurrent->pLNext);
  if (pCurrent->pRNext)
   stack1.push(pCurrent->pRNext);
 }
 while (!output.empty())
 { 
   cout << " " << output.top()->data;
  output.pop();
 }

}

int main(int argc, char* argv[])
{
 MyBTree MyBT;
 MyBTree CopyBT;

 int height,data;
 int input = -1;
 int input5 = -1;
 int input6 = -1;
 int nodes,leaves;
 int searchValue, delValue;
 /*
  MyBT.InsertNode(5);
  MyBT.InsertNode(2);
  MyBT.InsertNode(-4);

  MyBT.InsertNode(3);
  MyBT.InsertNode(18);
  MyBT.InsertNode(21);
  MyBT.InsertNode(19);
  MyBT.InsertNode(25);
  */

 while (input != 0)
 {
  switch (input)
  {
  case 1: //Check if Binary Tree is Empty
   if (MyBT.pRoot == NULL)
   {
    cout << "Binary Search Tree Empty" << endl;
   }
   else
    cout << "Binary Search Tree not Empty " << endl;
   break;

  case 2: //Insert an Item
   cout << "Node to be inserted: " << endl;
   cin >> data;
   MyBT.InsertNode(data);
   break;

  case 3: //Search an Item in Binary Tree
   cout << "Value to be searched: " << endl;
   cin >> searchValue;
   cout << endl; 
   
   if (MyBT.SearchBTree(searchValue))
    cout << "Value " << searchValue << " Found" << endl;
   else
    cout << "Value not Found" << endl;
   cout << endl << endl;
   break;

  case 4: //Delete an Item
   cout << "Please give the value to be deleted" << endl;
   cin >> delValue;
   MyBT.DeleteNode(delValue);
   cout << endl << endl;
   break;

  case 5: //Traverse the binary tree

   cout << "Please select type of traversing:" << endl
    << "1 : In-Order Print" << endl
    << "2 : Pre-Order Print " << endl
    << "3 : Post-Order Print" << endl;

   cin >> input5;

   switch (input5)
   {

   case 1: //In-order print
    cout << "InOrder Print" << endl;
    MyBT.InOrderPrint(MyBT.pRoot);
    cout << endl << endl;
    break;
   case 2: //Pre-Order Print
    cout << "PreOrder Print" << endl;
    MyBT.PreOrderPrint(MyBT.pRoot);
    cout << endl << endl;
    break;
   case 3: //Post-Order Print
    cout << "PostOrder Print" << endl;
    MyBT.PostOrderPrint(MyBT.pRoot);
    cout << endl << endl;
    break;

   default:
    break;

   }
   break;
  case 6: //Non-Recursive traversing the binary tree
    cout << "Please select type of Non-Recursive
traversing:" << endl
    << "1 : In-Order Print" << endl
    << "2 : Pre-Order Print " << endl
    << "3 : Post-Order Print" << endl;
   cin >> input6;

   switch (input6)
   {
   case 1:
    cout << "NonRecursive In-order" << endl;
    MyBT.nonRecursiveInOrder(MyBT.pRoot);
    cout << endl << endl;
    break;

   case 2:
    cout << "NonRecursive Pre-order" << endl;
    MyBT.nonRecursivePreOrder(MyBT.pRoot);
    cout << endl << endl;
    break;

   case 3:
    cout << "NonRecursive Post-order" << endl;
    MyBT.nonRecursivePostOrder(MyBT.pRoot);
    cout << endl << endl;
    break;
   default:
    break;
   }
   break;

  case 7: // Height of Binary Tree
   height = MyBT.HeightOfBTree(MyBT.pRoot);
   cout << "Height: " << height << endl;
   cout << endl << endl;
   break;

  case 8:// Number of Leaves
   leaves = MyBT.numberofleaf(MyBT.pRoot);
   cout << "Number of Leaves = " << leaves << endl;
   break;

  case 9: // Number of Nodes 
   nodes = MyBT.numberofnodes(MyBT.pRoot);
   cout << "Number of nodes =" << nodes << endl;
   break;

  case 10: // Copy the Binary Tree
   cout << "Copy B = A" << endl;
   CopyBT = MyBT;
   
   cout << "In-OrderPrint B" << endl; 
      MyBT.InOrderPrint(CopyBT.pRoot);
   cout << endl << endl;

   cout << "Pre-OrderPrint B" << endl;
   MyBT.PreOrderPrint(CopyBT.pRoot);
   cout << endl << endl;

   cout << "Post-OrderPrint B" << endl;
   MyBT.PostOrderPrint(CopyBT.pRoot);
   cout << endl << endl;
   break;

  case 11: //Balancing the Binary Tree
   if (isheightbalanced(MyBT.pRoot, h))
    cout << "Tree is balanced";
   else
    cout << "Tree is not balanced";
   break;

  default:
   cout << "0 : Exit" << endl
    << "1: Check the Binary Tree if Empty" << endl
    << "2: Insert an Item" << endl
    << "3: Search an Item" << endl
    << "4: Delete an Item" << endl
    << "5: Traverse the Binary Tree" << endl
    << "6: Non-Recursive Traverse" << endl
    << "7: Height of Binary Tree" << endl
    << "8: Number of Leaves in Binary Tree" << endl
    << "9: Number of Nodes in Binary Tree" << endl
    << "10: Copy the Binary Tree" << endl
    << "11: Check if tree is balanced" << endl
    break;
  }
  cout << "Please select an option for Binary Tree Control: ";
  cin >> input;
  cout << endl;
 }
 MyBT.~MyBTree();
  Console::ReadKey();
   return 0;
}
   
   
