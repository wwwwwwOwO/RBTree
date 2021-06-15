#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <vector>
using namespace std;


typedef int T;

class Bag {
  public:
   virtual size_t size() const = 0;//returns the number of items in the bag.
   virtual bool empty() const = 0;//returns true if it is empty, returns false otherwise.
   virtual bool contains(const T &x) const = 0;//returns true if x is in the bag, returns false otherwise.
   virtual void insert(const T &x) = 0;//insert x even if x is in the bag
   virtual void erase(const T &x) = 0;//erase x if x is in the bag.
   virtual void display() const = 0;//print all elements to standard output in ascending order, and leave a space after every element.
   virtual T min() const = 0;//returns a reference to the smallest item if it is not empty.
   virtual T max() const = 0; //returns a reference to the biggest item if it is not empty.
   virtual void clear() = 0;//make an empty bag 
   void print()const //don't override this method! 
   {
      cout<<"size:" <<size()<<endl;
      cout<<"elements:";
      display();
      cout<<endl;
   }
};

#endif
