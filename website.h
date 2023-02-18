//*****************************************************************************
// Name: website.h
// Descrtiption: This is the header file for the Website class object.
//*****************************************************************************
#ifndef WEBSITE_H
#define WEBSITE_H
#include <iostream>
#include <cstring>
using namespace std;

class Website
{
public:
   Website();
   Website(const char *, const char *, const char *, const char *, int);
   Website(const Website &);
   ~Website();
   void setTopicName(const char *);
   void setAddress(const char *);
   void setSummary(const char *);
   void setReview(const char *);
   void setRating(int);
   const char *getTopicName() const;
   const char *getAddress() const;
   const char *getSummary() const;
   const char *getReview() const;
   int getRating() const;
   const Website &operator=(const Website &);
   friend ostream &operator<<(ostream &, const Website &);
private:
   char *topicName;
   char *address;
   char *summary;
   char *review;
   int rating;
   void init(const char *, const char *, const char *, const char *, int);
};
bool operator<(const Website &, const Website &);
bool operator==(const Website &s1, const Website &s2);
bool operator!=(const Website &s1, const Website &s2);

#endif