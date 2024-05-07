/*
----------Assignment 13----------
Company maintains employee information as employee ID, name, designation and salary.
Allow user to add, delete information of employee. Display information of particular
employee. If employee does not exist an appropriate message is displayed. If it is, then
the system displays the employee details. Use index sequential file to maintain the data.
*/

#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

class EMP_CLASS
{
	typedef struct EMPLOYEE
	{
		char name[10];
		char desig[20];
		int emp_id;
		int salary;
	}Rec;
	typedef struct INDEX
	{
		int emp_id;
 		int position;
 	}Ind_Rec;
 	Rec Records;
 	Ind_Rec Ind_Records;
 	public:
  		EMP_CLASS();
  		void Create();
  		void Display();
  		void Delete();
  		void Search();
};

EMP_CLASS::EMP_CLASS()
{
	strcpy(Records.name,"");
	strcpy(Records.desig,"");
}

void EMP_CLASS::Create()
{
	int i,j;
	char ch='y';
	fstream seqfile;
 	fstream indexfile;
 	i=0;
 	indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
 	seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
 	do
 	{
  		cout<<"\n Enter Name: ";
  		cin>>Records.name;
  		cout<<"\n Enter Emp_ID: ";
  		cin>>Records.emp_id;
		cout<<"\n Enter Designation: ";
  		cin>>Records.desig;
  		cout<<"\n Enter Salary: ";
  		cin>>Records.salary;
  		seqfile.write((char*)&Records,sizeof(Records))<<flush;
  		Ind_Records.emp_id=Records.emp_id;
  		Ind_Records.position=i;
  		indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
  		i++;
  		cout<<"\nDo you want to add more records?";
  		cin>>ch;
  	}while(ch=='y');
  	seqfile.close();
  	indexfile.close();
}

void EMP_CLASS::Display()
{
	fstream seqfile;
 	fstream indexfile;
 	int n,i,j;
 	seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
 	indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
 	indexfile.seekg(0,ios::beg);
 	seqfile.seekg(0,ios::beg);
 	cout<<"\n The Contents of file are ..."<<endl;
 	i=0;
 	while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
 	{
		i=Ind_Records.position*sizeof(Rec);//getting pos from index file
   		seqfile.seekg(i,ios::beg);//seeking record of that pos from seq.file
   		seqfile.read((char *)&Records,sizeof(Records));//reading record
		if(Records.emp_id!=-1)//if rec. is not deleted logically then display it
   		{   
   			cout<<"\nName: "<<Records.name<<flush;
   			cout<<"\nEmp_ID: "<<Records.emp_id;
			cout<<"\nDesignation: "<<Records.desig;
   			cout<<"\nSalary: "<<Records.salary;
   			cout<<"\n";
    		}
	}
 	seqfile.close();
 	indexfile.close();
}

void EMP_CLASS::Delete()
{
	int id,pos;
 	cout<<"\n For deletion,";
 	cout<<"\n Enter the Emp_ID for for searching ";
 	cin>>id;
 	fstream seqfile;
 	fstream indexfile;
 	seqfile.open("EMP.txt",ios::in|ios::out|ios::binary);
 	indexfile.open("IND.txt",ios::in|ios::out|ios::binary);
 	seqfile.seekg(0,ios::beg);
 	indexfile.seekg(0,ios::beg);
 	pos=-1;
 	//reading index file for getting the index
 	while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
 	{
  		if(id==Ind_Records.emp_id) //desired record is found
  		{
   			pos=Ind_Records.position;
   			Ind_Records.emp_id=-1;
   			break;
  		}
 	}
 	if(pos==-1)
 	{
  		cout<<"\n The record is not present in the file";
  		return;
 	}
	//calculating the position of record in seq. file using the pos of ind. file
 	int offset=pos*sizeof(Rec);
 	seqfile.seekp(offset);//seeking the desired record for deletion
 	strcpy(Records.name,"");
	strcpy(Records.desig,"");
 	Records.emp_id=-1; //logical deletion
 	Records.salary=-1; //logical deletion
 	seqfile.write((char*)&Records,sizeof(Records))<<flush;//writing deleted status 
    	//From index file also the desired record gets deleted as follows
	offset=pos*sizeof(Ind_Rec);//getting position in index file
 	indexfile.seekp(offset); //seeking that record
 	Ind_Records.emp_id=-1; //logical deletion of emp_id
 	Ind_Records.position=pos;//position remain unchanged
 	indexfile.write((char*)&Ind_Records,sizeof(Ind_Records))<<flush;
 	seqfile.seekg(0);
 	indexfile.close();
 	seqfile.close();
 	cout<<"\n The record is Deleted!!!";
}

void EMP_CLASS::Search()
{
	fstream seqfile;
 	fstream indexfile;
 	int id,pos,offset;
 	cout<<"\n Enter the Emp_ID for searching the record ";
 	cin>>id;
 	indexfile.open("IND.txt",ios::in|ios::binary);
 	pos=-1;
 	//reading index file to obtain the index of desired record
 	while(indexfile.read((char *)&Ind_Records,sizeof(Ind_Records)))
 	{
  		if(id==Ind_Records.emp_id)//desired record found
  		{
   			pos=Ind_Records.position;//seeking the position
   			break;
  		}
 	}
  	if(pos==-1)
  	{
  		cout<<"\n Record is not present in the file";
  		return;
  	}
	//calculate offset using position obtained from ind. file
  	offset=pos*sizeof(Records);
  	seqfile.open("EMP.txt",ios::in|ios::binary);
	//seeking the record from seq. file using calculated offset
  	seqfile.seekg(offset,ios::beg);//seeking for reading purpose
  	seqfile.read((char *)&Records,sizeof(Records));
  	if(Records.emp_id==-1)
  	{
  		cout<<"\n Record is not present in the file";
  		return;
  	}
  	else //emp_id=desired record’s id
  	{
  		cout<<"\n The Record is present in the file and it is...";
  		cout<<"\n Name: "<<Records.name;
  		cout<<"\n Emp_ID: "<<Records.emp_id;
		cout<<"\n Name: "<<Records.desig;
  		cout<<"\n Salary: "<<Records.salary;
  	}
  	seqfile.close();
  	indexfile.close();
}

int main()
{
	EMP_CLASS List;
	char ans='y';
 	int choice,key;
 	do
 	{
  		cout<<"\n-----Main Menu-----"<<endl;
  		cout<<"\n 1.Create";
  		cout<<"\n 2.Display";
  		cout<<"\n 3.Delete";
		cout<<"\n 4.Search";
  		cout<<"\n 5.Exit";
  		cout<<"\n Enter your choice: ";
  		cin>>choice;
  		switch(choice)
  		{
  			case 1:
				List.Create();
      				break;
  			case 2:
				List.Display();
      				break;
    			case 3:
				List.Delete();
      				break;
    			case 4:
				List.Search();
      				break;
  			case 5:
				exit(0);
  		}
 	}while(choice!=6);
	return 0;
}
