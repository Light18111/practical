/*
----------Assignment No - 7----------
There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight takes to reach city B from A, or the amount of fuel used for the journey. Represent this as a graph. The node can be represented by airport name or name of the city. Use adjacency list representation of the graph or use adjacency matrix representation of the graph. Justify the storage representation used*/

#include<iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;
const int MAX=30;
class node
{
	node *next;
	string city;
	int timeCost;
	public:
		friend class graph;
		node()
		{
			next=NULL;
			city="";
			timeCost=-1;
		}
		node(string city, int weight)
		{
			next=NULL;
			this->city=city;
			timeCost=weight;
		}
};

class graph
{
	node *head[MAX];
	int n;
	public:
		graph(int num)
		{
			n=num;
			for(int i=0;i<n;i++)
				head[i]=NULL;
		}
		void insert(string city1, string city2, int time);
		void readdata();
		int getindex(string s1);
		void display();
};

int graph::getindex(string s1)
{
	for(int i=0;i<n;i++)
	{
		if(head[i]->city==s1)
			return i;
	}
	return -1;
}

void graph::insert(string city1, string city2, int time)
{
	node * source;
	node *dest=new node(city2, time);
	int ind=getindex(city1);
	source=head[ind];
	while(source->next!=NULL)
		source=source->next;
	source->next=dest;
}

void graph::display()
{
	node* source;
	for(int i=0;i<n;i++)
	{
		source=head[i];
		while(source!=NULL)
		{
			cout<<source->city<<"->";
			source=source->next;
		}
		cout<<"NULL"<<endl;
	}
}

void graph::readdata()
{
	string city1, city2, tmpcity;
	int fcost,flight;
	cout<<"\nEnter City Details:\n";
	for(int i=0;i<n;i++)
	{
		head[i]=new node;
		cout<<"Enter name of city "<<i+1<<" ";
		cin>>head[i]->city;
	}
	cout<<"\nEnter Number of Flights to insert: ";
	cin>>flight;
	for(int i=0;i<flight;i++)
	{
		cout<<"\nEnter Source:";
		cin>>city1;
		cout<<"Enter Destination:";
		cin>>city2;
		cout<<"Enter Time:";
		cin>>fcost;
		insert(city1,city2,fcost);
	}
}

int main()
{
	int number, choice;
	cout<<"\nEnter Number of Airport Stations:";
	cin>>number;
	graph g1(number);
	do
	{
		cout<<"------Menu------";
		cout<<"\n1.Insert Flight detail";
		cout<<"\n2.Display";
		cout<<"\n3.Exit";
		cout<<"\nEnter your choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:
				g1.readdata();
				break;
			case 2:
				cout<<"**Adjacency List**"<<endl;
				g1.display();
				break;
			default:
				cout<<"\nWrong Choice";
		}
	}while(choice!=3);
	return 0;
}
