#include "Strand.h"
#include <cstring>
#include <iostream>

Strand::Strand() : mString(0) { }

Strand::Strand(const char *src) : mString(0) {
  setString(src);
}

Strand::Strand(const Strand &src) : mString(0) {
  *this = src;
}

Strand::~Strand() {
  if (mString) {
    delete [] mString;
    mString = 0;
  }
}

Strand &Strand::operator=(const Strand &rhs) {
  setString(rhs.getString());
  return *this;
}

Strand &Strand::operator+=(const Strand &rhs) {
  char *added = new char [std::strlen(getString()) + std::strlen(rhs.getString()) + 1];
  std::strcpy(added, getString());
  std::strcat(added, rhs.getString());
  setString(added);
  delete [] added;
  return *this;
}

Strand Strand::operator+(const Strand &rhs) const {
  // Compute the new string
  char *added = new char [std::strlen(getString()) + std::strlen(rhs.getString()) + 1];
  std::strcpy(added, getString());
  std::strcat(added, rhs.getString());

  Strand newInstance(added);
  return newInstance;
}

bool Strand::operator==(const Strand &rhs) const {
  return std::strcmp(getString(), rhs.getString()) == 0;
}

bool Strand::operator!=(const Strand &rhs) const {
  return !(*this == rhs);
}

bool Strand::operator<(const Strand &rhs) const {
  return std::strcmp(getString(), rhs.getString()) < 0;
}

bool Strand::operator>(const Strand &rhs) const {
  return std::strcmp(getString(), rhs.getString()) > 0;
}

char* Strand::getString() const {
  return mString;
}

void Strand::setString(const char *string) {
  if (mString) {
    delete[] mString;
    mString = 0;
  }

  if (string) {
    mString = new char [std::strlen(string) + 1];
    std::strcpy(mString, string);
  }
}

size_t Strand::size() const {
  return std::strlen(mString);
}

Strand Strand::substrand(size_t i, size_t j) const {
  char *newString = new char [j - i];
  size_t index;
  for (index=i; index < j; index++) {
    newString[index-i] = mString[index];
  }

  Strand *newStrand = new Strand;
  newStrand->setString(newString);
  return *newStrand;
}

Strand Strand::merge(size_t i, const Strand &rhs) const {
  Strand *newStrand = new Strand;
  *newStrand = substrand(0, i);
  *newStrand += rhs;
  return *newStrand;
}

size_t Strand::overlap(const Strand &rhs) const {
  size_t i;
  for (i=0; i < size(); i++) {
    Strand *last = new Strand;
    Strand *first = new Strand;

    *last = substrand(i, size());
    *first = rhs.substrand(0, size()-i);

    if (*last == *first) {
      return i;
    }
    delete last;
    delete first;
  }
  return size() + 1;
}
