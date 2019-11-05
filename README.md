Assigment 8 - Recursion and Binary Search Trees

Assignment Description. In this assignment, you will implement a set data structure using a binary search tree of characters. You will use your set in a hangman-style game.

Create a C++ class named TreeSet.
As an internal class, create a new class inside TreeSet called Node.
Implement the Node class with the following member data and methods:
A member variable of type char for the Node’s key.
Three member variables of type Node for the left, right, and parent links.
Mutator methods for all four member variables, e.g., setParent, setLeft, setRight, and setData.
Implement the TreeSet class with the following member data and methods:
A member variable for the Root of the tree.
A member variable to track the Count of the number of data items in the tree.
Private methods that will act as “helpers”:
findKey(char key, Node n): recursively locates and returns the Node which contains the speciﬁed key in the tree below and including n. Returns null if no such node exists.
findMaximum(Node n): recursively ﬁnds and returns the Node with the largest key in the tree below and including n.
printInorder(Node n): recursively prints the Node called n and its children using an in-order traversal.
Public methods for:
add(char key): adds the key to the set.
You will need to add another private method addAt(char key, Node n) for this method, which recursively adds the key to the correct position below the node n.
remove(char key): removes the key from the set. You may add a helper method removeNode if you so desire.
clear(): clears the set so it is empty.
find(char key): returns true if the set contains the given key.
getCount(): returns the number of keys in the tree.
getHeight(): returns the height of the tree, calculated recursively.
You will need another private method getHeight(Node n) for this method, which recursively calculates the height of the sub-tree starting at n.
Copy the following method to your TreeSet.cpp ﬁle, after the methods you wrote yourself:
/∗ Given a binary search tree, print out its data elements in increasing 
   sorted order. ∗/
void printTree (struct node∗ node) {
if (node == NULL) return;
printTree (node−>left);
printf ("%d ", node−>data);
printTree (node−>right); }

