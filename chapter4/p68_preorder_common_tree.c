#include <stdio.h>
#include <malloc.h>

#define ElementType char
#define Error(str) printf("\n error: %s \n",str)   

struct Tree;
typedef struct Tree *Tree;

Tree createTree();
Tree makeEmpty(Tree t);
Tree insert(ElementType e, Tree t);

// we adopt child-sibling notation
struct Tree
{
	ElementType value;
	Tree firstChild;
	Tree nextSibling;
};

// create a tree with root node
Tree createTree()
{	
	Tree t;

	t = (Tree)malloc(sizeof(struct Tree));
    if(!t) {
        Error("out of space, from func createTree");        
        return NULL;
    }    
	t->firstChild = NULL;
	t->nextSibling = NULL;	
	t->value = '/';
	
	return t;
}

// make the tree empty 
Tree makeEmpty(Tree t)
{
	if(t){
		makeEmpty(t->firstChild);
		makeEmpty(t->nextSibling);		
		free(t);
	}			
	return NULL;
}

//
Tree insert(ElementType e, Tree parent)
{
	Tree child;
	Tree newSibling;
	
	if(!parent){
		Error("for parent tree node is empty , you cannot insert one into the parent node, from func insert");        
        return NULL;
	}

	newSibling = (Tree)malloc(sizeof(struct Tree));
	if(!newSibling) {
        Error("out of space, from func insert");        
        return NULL;
    }
	newSibling->value = e;
	newSibling->nextSibling = NULL;
	newSibling->firstChild = NULL;// building the node with value e over

	child = parent->firstChild;	
	if(!child) {
		parent->firstChild = newSibling;
		return parent;
	}

	while(child->nextSibling)
		child = child->nextSibling; // find the last child of parent node
	child->nextSibling = newSibling;

	return parent;
}

// find the tree root node with value equaling to e
Tree find(ElementType e, Tree root)
{
	Tree temp;

	if(root == NULL)
		return NULL;
	if(root->value == e)
		return root;

	temp = find(e, root->firstChild);	
	if(temp) 
		return temp;
	else
		return 	find(e, root->nextSibling);				
}

// analog print directories and files name in the tree, which involves preorder traversal.
void printPreorder(int depth, Tree root)
{			
	int i;
	
	if(root) {		
		for(i = 0; i < depth; i++)
			printf("    ");
		printf("%c\n", root->value);			
		printPreorder(depth + 1, root->firstChild);									
		printPreorder(depth, root->nextSibling);
	} 
}

int main()
{
	Tree tree;

	tree = createTree();
	
	printf("\n test for insert 'A' 'B' into the parent '/' and 'C' 'D' into the parent 'A' \n");	
	insert('A', tree);	
	insert('B', find('/', tree));	
	insert('C', find('A', tree));
	insert('D', find('A', tree));
	printPreorder(1, tree);

	printf("\n test for insert 'E' 'F' into the parent '/'  \n");	
	insert('E', find('/', tree));
	insert('F', find('/', tree));
	printPreorder(1, tree);

	printf("\n test for insert 'G' 'H' into the parent 'E' and 'I' into the parent 'H' and even 'J' 'K' into the parent 'I' \n");	
	insert('G', find('E', tree));
	insert('H', find('E', tree));
	insert('I', find('H', tree));
	insert('J', find('I', tree));
	insert('K', find('I', tree));
	printPreorder(1, tree);

	return 0;
}