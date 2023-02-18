//*****************************************************************************
// Name: website.cpp
// Descrtiption: This is the executable file for the Website class object.
//*****************************************************************************
#include "website.h"

// name: Website()
// description: constructor
// input: none
// output: none
Website::Website() : topicName(nullptr), address(nullptr), summary(nullptr), review(nullptr), rating(0) {}

// name: Website(const char *topicName, const char *address, const char *summary, const char *review, int rating)
// description: param constructor
// input: none
// output: none
Website::Website(const char *topicName, const char *address, const char *summary, const char *review, int rating) : topicName(nullptr), address(nullptr), summary(nullptr), review(nullptr)
{
   init(topicName, address, summary, review, rating);
}

// name: Website(const Website &aWebsite)
// description: param constructor
// input: none
// output: none
Website::Website(const Website &aWebsite) : topicName(nullptr), address(nullptr), summary(nullptr), review(nullptr)
{
   init(aWebsite.topicName, aWebsite.address, aWebsite.summary, aWebsite.review, aWebsite.rating);
}

// name: ~Website()
// description: destructor
// input: none
// output: none
Website::~Website()
{
   if(this->topicName)
   {
      delete[] this->topicName;
   }
   if (this->address)
   {
      delete[] this->address;
   }
   if (this->summary)
   {
      delete[] this->summary;
   }
   if (this->review)
   {
      delete[] this->review;
   }
   this->topicName = nullptr;
   this->address = nullptr;
   this->summary = nullptr;
   this->review = nullptr;
   this->rating = 0;
}

// name: init(const char *topicName, const char *address, const char *summary, const char *review, int rating)
// description: this function initializes all the private member variables.
// input: none
// output: none
void Website::init(const char *topicName, const char *address, const char *summary, const char *review, int rating)
{
   setTopicName(topicName);
   setAddress(address);
   setSummary(summary);
   setReview(review);
   setRating(rating);
}

// name: setTopicName(const char *srcTopicName)
// description: this function sets topicName.
// input: none
// output: none
void Website::setTopicName(const char *srcTopicName)
{
   if(this->topicName)
   {
      delete[] this->topicName;
      this->topicName = nullptr;
   }
   this->topicName = new char[strlen(srcTopicName) + 1];
   strcpy(this->topicName, srcTopicName);
}

// name: setAddress(const char *srcAddress)
// description: this function sets address.
// input: none
// output: none
void Website::setAddress(const char *srcAddress)
{
   if (this->address)
   {
      delete[] this->address;
      this->address = nullptr;
   }
   this->address = new char[strlen(srcAddress) + 1];
   strcpy(this->address, srcAddress);
}

// name: setSummary(const char *srcSummary)
// description: this function sets summary.
// input: none
// output: none
void Website::setSummary(const char *srcSummary)
{
   if (this->summary)
   {
      delete[] this->summary;
      this->summary = nullptr;
   }
   this->summary = new char[strlen(srcSummary) + 1];
   strcpy(this->summary, srcSummary);
}

// name: setReview(const char *srcReview)
// description: this function sets review.
// input: none
// output: none
void Website::setReview(const char *srcReview)
{
   if (this->review)
   {
      delete[] this->review;
      this->review = nullptr;
   }
   this->review = new char[strlen(srcReview) + 1];
   strcpy(this->review, srcReview);
}

// name: setRating(int srcRating)
// description: this function sets rating.
// input: none
// output: none
void Website::setRating(int srcRating)
{
   this->rating = srcRating;
}

// name: getTopicName()
// description: this function returns topicName.
// input: none
// output: none
const char *Website::getTopicName() const
{
   return topicName;
}

// name: getAddress()
// description: this function returns address.
// input: none
// output: none
const char *Website::getAddress() const
{
   return address;
}

// name: getSummary()
// description: this function returns summary.
// input: none
// output: none
const char *Website::getSummary() const
{
   return summary;
}

// name: getReview()
// description: this function returns review.
// input: none
// output: none
const char *Website::getReview() const
{
   return review;
}

// name: getRating()
// description: this function returns rating.
// input: none
// output: none
int Website::getRating() const
{
   return rating;
}

// name: operator=(const Website &aWebsite)
// description: assignment operator overloading
// input: none
// output: none
const Website &Website ::operator=(const Website &aWebsite)
{
   if (this == &aWebsite)
   {
      return *this;
   }
   init(aWebsite.topicName, aWebsite.address, aWebsite.summary, aWebsite.review, aWebsite.rating);
   return *this;
}

// name: operator<<(ostream &out, const Website &aWebsite)
// description: output operator overloading
// input: none
// output: char *topicName, char *address, char *summary, char *review, int 
// rating
ostream &operator<<(ostream &out, const Website &aWebsite)
{
   out << aWebsite.topicName << endl
       << aWebsite.address << endl
       << aWebsite.summary << endl
       << aWebsite.review << endl
       << aWebsite.rating << endl;
   return out;
}

// name: operator<(const Website &s1, const Website &s2)
// description: relational operator overloading
// input: none
// output: none
bool operator<(const Website &s1, const Website &s2)
{
   int compareResult = strcmp(s1.getTopicName(), s2.getTopicName());
   return compareResult < 0;
}

// name: operator==(const Website &s1, const Website &s2)
// description: relational operator overloading
// input: none
// output: none
bool operator==(const Website &s1, const Website &s2)
{
   int compareResult = strcmp(s1.getAddress(), s2.getAddress());
   return compareResult == 0;
}

bool operator!=(const Website &s1, const Website &s2)
{
   int compareResult = strcmp(s1.getAddress(), s2.getAddress());
   return compareResult != 0;
}