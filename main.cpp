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

void test_abs() {
  std::cerr << "ABS test:\n";

  ABS<int> hi;
  assert(hi.getSize() == 0);
  assert(hi.getMaxCapacity() == 1);
  hi.push(7);
  hi.push(8);
  assert(hi.getSize() == 2);
  assert(hi.peek() == 8);
  assert(hi.pop() == 7);
  assert(hi.getSize() == 1);
  assert(hi.getMaxCapacity() == 2);

  ABS<int> hi2 = ABS(hi);
  for (size_t i = 0; i < hi.getSize(); i++) {
    assert(hi.pop() == hi2.pop());
  }

  std::cerr << "ABS success\n";
}

int main() {
  test_abs();

  // std::cout << "ll:\n";

  // {
  //   LinkedList<int> ll;

  //   assert(ll.getTail() == nullptr);

  //   ll.addHead(1);
  //   ll.removeTail();

  //   assert(ll.getHead() == nullptr);
  //   assert(ll.removeHead() == false);
  //   assert(ll.removeTail() == false);

  //   ll.addTail(1);
  //   assert(ll.getTail()->data == 1);
  //   assert(ll.getHead()->data == 1);
  //   ll.addTail(2);
  //   ll.removeHead();
  //   assert(ll.getTail()->data == 2);
  //   assert(ll.getHead()->data == 2);

  //   LinkedList<int> ll2(ll);
  //   assert(ll2.getTail()->data == 2);

  //   LinkedList<int> ll3(std::move(ll));
  //   assert(ll3.getTail()->data == 2);
  // }

  // std::cout << "ABDQ:\n";

  // {
  //   ABDQ<int> hi;

  //   hi.pushFront(2);
  //   assert(hi.popFront() == 2);

  //   try {
  //     hi.popFront();
  //     return 1;
  //   } catch (...) {
  //   }

  //   try {
  //     hi.popBack();
  //     return 1;
  //   } catch (...) {
  //   }

  //   try {
  //     hi.front();
  //     return 1;
  //   } catch (...) {
  //   }

  //   try {
  //     hi.back();
  //     return 1;
  //   } catch (...) {
  //   }

  //   hi.pushFront(2);

  //   assert(hi.popBack() == 2);

  //   hi.pushFront(1);
  //   assert(hi.front() == 1);
  //   assert(hi.back() == 1);
  //   hi.pushBack(2);
  //   assert(hi.back() == 2);
  //   assert(hi.front() == 1);

  //   hi.pushFront(2);
  //   assert(hi.front() == 2);
  //   assert(hi.back() == 2);

  //   hi.popBack();
  //   hi.popBack();
  //   hi.popBack();
  // }

  std::cout << "Success!\n";
  return 0;
}

// #endif