/* 
----------Assignment No - 4----------

Construct an expression tree from the given prefix expression eg. 
		
	+--a*bc/def 

and traverse it using post order traversal (non recursive) and then delete the entire tree.	*/

#include<iostream>
#include<cstdlib>
#include<cstdio>     
#include<cstring> 
using namespace std;
 
class TreeNode
{
	public:
	        char data;
	        TreeNode *left, *right;
	        TreeNode(char data)
	        {
	            this->data = data;
	            this->left = NULL;
	            this->right = NULL;
	        }
}; 
 
class StackNode
{
	public:
        	TreeNode *treeNode;
        	StackNode *next;
        	StackNode(TreeNode *treeNode)
        	{
			this->treeNode = treeNode;
			next = NULL;
		}
};
 
class ExpressionTree
{
	private:
		StackNode *top;
	public:
	        ExpressionTree()
        	{
            		top = NULL;
        	}
		void clear()
	        {
	            top = NULL;
	        }
	        void push(TreeNode *ptr)
		{
            		if (top == NULL)
                		top = new StackNode(ptr);
            		else
            		{
                		StackNode *nptr = new StackNode(ptr);
                		nptr->next = top;
                		top = nptr;
            		}
        	}
 	        TreeNode *pop()
		{
			if (top == NULL)
        		{
                		cout<<"Underflow"<<endl;
            		}
            		else
            		{
                		TreeNode *ptr = top->treeNode;
                		top = top->next;
                		return ptr;
            		}
        	}
 		TreeNode *peek()
        	{
            		return top->treeNode;
        	}
		void insert(char val)
		{
			if (isOperator(val))
            		{
                		TreeNode *nptr = new TreeNode(val);
                		nptr->left = pop();
                		nptr->right = pop();
                		push(nptr);
            		}
			else
            		{
                		TreeNode *nptr = new TreeNode(val);
                		push(nptr);
            		}
		}
		bool isOperator(char ch)
	        {
            		return ch == '+' || ch == '-' || ch == '*' || ch == '/';
        	}
		void buildTree(string eqn)
        	{
            		for (int i = eqn.length() - 1; i >= 0; i--)
                		insert(eqn[i]);
        	}
		void postfix()
        	{
            		postOrder(peek());
        	}
		void postOrder(TreeNode *ptr)
        	{
            		if (ptr != NULL)
            		{
                		postOrder(ptr->left);            
                		postOrder(ptr->right);
                		cout<<ptr->data;            
            		}    
        	}
        	void infix()
        	{
            		inOrder(peek());
        	}
		void inOrder(TreeNode *ptr)
        	{
            		if (ptr != NULL)
            		{
                		inOrder(ptr->left);
                		cout<<ptr->data;   
                		inOrder(ptr->right);            
            		}    
        	}
		void prefix()
        	{
            		preOrder(peek());
        	}
		void preOrder(TreeNode *ptr)
		{
			if (ptr != NULL)
            		{
                		cout<<ptr->data;
                		preOrder(ptr->left);
                		preOrder(ptr->right);            
            		}    
        	}
}; 

int main()
{
    string s;
    cout<<"Expression Tree Test"<<endl;
    ExpressionTree et;
    cout<<"\nEnter equation in Prefix form: ";
    cin>>s;
    et.buildTree(s);
    cout<<"\nPrefix  : ";
    et.prefix();
    cout<<"\n\nInfix   : ";
    et.infix();
    cout<<"\n\nPostfix : ";
    et.postfix();
    return 0;
}
