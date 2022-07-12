#define DBG_PRINTF(_str_, ...) //printf(_str_,__VA_ARGS__)
#include <stdlib.h> // for NULL
#include <stdio.h> // for printf

// exclusive access to list
// head points to first element
// that element points to the next
// so to maniplate you need a work element
// walk the list to get to the end marked by a null in its next pointer
// as walking thru the list maintain your current pointer and previous
// current is pointing to the end object, previous is pointing to the next to end
// next to end ptr get nulled
// end ptr get set to head->
// head get set to end ptr
// walk the list until we reach the "previous ptr"
// head->next-> = previous (C)
// A -> B -> C -> D - > NULL
// D -> A -> B -> C -> NULL
// D -> C -> A -> B -> NULL
// D -> C -> B -> A

struct Payload
{
    char        value;
};

struct Element
{
	Element*	next;
	Payload		payload;
};

struct SingleLinkedList
{
	Element*	start;
	int         numOfElements;
};

void PrintSingleLinkList( SingleLinkedList* apList)
{
    if( NULL != apList )
    {
        Element*    p_ = apList->start;
        for( int i_ = 0; i_ < apList->numOfElements; i_++ )
        {
            printf("%d = %c\n", i_, p_->payload.value);
            if( NULL == p_->next )
            {
                break;
            }
            else
            {
                p_ = p_->next;
            }
        }
        printf("\n");
    }
}

bool ReverseSingleLinkedList( SingleLinkedList * apList)
{
    bool        ret_ = true;
	Element* 	previous;
	Element* 	current;
	Element*	insertionElement = NULL; // If null, insert at start of list
	int         num_ = apList->numOfElements - 1; // iterate over all elements but 1
	int			runAwayCatch; // assuming int is larget enough
	if( apList->start != NULL )
	{
		while( num_-- && ret_ )
		{
		    if( NULL == insertionElement )
		    {
		        current = apList->start;
		    }
		    else
		    {
			    current = insertionElement;
		    }
		    
		    runAwayCatch = 0;
			while( current->next != NULL )
			{
				previous = current;
				current = current->next; // move to next element
				if( ++runAwayCatch > apList->numOfElements )
				{
				    ret_ = false;
				    break;
				}
			}
			
			if( ret_ )
			{
    			if( NULL == insertionElement )
    			{
    			    current->next = apList->start;  // element from end now points to previous starting point
    				apList->start = current;        // starting point now points to the item removed from the end
    				insertionElement = current;     // set the insertion point to the newly inserted item
    			}
    			else
    			{
    				current->next = insertionElement->next; // element from end now points to next item after the insertionElement
    				insertionElement->next = current; // insertion target is updated to point to moved item
    				insertionElement = insertionElement->next; // update the insertion pointer
    			}
    		    previous->next = NULL;
    			DBG_PRINTF("current=%c\n", current->payload.value);
    			DBG_PRINTF("previous=%c\n", previous->payload.value);
    			DBG_PRINTF("insertionElement=%c\n", insertionElement->payload.value);
			}
		}
	}
	return( ret_ );
}

#define NUM_ELEMENTS 26
Element elm[NUM_ELEMENTS];
SingleLinkedList sll;

void PopulateSingleLinkedList( SingleLinkedList* aList)
{
    char val_ = 'A';
    sll.start = &elm[0];
    sll.numOfElements = NUM_ELEMENTS;
    for( int i_ = 0; i_ < sll.numOfElements - 1; i_++ )
    {
        elm[i_].next = &elm[i_ + 1];
        elm[i_].payload.value = (char)(val_ + i_);
    }
    elm[sll.numOfElements - 1].next = NULL;
    elm[sll.numOfElements - 1].payload.value = (char)(val_ + NUM_ELEMENTS - 1);
}

int main(int argc, char* argv[])
{
    PopulateSingleLinkedList(&sll);
    PrintSingleLinkList(&sll);
    bool ret_ = ReverseSingleLinkedList(&sll);
    if( ret_ )
    {
        PrintSingleLinkList(&sll);
    }
    return(ret_ ? 0 : -1);
}
