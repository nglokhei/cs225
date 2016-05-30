#include <iostream>
#include <string>

using namespace std;

/*************************************************************************
* This is the list class which is used for organizing 
* the list of student names.
* This is a singly linked list.
* 
* ListNode class is the structure of ever node in 
* the linked list. 
*
* next is the pointer to the next node of the list
* name is the name of every student
* netid is the unique netid of every student
*
**************************************************************************/

class List
{
	private:
	class ListNode
	{
		public:

		//Constructs list node with given data
		ListNode(std::string a_name);
		
		ListNode* next;
		std::string m_sName;
	};

	ListNode* head;
	ListNode* tail;
	int length;

	public:

	// Default constructor 
	// Empty List with head pointing to NULL
	List();

	//Returns length
	int getLength();

	//Print list
	void print();

	// Inserts a new node at the back of the list. 
	void insertBack(std::string a_name);

	// Reorganizes the list of student names according
	// to given pattern in question
	void reorganizeList();
};

//Constructor for list node
List::ListNode::ListNode(std::string a_name)
{
	m_sName = a_name;
	next = NULL;
}

//Default constructor for list
List::List()
{
	length = 0;
	head = NULL;
	tail = NULL;
}

//Return length
int List::getLength()
{
	return length;
}

//Insert Back
void List::insertBack(std::string a_name)
{
	ListNode * temp = new ListNode(a_name);
	if(head == NULL)
	{
		head = temp;
		tail = temp;
	}
	
	else
	{
		tail->next = temp;
		tail = tail->next;
	}

	length ++;
}

//Reorganize the list
//Example : a -> b -> c -> d -> e -> f -> NULL becomes
// a -> c -> e -> b -> d -> f -> NULL
void List::reorganizeList()
{
    //TODO Your code here
    if (list.size() == 0){
	return;
    else{
	ListNode* tmp = head -> next;
	ListNode* prev = head;
	for (int i = 0; i < getLength() / 2; i++){
	    // move the even number nodes to the back
	    if (tmp != NULL && tmp != tail){
		prev -> next = tmp -> next;
		tail -> next = tmp;
		tmp -> next = NULL;
		tail = tmp;

		// update the ptrs
		if (prev -> next != NULL)
		    prev = prev -> next;
		if (prev -> next != NULL){
		    tmp = prev -> next;
	    }
	}
	
}

//Use this function to display the list
void List::print()
{
	cout<<"----------------Printing List----------"<<endl; 
	ListNode * curr = head;

	while(curr != tail)
	{
		cout<<curr->m_sName<<" -> ";
		curr = curr->next;
	}
	
	cout<<curr->m_sName<<endl;
	cout<<"--------------------------------------"<<endl;
}

int main()
{
	List studentNames;
	studentNames.insertBack("a");
	studentNames.insertBack("b");
	studentNames.insertBack("c");
	studentNames.insertBack("d");

	studentNames.print();

	studentNames.reorganizeList();

    //Expected output
    //a -> c -> b -> d
    
	studentNames.print();
}

