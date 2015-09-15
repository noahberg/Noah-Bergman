#include "llistint.h"
#include <cstdlib>
#include <stdexcept>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const int& val)
{
	if(loc > size_ || loc < 0) {
		return;
	}
	if(size_ == 0) {
		Item* new_item = new Item;
		new_item->val = val;
		new_item->next = NULL;
		new_item->prev = NULL;
		head_ = new_item;
		tail_ = new_item; 
	}
	else if(loc==size_) {
		Item* new_item = new Item;
		new_item->val = val;
		new_item->prev = tail_;
		new_item->next = NULL;
		tail_->next = new_item;
		tail_ = new_item;

	}
	else if(loc ==0) {
		Item* new_item = new Item;
		new_item->val = val;
		new_item->next = head_;
		new_item->prev = NULL;
		head_->prev = new_item;
		head_ = new_item;
	}
	else {
		Item* new_item = new Item;
		new_item->val = val;
		Item* p = getNodeAt(loc-1);
		Item* n = getNodeAt(loc);
		new_item->prev = p;
		new_item->next = n;
		p->next = new_item;
		n->prev = new_item;
	}
	size_++;


}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
	if(loc > size_ -1 || loc < 0 || size_ ==0) {
		return;
	}
	else if(loc == 0) {
		Item* temp = head_;
		head_ = head_->next;
		if(head_ != NULL)
			head_->prev = NULL;
		delete temp; 
	}
	else if(loc == size_-1) {
		Item* temp = tail_;
		tail_ = tail_->prev;
		tail_->next = NULL;
		delete temp; 
	}
	else {
		Item* temp = getNodeAt(loc);
		Item* p = temp->prev;
		Item* n = temp->next;
		delete temp;
		p->next = n;
		n->prev = p;
	}
	size_--;
}

void LListInt::set(int loc, const int& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  if(loc < 0 || loc >= size_){
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
 * Complete the following function
 */
LListInt::Item* LListInt::getNodeAt(int loc) const
{	
	if(loc >= size_ || loc < 0) {
		return NULL;
	}
	if(loc ==0 ) {
		return head_;
	}
	if(loc == size_ -1) {
		return tail_;
	}
	if(loc > size_/2) {
		Item* current = tail_;
		for(int i =size_-2; i>0; i++) {
			current = current->prev;
			if(i==loc)
				return current;
		}
	}
	else {
		Item* current = head_;
		for(int i = 1; i<size_; i++) {
			current = current->next;
			if(i==loc)
				return current;
		}
	}


}
