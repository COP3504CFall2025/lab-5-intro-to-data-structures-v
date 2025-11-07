#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
// #include "Interfaces.hpp"
#include "LinkedList.hpp"
// #include "LLDQ.hpp"
// #include "LLQ.hpp"
// #include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {

    // LinkedList<int> l;
    // l.addTail(5);
    // l.removeTail();
    // l.printForward();
    // cout << l.getTail()->data << endl;

    // ABS<int> stack;
    // stack.push(5);
    // stack.push(10);
    // stack.pop();
    // stack.push(5);
    // stack.push(10);
    // ABS<int> stack2 = stack;
    // // cout << stack2.getSize() << endl;
    // // cout << stack.peek() << endl;

    // ABQ<int> queue;
    // queue.enqueue(1);
    // queue.enqueue(2);
    // queue.enqueue(3);
    // int* data = queue.getData();
    // for (size_t i = 0; i < queue.getSize(); i++) {
    //     cout << data[i] << " ";
    // }
    // cout << endl;

    ABDQ<int> dq;
    dq.pushFront(10);
    dq.pushFront(5);
    dq.pushFront(20);
    dq.print();
    dq.pushFront(30);
    dq.pushFront(40);
    dq.print();
    dq.pushBack(50);
    dq.pushBack(60);
    dq.pushBack(70);
    dq.pushBack(80);
    dq.print();

    return 0;
}


#endif