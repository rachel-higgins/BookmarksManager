//*****************************************************************************
// Name: table.cpp
// Descrtiption: This is the executable file for the Table class object.
//*****************************************************************************
#include "table.h"

// name: Table()
// description: constructor
// input: none
// output: none
Table::Table() : root(nullptr), size(0) {}

// name: Table(const Table &aTable)
// description: param constructor
// input: none
// output: none
Table::Table(const Table &aTable) : root(nullptr), size(0)
{
   *this = aTable;
}

// name: ~Table()
// description: destructor
// input: none
// output: none
Table::~Table()
{
   destroy(root);
}

// name: destroy()
// description: this function iterates through the Table object and destroys
// each node in the tree and it's data.
// set to nullptr.
// input: none
// output: none
void Table::destroy(Node *&currRoot)
{
   if (currRoot)
   {
      destroy(currRoot->left);
      destroy(currRoot->right);
      delete currRoot->data;
      delete currRoot;
      currRoot = nullptr;
   }
   size = 0;
}

// name: add(const Website &aWebsite)
// description: this function calls a helper function to add a new website 
// to the BST.
// input: none
// output: none
void Table::add(const Website &aWebsite)
{
   add_(this->root, aWebsite);
   size++;
}

// name: add_(Node *&currRoot, const Website &aWebsite)
// description: this function recursively performs a binary search to find the 
// correct position of insertion.
// input: none
// output: none
void Table::add_(Node *&currRoot, const Website &aWebsite)
{
   if (!currRoot)
   {
      currRoot = new Node(aWebsite);
   }
   else
   {
      int compareResult = strcmp(aWebsite.getTopicName(), currRoot->data->getTopicName());
      if (compareResult < 0)
      {
         add_(currRoot->left, aWebsite);
      }
      else if (compareResult > 0)
      {
         add_(currRoot->right, aWebsite);
      }
      else
      {
         Node *temp = new Node(aWebsite);
         temp->left = currRoot->left;
         currRoot->left = temp;
      }
   }
}

// name: remove(const char *key)
// description: this function calls a helper function to remove all Websites 
// of a given topic.
// input: none
// output: none
bool Table::remove(const char *key)
{
   return remove_(this->root, key);
}

// name: remove_(Node *&currRoot, const char *key)
// description: this recursive function removes all Websites of a given topic.
// input: none
// output: none
bool Table::remove_(Node *&currRoot, const char *key)
{
   if (!currRoot)
   {
      return false;
   }

   int compareResult = strcmp(key, currRoot->data->getTopicName());
   if (compareResult == 0)
   {
      deleteNode(currRoot);
      size--;
      remove_(currRoot, key);
      return true;
   }
   else if (compareResult < 0)
   {
      return remove_(currRoot->left, key);
   }
   else
   {
      return remove_(currRoot->right, key);
   }
}

// name: remove(Website aWebsite)
// description: this function calls a helper function to remove a specific
// Website.
// input: none
// output: none
bool Table::remove(Website aWebsite)
{
   return remove_(this->root, aWebsite);
}

// name: remove_(Node *&currRoot, Website &aWebsite)
// description: this recursive function removes a specific Website.
// input: none
// output: none
bool Table::remove_(Node *&currRoot, Website &aWebsite)
{
   if (currRoot)
   {
      int compareResult = strcmp(aWebsite.getTopicName(), currRoot->data->getTopicName());
      if (*(currRoot->data) == aWebsite)
      {
         deleteNode(currRoot);
         size--;
         return true;
      }
      else if (compareResult > 0)
      {
         return remove_(currRoot->right, aWebsite);
      }
      else
         return remove_(currRoot->left, aWebsite);
   }
   else
      return false;
}

// name: deleteNode(Node *&target)
// description: this function removes a node from the tree.
// input: none
// output: none
void Table::deleteNode(Node *&target)
{
   // target node is a leaf
   if (!target->left && !target->right)
   {
      delete target->data;
      delete target;
      target = nullptr;
   }
   // target node only has left child
   else if (!target->right)
   {
      Node *temp = target;
      target = target->left;
      delete temp->data;
      delete temp;
   }
   // target node only has right child
   else if (!target->left)
   {
      Node *temp = target;
      target = target->right;
      delete temp->data;
      delete temp;
   }
   // target node has two children
   else
   {
      // find the inorder successor of target node
      Node *prev = nullptr;
      Node *curr = target->right; // start with the right child
      if (!curr->left)            // the right child is the inorder successor
      {
         target->right = curr->right;
      }
      else
      {
         while (curr->left)
         {
            prev = curr;
            curr = curr->left; // then go all the way to the left
         }
         prev->left = curr->right;
      }
      delete target->data;
      target->data = curr->data;
      delete curr;
      return;
   }
}

// name: retrieve(const char *key, Website *&aList, int &count)
// description: this function calls a helper function to retrieve all websites 
// that match the search key and return true or false values if any matching 
// websites were or were not retrieved.
// input: none
// output: none
bool Table::retrieve(const char *key, Website *&aList, int &count)
{
   return retrieve_(root, key, aList, count);
}

// name: retrieve_(const Node *currRoot, const char *key, Website *&aList,
// int &count)
// description: this recursive function retrieves all websites that match the 
// search key and return true or false values if any matching websites were or 
// were not retrieved.
// input: none
// output: none
bool Table::retrieve_(const Node *currRoot, const char *key, Website *&aList, int &count)
{
   if (currRoot)
   {
      int compareResult = strcmp(key, currRoot->data->getTopicName());
      if (compareResult == 0)
      {
         int pos = count;
         retrieve_(currRoot->left, key, aList, ++count);
         aList[pos] = *(currRoot->data);
         return count > 0;
      }
      else if (compareResult < 0 && count == 0)
      {
         return retrieve_(currRoot->left, key, aList, count);
      }
      else if (compareResult > 0 && count == 0)
         return retrieve_(currRoot->right, key, aList, count);
   }
   aList = new Website[count + 1];
   return count > 0;
}

// name: operator=(const Table &tableSrc)
// description: assignment operator overloading
// input: none
// output: none
const Table &Table::operator=(const Table &tableSrc)
{
   if (this == &tableSrc)
      return *this;
   if (this->root)
      destroy(this->root);
   size = tableSrc.size;
   copy(tableSrc.root, this->root);
   return *this;
}

// name: copy(Node *srcRoot, Node *&destRoot)
// description: this recursive function copies the data from one node to the 
// other until the entire tree has been copied to the destination tree.
// input: none
// output: none
void Table::copy(Node *srcRoot, Node *&destRoot)
{
   if (srcRoot)
   {
      destRoot = new Node(*(srcRoot->data));
      copy(srcRoot->left, destRoot);
      copy(srcRoot->right, destRoot);
   }
   else
      destRoot = nullptr;
}

// name: operator<<(ostream &out, const Table &aTable)
// description: output operator overloading
// input: none
// output: none
ostream &operator<<(ostream &out, const Table &srcTable)
{
   out << "Tree has " << srcTable.size << " total items" << endl;
   srcTable.display(out, srcTable.root);
   return out;
}

// name: display(ostream &out, Node *currRoot) const
// description: this function displays each element in the table
// input: none
// output: none
void Table::display(ostream &out, Node *currRoot) const
{
   // out << endl
   //     << "Pre-order showing the tree ..." << endl;
   // displayPreorder(out, currRoot);
   out << endl
       << "In-order showing the tree ..." << endl;
   displayInorder(out, currRoot);
   // out << endl
   //     << "Post-order showing the tree ..." << endl;
   // displayPostorder(out, currRoot);
}

// name: display(ostream &out, Node *currRoot) const
// description: this function displays each element in the table in pre-order.
// input: none
// output: none
void Table::displayPreorder(ostream &out, Node *currRoot) const
{
   if (currRoot)
   {
      out << *(currRoot->data) << endl;
      displayPreorder(out, currRoot->left);
      displayPreorder(out, currRoot->right);
   }
}

// name: display(ostream &out, Node *currRoot) const
// description: this function displays each element in the table in order.
// input: none
// output: none
void Table::displayInorder(ostream &out, Node *currRoot) const
{
   if (currRoot)
   {
      displayInorder(out, currRoot->left);
      out << *(currRoot->data) << endl;
      displayInorder(out, currRoot->right);
   }
}

// name: display(ostream &out, Node *currRoot) const
// description: this function displays each element in the table in post-order.
// input: none
// output: none
void Table::displayPostorder(ostream &out, Node *currRoot) const
{
   if (currRoot)
   {
      displayPostorder(out, currRoot->left);
      displayPostorder(out, currRoot->right);
      out << *(currRoot->data) << endl;
   }
}

// name: edit(const Website &aWebsite, const char *newReview, int newRating)
// description: this function modifies the review and rating for a 
// particular topic and website match.
// input: none
// output: none
bool Table::edit(const Website &aWebsite, const char *newReview, int newRating)
{
   edit_(root, aWebsite, newReview, newRating);
   return false;
}

// name: edit_(Node *&currRoot, const Website &aWebsite, const char *newReview, int newRating)
// description: this recursive function modifies the review and rating for a
// particular topic and website match.
// input: none
// output: none
bool Table::edit_(Node *&currRoot, const Website &aWebsite, const char *newReview, int newRating)
{
   if (currRoot)
   {
      int compareResult = strcmp(aWebsite.getTopicName(), currRoot->data->getTopicName());
      if (aWebsite == *(currRoot->data))
      {
         currRoot->data->setReview(newReview);
         currRoot->data->setRating(newRating);
         return true;
      }
      else if (compareResult > 0)
      {
         return edit_(currRoot->right, aWebsite, newReview, newRating);
      }
      else
         return edit_(currRoot->left, aWebsite, newReview, newRating);
   }
   return false;
}

// name: getSize() const
// description: this function returns size.
// input: none
// output: none
int Table::getSize() const
{
   return size;
}

// name: getTreeHeight() const
// description: this function calculates the actual height of the tree along 
// with the minimum and maximum possible heights given the number of items in 
// the table.
// input: none
// output: none
int Table::getTreeHeight() const
{
   int currLen = 0, maxLen = size, minLen = 0, n = 1;
   if (size > 0)
   {
      for (minLen++; n < size; minLen++)
      {
         n *= 2;
         n += 1;
      }
   }
   getTreeHeight_(root, currLen, currLen);
   cout << "The tree has " << size << " total items and a height of "
        << currLen << endl
        << "Minimum Tree Height Possible: " << minLen << endl
        << "Maximum Tree Height Possible: " << maxLen << endl
        << endl;

   return currLen;
}

// name: getTreeHeight_(Node *currRoot, int currLen, int &maxLen) const
// description: this recursive function calculates the actual height of the
// tree along with the tree.
// input: none
// output: none
void Table::getTreeHeight_(Node *currRoot, int currLen, int &maxLen) const
{
   if (currRoot)
   {
      getTreeHeight_(currRoot->left, currLen + 1, maxLen);
      getTreeHeight_(currRoot->right, currLen + 1, maxLen);
   }
   else
   {
      if (currLen > maxLen)
      {
         maxLen = currLen;
      }
   }
}

// name: loadFromFile(const char *fileName)
// description: this function opens, then reads from a given file and passes the data to the add() function.
// input: none
// output: error message if file fails to open.
void Table::loadFromFile(const char *fileName)
{
   ifstream in;
   const int MAX_CHAR = 201;
   char topicName[MAX_CHAR + 1];
   char address[MAX_CHAR + 1];
   char summary[MAX_CHAR + 1];
   char review[MAX_CHAR + 1];
   int rating;

   in.open(fileName);
   if (!in)
   {
      cerr << "Fail to open " << fileName << " for reading!" << endl;
      exit(1);
   }

   in.get(topicName, MAX_CHAR, ';');
   while (!in.eof())
   {
      in.ignore(1);
      in.get(address, MAX_CHAR, ';');
      in.ignore(1);
      in.get(summary, MAX_CHAR, ';');
      in.ignore(1);
      in.get(review, MAX_CHAR, ';');
      in.ignore(1);
      in >> rating;
      in.ignore(MAX_CHAR, '\n');

      Website currWebsite(topicName, address, summary, review, rating);
      add(currWebsite);

      in.get(topicName, MAX_CHAR, ';');
   }
   in.close();
}

// name: saveToFile(const char *fileName) const
// description: this function writes the data in aTable into a given file.
// input: none
// output: error message if file fails to open.
void Table::saveToFile(const char *fileName) const
{
   ofstream out;

   out.open(fileName);
   if (!out)
   {
      cerr << "Fail to open " << fileName << " for writing!" << endl;
      exit(1);
   }

   saveToFile(out, this->root);
   out.close();
}

// name: saveToFile(ostream &out, Node *currRoot) const
// description: this function writes the data in aTable into a given file.
// input: none
// output: error message if file fails to open.
void Table::saveToFile(ostream &out, Node *currRoot) const
{
   if (currRoot)
   {
      out << currRoot->data->getTopicName() << ';'
          << currRoot->data->getAddress() << ';'
          << currRoot->data->getSummary() << ';'
          << currRoot->data->getReview() << ';'
          << currRoot->data->getRating() << endl;
      saveToFile(out, currRoot->left);
      saveToFile(out, currRoot->right);
   }
}
