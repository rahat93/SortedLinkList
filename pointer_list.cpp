#include<iostream>
using namespace std;
struct link {
	int value;
	link * next;
	link() { value = 0; next = 0; }
	link(int _value) { value = _value; next = 0; }
};
void printList(link *);
int main() {
	link * eventop = 0;
	link * oddtop = 0;
	link * mergetop = 0;
	link * mergebottom;
	link * previous = 0;
	link * current = 0;
	link * lptr = 0;
	int invalue;
	cout << "Input an integer, enter 0 to terminate: " << flush;
	cin >> invalue;
	while (invalue != 0) {
		if (invalue % 2) { // checking if odd
			if (oddtop == 0) { // checking if first element
				oddtop = new link(invalue);
			}
			else {
				lptr = oddtop;
				while ((lptr->value < invalue) && (lptr->next != 0)) { // searching for place to insert
					if (lptr->next->value > invalue) // checking if step excess
						break;
					lptr = lptr->next;
				}
				if (lptr->value > invalue && lptr == oddtop) // checking if we have to insert to list top
				{
					oddtop = new link(invalue);
					oddtop->next = lptr;
				}
				else {
					current = lptr->next;
					lptr->next = new link(invalue);
					lptr->next->next = current;
				}
			}
		}
		else {
			if (eventop == 0) { // checking if first element
				eventop = new link(invalue);
			}
			else {
				lptr = eventop;
				while ((lptr->value < invalue) && (lptr->next != 0)) { // searching for place to insert
					if (lptr->next->value > invalue) // checking if step excess
						break; 
					lptr = lptr->next;
				}
				if (lptr->value > invalue && lptr == eventop) // checking if we have to insert to list top
				{
					eventop = new link(invalue);
					eventop->next = lptr;
				}
				else {
					current = lptr->next;
					lptr->next = new link(invalue);
					lptr->next->next = current;
				}
			}
		}
		cout << "Input an integer, enter 0 to terminate: " << flush;
		cin >> invalue;
	}

	printList(oddtop);
	cout << "\n\n";
	printList(eventop);
	cout << "\n\n";
	mergetop = mergebottom = 0;

	current = eventop; // pointer to start of even list
	lptr = oddtop; // pointer to start of odd list
	while (mergebottom == 0) { 
		if (current != 0 && lptr != 0) { // check if we can use both lists
			if (current->value < lptr->value) { // choosing of smallest link value
				if (previous != 0) // if it first part of merge list
					previous->next = current;
				previous = current;
				current = current->next;
			}
			else {
				if (previous != 0) // if it first part of merge list
					previous->next = lptr;
				previous = lptr;
				lptr = lptr->next;
			}
		}
		else
			if (current == 0) { // if we can't use odd list
				if (previous != 0) // if it first part of merge list
					previous->next = lptr;
				previous = lptr;
				lptr = lptr->next;
			}
			else 
				if (lptr == 0) { // if we can't use even list
					if (previous != 0) // if it first part of merge list
						previous->next = current;
					previous = current;
					current = current->next;
				}
		if (mergetop == 0) // if it first part of merge list
		{
			mergetop = previous;
		}
		if (current == 0 && lptr == 0) // if it last part of merge list
			mergebottom = previous;
	}
	printList(mergetop);
	while (mergetop) {
		lptr = mergetop;
		mergetop = mergetop->next;
		delete lptr;
	}
	return 0;
}
void printList(link * list) {
	if (list == 0) // if list is empty
		return;
	cout << list->value << " ";
	while (list->next != 0) {
		list = list->next;
		cout << list->value << " ";
	}
	cout << endl;
}