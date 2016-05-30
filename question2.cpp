#include <iostream>
#include <string>
using namespace std;

class ListNode{
public:
  string word;
  ListNode * next;

  ListNode(string value){
    word = value;
    next = NULL;
  }
};

//You can check the size of a string using [string].size()
//Threshold will always be a number greater than or equal to zero
int removeLongWords(ListNode * &head, int threshold){
  //Your code goes here
  //You may add helper methods if needed

  if (head == NULL)
    return 0;

  string s = head -> word;

  int count = 0;
  if (s.size() > threshold){
    count++;
    head = head -> next;
  }
  if (head != NULL)
    count += removeLongWords(head -> next, threshold);  

  return count;
}

int main(){
  //Example driver class for testing
  //You may add code here as you wish
  //This code will not be evaluated
  //This code does not test all possible test cases   
  
  ListNode elem1 = ListNode("Apple");
  ListNode elem2 = ListNode("Pear");
  ListNode elem3 = ListNode("Plum");
  ListNode elem4 = ListNode("Grape");
  elem1.next = &elem2;
  elem2.next = &elem3;
  elem3.next = &elem4;
  
  ListNode * head = &elem1;

  cout << removeLongWords(head, 4) << endl;
  return 0;
}
