/*
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
using namespace std;

template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1

    while (head != tail){
	head = head -> next;
	delete head -> prev;
	head -> prev = NULL;
    }

    delete head;
    head = NULL;
    tail = NULL;
    length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* p = new ListNode(ndata);
    length ++;
    if (head == NULL && tail == NULL){
	tail = p;
    }
    else {
        head -> prev = p;
        p -> next = head;
    }
    head = p;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode *p = new ListNode(ndata);
    length ++;
    if (head == NULL && tail == NULL){
	head = p;
    }
    else {
	tail -> next = p;
        p -> prev = tail;
    }
    tail = p;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
    if (startPoint == endPoint || endPoint == NULL || startPoint == NULL)
	return;

    ListNode* before = endPoint -> next;
    ListNode* after = startPoint -> prev;

    if (before != NULL)
	before -> prev = startPoint;
    if (after != NULL)
	after -> next = endPoint;
    
    ListNode* t1 = startPoint;
    ListNode* t2 = startPoint -> next;

    startPoint -> next = before;
    endPoint -> prev = after;

    while (t1 != endPoint){
	t1 -> prev = t2;
	t2 = t2-> next;
	(t1 -> prev) -> next = t1;
	t1 = t1 -> prev;
    }
    endPoint = startPoint;
    startPoint = t1;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    if (head == NULL || tail == NULL || head == tail)
	return;
    
    int times = length / n;
    
    if (times == 0){
	reverse(head,tail);
	return;
    }

    // reverse the first block
    ListNode* st;
    ListNode* en = head;
	
    for (int i = 0; i < n - 1; i++){
        en = en -> next;
    }

    reverse(head, en);
	
    st = en -> next;
    for (int t = 1; t < times; t++){
         // fix en
        for (int i = 0; i < n; i++){
            en = en -> next;
        }
	
	reverse(st,en);
	
	st = en -> next;
    }

    // fix the end
    if ( length % n == 0){
	tail = en;
    }
    else {
	reverse(st,tail);
    }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if (length < 3){
	return;
    }

    ListNode* prevNode = head;
    ListNode* presNode = prevNode -> next;
    ListNode* nextNode = presNode -> next;
    while (presNode != NULL && prevNode != NULL && nextNode != NULL){
	
	prevNode -> next = nextNode;
	nextNode -> prev = prevNode;
	
	presNode -> next = NULL;
	presNode -> prev = NULL;
	
	presNode -> prev = tail;
	tail -> next = presNode;
	tail = presNode;
	
	// update the variables
	prevNode = nextNode;
	presNode = prevNode -> next;
	nextNode = presNode -> next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if (splitPoint == length)
	return NULL;
    if (splitPoint == 0)
	return start;
    ListNode* secondhead = start;
    
    for (int i = 0; i < splitPoint; i++){
	secondhead = secondhead -> next;
    }
 
    (secondhead -> prev) -> next = NULL;
    secondhead -> prev = NULL; 
    return secondhead; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    if (first == NULL)
	return second;
    if (second == NULL)
	return first;

    ListNode* seqHead;
    // determine the head
    // set first to be the sequence with seqHead, second to be the other sequence
    if (first -> data < second -> data){
	seqHead = first;
    }
    else{
	seqHead = second;
	second = first;
	first = seqHead;
    }
    ListNode* tmp = first;
    // merge the list
    while (first != NULL ){
	if (first -> data < second -> data || first -> data == second -> data){
	    tmp = first;
	    first = first -> next;
	    
 	}
	else{
	    first -> prev = NULL;
	    tmp -> next = second;
	    second -> prev = tmp;

	    // update
	    second = first;
	    tmp = tmp -> next;
	    first = tmp -> next;
	}
    }
    
    // fix the end
    tmp -> next = second;
    second -> prev = tmp;

    return seqHead; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if (chainLength <= 1)
	return start;

    ListNode* head2;
    head2 = split(start, chainLength / 2);

    head2 = mergesort(head2, chainLength - chainLength / 2);

    ListNode * head1;
    head1 = mergesort(start, chainLength / 2);
 
    head1 = merge(head1, head2);
    
    return head1; // change me!
}
