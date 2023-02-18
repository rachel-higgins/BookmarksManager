//*****************************************************************************
// Name: table.h
// Descrtiption: This is the header file for the Table class object.
//*****************************************************************************
#ifndef TABLE_H
#define TABLE_H
#include "website.h"
#include <fstream>

class Table
{
public:
   Table();
   Table(const Table &aTable);
   ~Table();
   void add(const Website &aWebsite);
   bool edit(const Website &aWebsite, const char *newReview, int newRating);
   bool remove(const char *key);
   bool remove(Website aWebsite);
   bool retrieve(const char *key, Website *&aList, int &count);
   int getSize() const;
   int getTreeHeight() const;
   const Table &operator=(const Table &tableSrc);
   friend ostream &operator<<(ostream &out, const Table &aTable);
   void searchAndDisplay(char *key);
   void loadFromFile(const char *fileName);
   void saveToFile(const char *fileName) const;
   

private:
   struct Node
   {
      Node() : data(nullptr), left(nullptr), right(nullptr) {}
      Node(const Website &aWebsite)
      {
         data = new Website(aWebsite);
         left = right = nullptr;
      }
      Website *data;
      Node *left;
      Node *right;
   };

   Node *root;
   int size;
   void add_(Node *&, const Website &);
   bool remove_(Node *&currRoot, const char *key, Website &aWebsite);
   void deleteNode(Node *&target);
   void destroy(Node *&currRoot);
   bool retrieve_(const Node *currRoot, const char *key, Website *&aList, int &count);
   bool remove_(Node *&currRoot, const char *key);
   bool remove_(Node *&currRoot, Website &aWebsite);
   void copy(Node *srcRoot, Node *&destRoot);
   bool edit_(Node *&currRoot, const Website &aWebsite, const char *newReview, int newRating);
   void display(ostream &out, Node *currRoot) const;
   void displayPreorder(ostream &out, Node *currRoot) const;
   void displayInorder(ostream &out, Node *currRoot) const;
   void displayPostorder(ostream &out, Node *currRoot) const;
   void getTreeHeight_(Node *currRoot, int currLen, int &maxLen) const;
   void saveToFile(ostream &out, Node *currRoot) const;
};

#endif