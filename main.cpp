// #ifdef MAIN

// #include "ABDQ.hpp"
// #include "ABQ.hpp"
// #include "ABS.hpp"
// #include "Interfaces.hpp"
// #include "LLDQ.hpp"
// #include "LLQ.hpp"
// #include "LLS.hpp"
#include "LinkedList.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH
   GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration
   in CLion, or through your own command line compilation. Make sure to add flag
   "-DMAIN" to your compilation so this main function can compile.

*/

int main() {
  LinkedList<int> ll;
  ll.addHead(1);
  ll.addHead(2);
  ll.addHead(3);
  ll.addTail(4);
  std::cout << ll.getTail()->data;
  ll.removeTail();
  std::cout << ll.getHead()->data;
  ll.removeHead();
  std::cout << ll.getHead()->data;
  ll.removeHead();
  std::cout << ll.getHead()->data;
  ll.removeHead();

  return 0;
}

// #endif