

#include "slist.h"
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

slist::slist() {
  head = nullptr;
  tail = nullptr;
  length = 0;
}

slist::slist(slist *s, int i1, int i2) {
  head = s->get(i1);
  for (int i = i1 + 1; i < i2; i++)
    add(s->get(i1)->dat);
  tail = get(i2 - i1 - 1);
}

slist::~slist() {
  Node *current = head;
  Node *next;
  while (current != nullptr) {
    next = current->next;
    delete current;
    current = next;
  }
}

void slist::add(Airport *a) {
  Node *toAdd = new Node;
  toAdd->dat = a;
  toAdd->next = nullptr;
  if (length != 0)
    get(length - 1)->next = toAdd;
  else
    head = toAdd;
  toAdd->next = tail;
  length++;
}

void slist::clear() {
  Node *current = head;
  while (current != nullptr) {
    Node *tmp = current;
    current = current->next;
    delete tmp;
  }
  head = nullptr;
  tail = nullptr;
  length = 0;
}

bool slist::equals(const slist &s) const {
  if (length != s.length)
    return false;
  Node *cThis = head;
  Node *cOther = s.head;
  while (cThis != nullptr) {
    Airport *a = cThis->dat;
    Airport *b = cOther->dat;
    if (!(a->code == b->code && a->longitude == b->longitude &&
          a->latitude == b->latitude))
      return false;
    cThis = cThis->next;
    cOther = cOther->next;
  }
  return true;
}

Node *slist::get(int idx) const {
  Node *curr = head;
  for (int i = 0; i < idx; ++i)
    curr = curr->next;
  return curr;
}

void slist::insert(int idx, Airport *a) {
  Node *n = new Node;
  n->dat = a;
  if (idx == 0) {
    n->next = head;
    head = n;
  } else {
    n->next = get(idx);
    get(idx - 1)->next = n;
  }
  length++;
}

void slist::exchg(int i1, int i2) const {
  Airport *a = get(i1)->dat;
  get(i1)->dat = get(i2)->dat;
  get(i2)->dat = a;
}

void slist::swap(int i1, int i2) {
  if (i1 <= 0 || i1 > size() || i2 <= 0 || i2 > size())
    return;
  if (i1 == i2)
    return;

  Node *n1 = get(i1);
  Node *p1 = i1 > 0 ? get(i1 - 1) : nullptr;
  Node *n2 = get(i2);
  Node *p2 = i2 > 0 ? get(i2 - 1) : nullptr;

  if (n1 != nullptr && n2 != nullptr) {
    if (p1 != nullptr)
      p1->next = n2;
    if (p2 != nullptr)
      p2->next = n1;
    Node *t = n1->next;
    n1->next = n2->next;
    n2->next = t;

    if (p1 == nullptr)
      head = n2;
    else if (p2 == nullptr)
      head = n1;
  }
}

bool slist::isEmpty() const {
  return length == 0 && head == nullptr && tail == nullptr;
}

Node *slist::remove(int idx) {
  if (idx != 0) {
    Node *prev = get(idx - 1);
    Node *current = prev->next;
    Node *next = current->next;
    prev->next = next;
    length--;
    return current;
  } else {
    Node *temp = head;
    head = head->next;
    length--;
    return temp;
  }
}

void slist::set(int idx, Airport *a) const { get(idx)->dat = a; }

int slist::size() const { return length; }

slist slist::subList(int s, int e) {
  slist sublist;
  Node *start = get(s);
  for (int i = s; i < e; i++) {
    sublist.add(start->dat);
    start = start->next;
  }
  return sublist;
}

string slist::toString() const {
  if (length == 0)
    return "\n";
  stringstream ss;
  Node *current = head;
  int count = 1;
  while (current != nullptr) {
    Airport *data = current->dat;
    ss << count << ": {" << data->code << ", (" << data->latitude << ", "
       << data->longitude << ")}" << endl;
    current = current->next;
    count++;
  }
  return ss.str();
}