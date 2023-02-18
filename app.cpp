//*****************************************************************************
// Author: Rachel Higgins
// Date: November 23, 2022
// Course: CS260 Data Structures
// Assignment: C++ Project Assignment 4
// Descrtiption: this is a program that keeps track of websites using the 
// Binary Search Tree ADT. The program allows the user to add a new
// website, retrieve all websites for a given topic, edit a website to modify
// the review and rating, remove all websites for a given topic, and
// display all items alphabetically, and monitor BSTs height.
// Input: int option
// Output: Table myFavorites, Website allMatches[], int numFound
//*****************************************************************************
#include <iostream>
#include "website.h"
#include "table.h"
using namespace std;

const int MAX_CHAR = 201;

int menu();
int getOption(int min, int max);
void validateInput(int &num);
void add(Table &aTable);
void edit(Table &aTable);
void removeSingle(Table &aTable);
void removeMultiple(Table &aTable);
int search(Table &aTable, Website *&allMatches);
void displayList(const int, const Website *);
void testApp();

int main()
{
   Table myFavorites;
   Website *allMatches = nullptr;
   Website aWebsite;
   int option = 0;
   char savedBookmarks[MAX_CHAR + 1] = "bookmarks.txt";

   myFavorites.loadFromFile(savedBookmarks);

   while ((option = menu()) && option != 8)
   {
      int count = 0;
      switch (option)
      {
      case 1: // Add a new website
         add(myFavorites);
         break;
      case 2: // Retrieve all websites for a specific topic
         count = search(myFavorites, allMatches);
         cout << "(" << count << " websites retrieved)\n\n";
         delete[] allMatches;
         allMatches = nullptr;
         break;
      case 3: // Edit a bookmark entry
         edit(myFavorites);
         break;
      case 4: // Select and remove a website
         removeSingle(myFavorites);
         break;
      case 5: // Remove all websites for a given topic
         removeMultiple(myFavorites);
         break;
      case 6: // Display all bookmark entries alphabetically
         cout << myFavorites;
         break;
      case 7: // Monitor tree height
         myFavorites.getTreeHeight();
         break;
      default:
         cerr << "\nError! " << option << " is not an option.\n\n";
         break;
      }
   }
   cout << "Goodbye!\n\n";
   return 0;
}

// name: menu()
// description: this function displays a menu, gets user input as int option ?
// and returns the integer.
// input: int option
// output: a menu of options as text.
int menu()
{
   int option = 0;
   cout << "------------------------------------------------------------------------------" << endl;
   cout << "Bookmark menu: " << endl
        << "1. Add a new website" << endl
        << "2. Retrieve all websites for a specific topic" << endl
        << "3. Edit a bookmark entry" << endl
        << "4. Select and remove a website" << endl
        << "5. Remove all websites for a specific topic" << endl
        << "6. Display all bookmark entries" << endl
        << "7. Monitor the performance of the hash table" << endl
        << "8. Exit" << endl;
   cout << "Enter option (1 - 8): ";
   option = getOption(1, 8);
   cout << "------------------------------------------------------------------------------" << endl
        << endl;
   return option;
}

// name: getOption(int min, int max)
// description: this function gets and returns valid input between min and max.
// input: int option
// output: error message
int getOption(int min, int max)
{
   int option = 0;
   validateInput(option);
   while (option < min || option > max)
   {
      cerr << "Input error! Enter option (" << min << " - " << max << "): ";
      validateInput(option);
   }
   return option;
}

// name: validateInput(int &num)
// description: this function request for a different input while incorrect
// input type persists
// input: int num
// output: error message
void validateInput(int &num)
{
   cin >> num;
   while (!cin)
   {
      cin.clear();
      cin.ignore(MAX_CHAR, '\n');
      cerr << "Input error! Try agin: ";
      cin >> num;
   }
   cin.ignore(MAX_CHAR, '\n');
}

// name: add(Table *&aTable)
// description: this function gets the data for a new Website object then
// inserts it into the given Table object.
// input: char textInput, int userInput
// output: prompt
void add(Table &aTable)
{
   Website aWebsite;
   char textInput[MAX_CHAR + 1];
   int userInput = 0;

   cout << "Enter topic name (" << MAX_CHAR << " character limit): ";
   cin.getline(textInput, MAX_CHAR);
   aWebsite.setTopicName(textInput);
   cout << "Enter the URL: ";
   cin.getline(textInput, MAX_CHAR);
   aWebsite.setAddress(textInput);
   cout << "Enter a Summary (" << MAX_CHAR << " character limit): ";
   cin.getline(textInput, MAX_CHAR);
   aWebsite.setSummary(textInput);
   cout << "Enter your review (" << MAX_CHAR << " character limit): ";
   cin.getline(textInput, MAX_CHAR);
   aWebsite.setReview(textInput);
   cout << "Enter your rating (1 - 5): ";
   userInput = getOption(1, 5);
   aWebsite.setRating(userInput);

   aTable.add(aWebsite);
}

// name: edit(Table &aTable)
// description: this function edits a specific website.
// input: int option, int newRating, char newReview
// output: prompt
void edit(Table &aTable)
{
   Website *allMatches = nullptr;
   int option = 0, newRating = 0, count = search(aTable, allMatches);
   char newReview[MAX_CHAR + 1];

   displayList(count, allMatches);
   if (count > 1)
   {
      cout << "Select a result to edit: ";
      option = getOption(1, count) - 1;
   }
   if (count >= 1)
   {
      cout << "Enter new review: ";
      cin.getline(newReview, MAX_CHAR);
      cout << "Enter new rating: ";
      newRating = getOption(1, 5);
      aTable.edit(allMatches[option], newReview, newRating);
   }
   delete[] allMatches;
}

// name: removeSingle(Table &aTable)
// description: this function removes a specific websites.
// input: int pos
// output: prompt
void removeSingle(Table &aTable)
{
   Website *allMatches = nullptr;
   int count, pos = 0;

   count = search(aTable, allMatches);

   if (count > 1)
   {
      displayList(count, allMatches);
      cout << "Enter which website to remove (1 - " << count << "): ";
      pos = getOption(1, count) - 1;
      cout << "Removing 1 item from tree...\n"
           << endl;
      aTable.remove(allMatches[pos]);
   }
   else if (count == 1)
   {
      cout << "1 result found: " << endl
           << endl
           << allMatches[pos] << endl
           << "Removing 1 item from tree...\n"
           << endl;
      aTable.remove(allMatches[pos]);
   }
   else
      displayList(count, allMatches);

   delete[] allMatches;
}

// name: removeMultiple(Table &aTable)
// description: this function removes all websites of a given topic.
// input: char textInput
// output: prompt
void removeMultiple(Table &aTable)
{
   int count = aTable.getSize();
   char textInput[MAX_CHAR + 1];

   cout << "Enter topic name: ";
   cin.getline(textInput, MAX_CHAR);
   aTable.remove(textInput);
   count -= aTable.getSize();
   cout << "Removing " << count << " item(s) from tree...\n\n";
}

// name: search(Table &aTable, Website *&aList)
// description: this function gets a search key from the user to retrieve
// all matching websites. The number of matches gets returned.
// input: char textInput
// output: prompt
int search(Table &aTable, Website *&aList)
{
   char textInput[MAX_CHAR + 1];
   int count = 0;
   if (aList)
   {
      delete[] aList;
      aList = nullptr;
   }
   cout << "Enter topic name: ";
   cin.getline(textInput, MAX_CHAR);
   aTable.retrieve(textInput, aList, count);

   return count;
}

// name: displayList(const int size, const Website *aList)
// description: this function displays each element in a given array.
// input: none
// output: Website aList[]
void displayList(const int size, const Website *aList)
{
   cout << size << " results found..." << endl
        << endl;
   for (int i = 0; i < size; i++)
   {
      cout << "Result " << i + 1 << ":\n"
           << aList[i] << endl;
   }
}

// name: testApp()
// description: this function test the table and website ADTs.
// input: none
// output: none
void testApp()
{
   char topic1[MAX_CHAR] = "Data Structures";
   char address1[MAX_CHAR] = "https://www.pearson.com/us/higher-education/product/Carrano-Data-Abstraction-Problem-Solving-with-C-5th-Edition/9780321433329.html";
   char summary1[MAX_CHAR] = "The classic, best-selling Data Abstraction and Problem Solving with C++: Walls and Mirrors book provides a firm foundation in data structures";
   char review1[MAX_CHAR] = "The textbook covers each topic for PCC's Data Structures in a way that is very easy to understand";

   char topic2[MAX_CHAR] = "Python";
   char address2[MAX_CHAR] = "https://docs.python.org/3/";
   char summary2[MAX_CHAR] = "This is the official documentation for the latest version ofPython";
   char review2[MAX_CHAR] = "Best resource for Python";

   Website test1(topic1, address1, summary1, review1, 5);
   Website test2(topic2, address2, summary2, review2, 5);
   Website test3(test1);
   test2 = test1;
}