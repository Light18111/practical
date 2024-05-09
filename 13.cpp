#include<bits/stdc++.h>
#include<string.h>
using namespace std ; 

int cmp;

class node
{
	public:
		string word;
		string mean;
		node *left;
		node *right;
		node()
		{
			mean=word="";
			left = right = NULL;
		}
		node(string w,string m)
		{
			word = w;
			mean = m;
			left = right = NULL;
		}
};

class dictionary
{
	node* root;
	int counter;
	node* insert(node*, string , string);
	node* leftRotate(node* );
	node* rightRotate(node* );
	node* inOrderSucc(node*);
	node* findNode(node* r,string w);
	void inOrder(node* );
	void preOrder(node* );
	int height(node *);
	int balanceFactor(node *);
	public:
		dictionary()
		{
			root = NULL;
			counter=0;
		}
		void input(string, string );
		void update(node* r,string w);
		void descending(node * root);
		node* getRoot()
		{
			return root;
		}
};

void dictionary :: input(string a, string b)
{
	root = insert(root,a,b);
}

node* dictionary :: insert(node *r , string w, string m)
{
	if(r==NULL)
	{
		node *temp = new node(w,m);
		r = temp;
		return r;
	}
	else if(w > r -> word)
		r -> right = insert(r -> right, w, m);
	else 
		r -> left = insert(r -> left, w, m);

	int bf = balanceFactor(r);

	if((bf==2))
	{
		if(balanceFactor(r-> left) == 1)
		{
			cout << "RIGHT ROTATION AT " << r  -> word << endl ; 
			return rightRotate(r);
		}
		else
		{
			cout << "LEFT ROTATION AT " << r -> left -> word << endl ; 
			cout << "RIGHT ROTATION AT " << r -> word << endl ; 
			r -> left = leftRotate(r -> left);
			return rightRotate(r);
		}
	}
	else if((bf==-2))
	{
		if(balanceFactor(r-> right) == -1)
		{
			cout << "LEFT ROTATION AT " << r  -> word << endl ; 
			return leftRotate(r);
		}
		else
		{
			cout << "RIGHT ROTATION AT " << r -> right -> word << endl ; 
			cout << "LEFT ROTATION AT " << r -> word << endl ;
			r -> right = rightRotate(r -> right);
			return leftRotate(r);
		}
	}
	return r;
}

int dictionary :: balanceFactor(node *t)
{
	if(t==NULL)
		return 0;
	return height(t-> left) - height(t->right);
}

node* dictionary :: rightRotate(node* t)
{
	node* ptr1 = t -> left;
	node* ptr2 = ptr1 -> right;
	ptr1 -> right = t;
	t -> left = ptr2;
	return ptr1;
}

node* dictionary :: leftRotate(node* t)
{
	node* ptr1 = t -> right;
	node* ptr2 = ptr1 -> left;
	ptr1 -> left = t;
	t -> right = ptr2;
	return ptr1;
}


node* dictionary :: inOrderSucc(node* ptr) 
{ 
    node* current = ptr; 
    while (current->left != NULL) 
        current = current->left; 
    return current; 
}

void dictionary ::update(node* r,string w)
{
	string meaning;
	node* temp=NULL;
	temp=findNode(r,w);
	if(temp != NULL)
	{
		cout<<"keyword found"<<endl;
		cout<<"Old Meaning is: "<<temp->mean<<endl;
		cout<<"Enter new Meaning: ";
		cin>>meaning;
		temp->mean=meaning;
		cout<<"keyword updated..."<<endl;
	}
	else
		cout<<"keyword not found"<<endl;
}

node* dictionary ::findNode(node* r,string w)
{
	if(r != NULL)
	{
		if(r->word==w)
		{
			return r;
		}
		if(r->word > w)
			return findNode(r->left,w);
		return findNode(r->right,w);
	}
	else
	{
		return NULL;
	}
}
void dictionary ::descending(node * root)
{
	if(root!=NULL)
	{
		descending(root->right);
		cout << "WORD : " << root -> word << " MEANING: " << root -> mean << endl;
		descending(root->left);
	}
}

void dictionary :: inOrder(node * ptr)
{
	if(ptr==NULL)
		return ;
	inOrder(ptr -> left);
	cout << "WORD : " << ptr -> word << " MEANING: " << ptr -> mean << endl;
	inOrder(ptr -> right);
}

int dictionary :: height(node *ptr)
{
	if(ptr==NULL)
		return 0;
	return max(height(ptr->left) ,height(ptr->right)) + 1;
}
int main()
{
	int in; 
	dictionary t;
	string a,b;
	do
	{
		cout << "Dictionary" << endl;
		cout << "1. Input a record " << endl;
		cout << "2. Update a record " << endl;
		cout << "3. Descending Order" << endl;
		cout<<"4. Exit"<<endl;
        	cin >> in;
		switch(in)
		{
			case 1:
				cout << "Enter word and meaning repectively: ";
				 cin >> a >>b;
                		t.input(a,b);
                		break;
			case 2:
				cout<<"Enter keyword to update its meaning: ";
				cin>>a;
				t.update(t.getRoot(),a);
				break;
			case 3:
				t.descending(t.getRoot());
				break;
			case 4:
				exit(0);
        	default:
                cout << "End" << endl;
        	}
	}while(in!=5);
}
