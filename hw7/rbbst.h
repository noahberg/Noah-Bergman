/*
 * rbbst.h
 *
 * Date        Author    Notes
 * =====================================================
 * 2014-04-14  Kempe     Initial version
 * 2015-04-06  Redekopp  Updated formatting and removed
 *                         KeyExistsException
 */
#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include "bst.h"

/* -----------------------------------------------------
 * Red-Black Nodes and Search Tree
 ------------------------------------------------------*/

enum Color {red, black};

template <class KeyType, class ValueType>
class RedBlackNode : public Node<KeyType, ValueType>
{
public:
  RedBlackNode (KeyType k, ValueType v, RedBlackNode<KeyType, ValueType> *p)
    : Node<KeyType, ValueType> (k, v, p)
    { color = red; }
  
  virtual ~RedBlackNode () {}
  
  Color getColor () const
    { return color; }
  
  void setColor (Color c)
    { color = c; }
  
  virtual RedBlackNode<KeyType, ValueType> *getParent () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_parent; }
  
  virtual RedBlackNode<KeyType, ValueType> *getLeft () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_left; }
  
  virtual RedBlackNode<KeyType, ValueType> *getRight () const
    { return (RedBlackNode<KeyType,ValueType>*) this->_right; }
  
 protected:
  Color color;
};

/* -----------------------------------------------------
 * Red-Black Search Tree
 ------------------------------------------------------*/

template <class KeyType, class ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
  void insert (const std::pair<const KeyType, ValueType>& new_item) {
  /* This one is yours to implement.
     It should insert the (key, value) pair to the tree, 
     making sure that it remains a valid Red-Black Tree.
     If the key is already in the tree
     (with a possibly different associated value),
     then it should overwrite the value with the new one.
     We strongly recommend defining suitable (private) helper functions. */
     RedBlackNode<KeyType, ValueType> *newNode = new RedBlackNode<KeyType, ValueType>(new_item.first, new_item.second, NULL);
      Node<KeyType, ValueType> *curr = RedBlackTree<KeyType, ValueType>::root;
     if(curr == NULL) {
        RedBlackTree<KeyType, ValueType>::root = newNode;
        newNode->setColor(black);
        return;
     }
     while(curr) {
        if(newNode->getKey() == curr->getKey()) {
          curr->setValue(newNode->getValue());
          return;
        }
        else if(newNode->getKey() < curr->getKey()) {
          if(curr->getLeft() == NULL) {
            curr->setLeft(newNode);
            newNode->setParent(curr);
            break;
          }
          else {
            curr = curr->getLeft();
          }
        }
        else if(newNode->getKey() > curr->getKey()) {
          if(curr->getRight() == NULL) {
            curr->setRight(newNode);
            newNode->setParent(curr);
            break;
          }
          else {
            curr = curr->getRight();
          }

        }

     }
     if((static_cast<RedBlackNode<KeyType,ValueType>*>(curr)->getColor()) == black)
      return;
    fixTree(newNode);
}

private:
  RedBlackNode<KeyType, ValueType>* findMyUncle(RedBlackNode<KeyType, ValueType>* curr) {
      if(amRightChild(curr)) {
        curr = curr->getParent();
        return curr->getLeft();
      }
      else {
        curr = curr->getParent();
        if(curr == NULL) {
          return curr;
        }
        return curr->getRight();
      }
  }
  bool amRightChild(RedBlackNode<KeyType, ValueType>* curr) {
    if(curr->getParent() != NULL) {
      if((curr->getParent())->getRight() == curr)
        return true;
    }
    else
      return false;
  }
  RedBlackNode<KeyType, ValueType>* RightRotate(RedBlackNode<KeyType, ValueType>* newParent) {

      RedBlackNode<KeyType, ValueType>* newChild = newParent->getParent();
      bool isRight = amRightChild(newChild);
      newChild->setLeft(newParent->getRight());
      newParent->setRight(newChild);
      newParent->setParent(newChild->getParent());
      if(newParent->getParent() == NULL) {
        RedBlackTree<KeyType, ValueType>::root = newParent;
      }
      else {
        if(isRight)
          (newParent->getParent())->setRight(newParent);
        else
          (newParent->getParent())->setLeft(newParent);
      }
      newChild->setParent(newParent);
      if(newChild->getLeft() != NULL) {
         RedBlackNode<KeyType, ValueType>* left = newChild->getLeft();
         left->setParent(newChild);
      }
      return newParent;
  }
  // start at rightmost node
  RedBlackNode<KeyType, ValueType>* LeftRotate(RedBlackNode<KeyType, ValueType>* newParent) {

  
      RedBlackNode<KeyType, ValueType>* newChild = newParent->getParent();
      bool isRight = amRightChild(newChild);
      newChild->setRight(newParent->getLeft());
      newParent->setLeft(newChild);
      newParent->setParent(newChild->getParent());
      if(newParent->getParent() == NULL) {
        RedBlackTree<KeyType, ValueType>::root = newParent;
      }
      else {
        if(isRight)
          (newParent->getParent())->setRight(newParent);
        else
          (newParent->getParent())->setLeft(newParent);
      }
      newChild->setParent(newParent);
      if(newChild->getRight() != NULL) {
         RedBlackNode<KeyType, ValueType>* right = newChild->getRight();
         right->setParent(newChild);
      }
      return newParent;

    
  }
  void fixTree(RedBlackNode<KeyType, ValueType>* problemNode) {
      if(problemNode == RedBlackTree<KeyType, ValueType>::root) {
        static_cast<RedBlackNode<KeyType,ValueType>*>(RedBlackTree<KeyType, ValueType>::root)->setColor(black);
        return;
      }
      if(problemNode->getParent() == RedBlackTree<KeyType, ValueType>::root) {
        static_cast<RedBlackNode<KeyType,ValueType>*>(RedBlackTree<KeyType, ValueType>::root)->setColor(black);
        return;
      }

      else if((findMyUncle(problemNode) != NULL) && ((findMyUncle(problemNode))->getColor() == red)) {
            static_cast<RedBlackNode<KeyType,ValueType>*>(findMyUncle(problemNode))->setColor(black);
            static_cast<RedBlackNode<KeyType,ValueType>*>(problemNode->getParent())->setColor(black);
            static_cast<RedBlackNode<KeyType,ValueType>*>((problemNode->getParent())->getParent())->setColor(red);
            RedBlackNode<KeyType, ValueType>* gp = ((problemNode->getParent())->getParent());
            if((gp->getParent() == NULL) || ((gp->getParent())->getColor() == red)) {
              fixTree(gp);
            }
            else
              return;
        }
      else {

        if(!amRightChild(problemNode->getParent())) {
          if(!amRightChild(problemNode)) {
            problemNode = RightRotate(problemNode->getParent());
            problemNode->setColor(black);
            (problemNode->getRight())->setColor(red);
            return;
          }
          else {
            problemNode = LeftRotate(problemNode);
            problemNode = RightRotate(problemNode->getParent());
            problemNode->setColor(black);
            (problemNode->getRight())->setColor(red);
            return;

          }
        }
        else {
          if(amRightChild(problemNode)) {
            problemNode = LeftRotate(problemNode->getParent());
            problemNode->setColor(black);
            (problemNode->getLeft())->setColor(red);
            return;
          }
          else {
            problemNode = RightRotate(problemNode);
            problemNode = LeftRotate(problemNode->getParent());
            problemNode->setColor(black);
            (problemNode->getLeft())->setColor(red);
            return;

          }
        }
      }
    }
      
  };



#endif
