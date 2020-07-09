#include <iostream>
using namespace std;
const int ArraySize = 32;
int value[ArraySize] = { 0 };
int Next[ArraySize] = { 0 };
int top = 1;
void initializeArrays();
int NextLocation();
void printlist(int);
void recycle(int);
void dump();
int main() {
	initializeArrays();
	int eventop = 0;
	int oddtop = 0;
	int mergetop = 0;
	int mergebottom = 0;
	int current = 0;
	int previous = 0;
	int lptr = 0;
	int invalue;
	cout << "Input an integer, enter 0 to terminate: " << flush;
	cin >> invalue;
	while (invalue != 0) {
		if (invalue % 2) { // checking if odd
			if (oddtop == 0) { // checking if first element
				oddtop = NextLocation();
				value[oddtop] = invalue;
			}
			else {
				lptr = oddtop;
				while ((value[lptr] < invalue) && (Next[lptr] != 0)) { // searching for place to insert
					if (value[Next[lptr]] > invalue) // checking if step excess
						break;
					lptr = Next[lptr];
				}
				if (value[lptr] > invalue && lptr == oddtop) // checking if we have to insert to list top
				{
					oddtop = NextLocation();
					value[oddtop] = invalue;
					Next[oddtop] = lptr;
				}
				else {
					current = Next[lptr];
					Next[lptr] = NextLocation();
					value[Next[lptr]] = invalue;
					Next[Next[lptr]] = current;
				}
			}
		}
		else {
			if (eventop == 0) { // checking if first element
				eventop = NextLocation();
				value[eventop] = invalue;
			}
			else {
				lptr = eventop;
				while ((value[lptr] < invalue) && (Next[lptr] != 0)) { // searching for place to insert
					if (value[Next[lptr]] > invalue) // checking if step excess
						break;
					lptr = Next[lptr];
				}
				if (value[lptr] > invalue && lptr == eventop) // checking if we have to insert to list top
				{
					eventop = NextLocation();
					value[eventop] = invalue;
					Next[eventop] = lptr;
				}
				else {
					current = Next[lptr];
					Next[lptr] = NextLocation();
					value[Next[lptr]] = invalue;
					Next[Next[lptr]] = current;
				}
			}
		}
		cout << "Input an integer, enter 0 to terminate: " << flush;
		cin >> invalue;
	}
	printlist(oddtop);
	cout << "\n---------\n";
	printlist(eventop);
	cout << "\n---------\n";
	cout << "oddtop = " << oddtop << endl;
	cout << "eventop = " << eventop << endl;
	dump();
	mergetop = mergebottom = 0;

	current = eventop; // pointer to start of even list
	lptr = oddtop; // pointer to start of odd list
	while (mergebottom == 0) {
		if (current != 0 && lptr != 0) { // check if we can use both lists
			if (value[current] < value[lptr]) { // choosing of smallest link value
				if (previous != 0) // if it first part of merge list
					Next[previous] = current;
				previous = current;
				current = Next[current];
			}
			else {
				if (previous != 0) // if it first part of merge list
					Next[previous] = lptr;
				previous = lptr;
				lptr = Next[lptr];
			}
		}
		else
			if (current == 0) { // if we can't use odd list
				if (previous != 0) // if it first part of merge list
					Next[previous] = lptr;
				previous = lptr;
				lptr = Next[lptr];
			}
			else
				if (lptr == 0) { // if we can't use even list
					if (previous != 0) // if it first part of merge list
						Next[previous] = current;
					previous = current;
					current = Next[current];
				}
		if (mergetop == 0) // if it first part of merge list
		{
			mergetop = previous;
		}
		if (current == 0 && lptr == 0) // if it last part of merge list
			mergebottom = previous;
	}
	cout << "\n---------\n";
	printlist(mergetop);
	while (mergetop) {
		lptr = mergetop;
		mergetop = Next[mergetop];
		recycle(lptr);
	}
	cout << "\n---------\n";
	dump();
}
void initializeArrays() {
	for (int i = 1; i < ArraySize; i++) {
		Next[i] = i + 1;
	}
	Next[ArraySize - 1] = 0;
}
int NextLocation() {
	for (int i = 1; i < ArraySize; i++) {
		if (Next[i] == i + 1 && value[i] == 0) {
			Next[i] = 0;
			return i;
		}
	}
	return 0;
}
void printlist(int list) {
	if (list == 0) // if list is empty
		return;
	cout << value[list] << " ";
	while (Next[list] != 0) {
		list = Next[list];
		cout << value[list] << " ";
	}
	cout << endl;
}
void recycle(int  link) {
	Next[link] = link + 1;
	value[link] = 0;
}
void dump() {
	cout << "top = " << top << endl;
	for (int i = 0; i < ArraySize; i++) {
		cout << "[ " << i << " ]" << "value = "
			<< value[i] << " Next = " << Next[i] << endl;
	}
}