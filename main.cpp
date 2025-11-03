// #ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include "LinkedList.hpp"
#include <cassert>
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH
   GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration
   in CLion, or through your own command line compilation. Make sure to add flag
   "-DMAIN" to your compilation so this main function can compile.

*/

int main() {
  {
    LinkedList<int> ll;

    try {
      ll.removeHead();
      return -1;
    } catch (...) {
    }

    try {
      ll.removeTail();
      return -1;
    } catch (...) {
    }

    ll.addTail(1);
    assert(ll.getTail()->data == 1);
    assert(ll.getHead()->data == 1);
    ll.addTail(2);
    ll.removeHead();
    assert(ll.getTail()->data == 2);
    assert(ll.getHead()->data == 2);

    LinkedList<int> ll2(ll);
    assert(ll2.getTail()->data == 2);

    LinkedList<int> ll3(std::move(ll));
    assert(ll3.getTail()->data == 2);
  }

  {
    ABDQ<int> hi;
    hi.pushFront(1);
    assert(hi.front() == 1);
    assert(hi.back() == 1);
    hi.pushBack(2);
    assert(hi.back() == 2);

    hi.popFront();
    assert(hi.front() == 1);
    assert(hi.back() == 1);
  }

  //   ABDQ<int> hi;

  //   try {
  //     hi.front();
  //     return 1;
  //   } catch (...) {
  //   }

  //   std::cout << "si: " << hi.getSize() << "\n";

  //   hi.pushFront(10);
  //   std::cout << "si: " << hi.getSize() << "\n";
  //   std::cout << "fr: " << hi.front() << "\n";

  return 0;
}

// #endif