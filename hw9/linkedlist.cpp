// Names: Christine Goh, Ira Narang, Rhea Samuel
// UTEIDs: cxg96, in2933, rss3488
// TACC Usernames: christinegoh, iranarang, rheasamuel12
#include "linkedlist.hpp"

int main() {
  List mylist;
  int inputValue; //value to be added

  cout << "Enter a sequence of numbers (0 to stop):" << endl;
  while (true) {
    cin >> inputValue;

    if (inputValue == 0) { //marks end of list
      break;
    }
    //inserts and prints values in list
    mylist.insert(inputValue);
    mylist.print();
  }

  return 0;
}

int List::length() {
  int count = 0;
  if (head==nullptr) //if the lsit is empty
    return 0;
  else
    return head->length(); //returns length of list
};

int Node::length() {
  if (!has_next()) //if list does not have next value
    return 1;
  else
    return 1+next->length();  //returns length of list if there are more values
};

/*
 * Iterative alternative
 * to recursive computation
 */
int List::length_iterative() {
  int count = 0;
  if (head!=nullptr) {  
    auto current_node = head;
    while (current_node->has_next()) { //loops through list
      current_node = current_node->nextnode(); count += 1;
    }
  }
  return count;
}; 

void Node::print() {
  cout << datavalue; //prints value in list
  if (next != nullptr) { //if there is still values
    cout << ", ";
    next->print(); //calls to print again
  }
}

void List::print() {
  cout << "List: ";
  if (head != nullptr) { //not empty
    head->print(); //calls to print
  }
  cout << '\n';
}

void List::insert(int value) {
  if (head == nullptr || value < head->value()) { //empty list or value is less than head value
    head = make_shared<Node>(value, head); //makes the value the new head
  } else {
    head->insert(value); //inserts value
  }
}

void Node::insert(int value) {
  if (next == nullptr || value < next->value()) { //empty list or value is less than head value
    shared_ptr<Node> new_node = make_shared<Node>(value, next); //makes the value the new head
    next = new_node;
  } else {
    next->insert(value); //inserts the value
  }
}
