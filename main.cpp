#include "bank.h"

int main(){
    Bank a("data.txt");
    a.showAvailable();
    a.showMax();
    a.showAlloc();
    a.showNeed();
    std::cout << "\nSafe Sequence:\n" << a.getSafeSequence() << "----PROGRAM TERMINATED----\n";
}


/*  OUTPUT

--Available--
3 3 2 
--MAX--
7 5 3 
3 2 2 
9 0 2 
2 2 2 
4 3 3 
--ALLOCATION--
0 1 0 
2 0 0 
3 0 2 
2 1 1 
0 0 2 
--NEED--
7 4 3 
1 2 2 
6 0 0 
0 1 1 
4 3 1 

Safe Sequence:
Process 1 has been allocated
	Current Work: 5 3 2 
Process 3 has been allocated
	Current Work: 7 4 3 
Process 4 has been allocated
	Current Work: 7 4 5 
Process 0 has been allocated
	Current Work: 7 5 5 
Process 2 has been allocated
	Current Work: 10 5 7 
----PROGRAM TERMINATED----
*/