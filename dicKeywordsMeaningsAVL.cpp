/*
----------Assignment 10----------
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting
keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/
Descending order. Also find how many maximum comparisons may require for finding any keyword. Use
Height balance tree and find the complexity for finding a keyword.
*/

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
	node* Delete(node*,string);
	node* inOrderSucc(node*);
	node* findNode(node* r,string w);
	void inOrder(node* );
	void preOrder(node* );
	int printGivenLevel(node* root, int level);
	int height(node *);
	int balanceFactor(node *);
	float printLevelOrder(node* root);
	public:
		dictionary()
		{
			root = NULL;
			counter=0;
		}
		void input(string, string );
		void DeleteNode(string);
		void update(node* r,string w);
		int search(node *, string);
		void ascending();
		void descending(node * root);
		float findAverage(node* r);
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

void dictionary :: DeleteNode(string val)
{
	root = Delete(root,val);
}

node* dictionary :: Delete(node* r, string w)
{
	if(r==NULL)
		return r;
	if(w > r -> word)
		r -> right = Delete(r -> right, w);
	else if(w < r -> word)
		r -> left = Delete(r -> left, w);
	else
	{
		if(r -> left == NULL || r -> right == NULL)
		{
			node * temp = new node;
			if(r -> left == NULL)
				temp = r -> right;
			else if(r -> right == NULL)
				temp = r ->left;

			if(temp==NULL)
			{
					temp = r;
					r = NULL;
					delete temp;
			}
			else
			{
				r ->left = temp -> left;
				r ->right = temp -> right;
				r -> word = temp -> word;
				r -> mean = temp -> word;
				delete temp;
			}
		}
		else
		{
			node *temp = inOrderSucc(r -> right);
			swap(r -> word,temp -> word);
			swap(r -> mean,temp -> mean);
			r -> right = Delete(r -> right, temp -> word);
		}
	}
	if(r == NULL)
		return r;
		
	int bf = balanceFactor(r);

	if((bf==2))
	{
		if(balanceFactor(r-> left) >=0)
		{
			cout << "RIGHT ROTATION AT " << r -> word << endl ; 
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
		if(balanceFactor(r-> right) <=0)
		{
			cout << "LEFT ROTATION AT " << r -> word << endl ;
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

int dictionary :: search(node* r , string w)
{
	int c=0;
	while(r != NULL)
	{
		c++;
		if(r->word == w)
		{
			cout<<"Maximum comparisons are: "<<c<<endl;
			return 1;
		}
		if(w < r->word)
		{
			r=r->left;
		}
		if(w > r->word)
		{
			r=r->right;
		}
	}
	return -1;
}

void dictionary :: ascending()
{
	if(root == NULL){
		cout << "EMPTY TREE " << endl;
		return;
	}
	inOrder(root);
	cout << endl;
}

void dictionary :: inOrder(node * ptr)
{
	if(ptr==NULL)
		return ;
	inOrder(ptr -> left);
	cout << "WORD : " << ptr -> word << " MEANING: " << ptr -> mean << endl;
	inOrder(ptr -> right);
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

float dictionary ::findAverage(node* r)
{
	float temp=printLevelOrder(r);
	return float(temp/counter);
}

float dictionary ::printLevelOrder(node* root)
{
	counter=0;
	int h = height(root);
	int i;
	float temp=0;
	for (i = 1; i <= h; i++)
	{
		int temp1 = printGivenLevel(root, i);
		temp+=i*temp1;
	}
	return temp;
}

int dictionary :: height(node *ptr)
{
	if(ptr==NULL)
		return 0;
	return max(height(ptr->left) ,height(ptr->right)) + 1;
}

int dictionary ::printGivenLevel(node* root, int level)
{
	int temp=0,temp1=0;
	if (root == NULL)
		return 0;
	if (level == 1)
	{
		counter++;
		return 1;
	}
	else if (level > 1)
	{
		temp=printGivenLevel(root->left, level-1);
		temp1=printGivenLevel(root->right, level-1);
	}
	return temp+temp1;
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
		cout << "2. Delete a record " << endl;
		cout << "3. Update a record" << endl;
		cout << "4. Search a record" << endl;
		cout << "5. Ascending Order" << endl;
		cout << "6. Descending Order" << endl;
		cout << "7. Avg Comparisons" << endl;
        	cin >> in;
		switch(in)
		{
			case 1:
				cout << "Enter word and meaning repectively: ";
				 cin >> a >>b;
                		t.input(a,b);
                		break;
			case 2:
				cout << "Enter the word to be deleted : ";
				cin >> a;
				t.DeleteNode(a);
                		break;
			case 3:
				cout<<"Enter keyword to update its meaning: ";
				cin>>a;
				t.update(t.getRoot(),a);
				break;
			case 4:
				cout << "Enter the word to be searched : ";
				cin >> a;
				if(t.search(t.getRoot(),a) == -1)
					cout<<"Keyword not found"<<endl;
				else
					cout<<"Keyword Found"<<endl;
				break;
			case 5:
				t.ascending();
				break;
			case 6:
				t.descending(t.getRoot());
				break;
			case 7:
				cout<<"cost is: "<<t.findAverage(t.getRoot())<<endl;
				break;
            		default:
                		cout << "End" << endl;
        	}
	}while(in!=8);
}
