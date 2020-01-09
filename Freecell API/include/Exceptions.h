//Andrew Lucentini, lucenta
#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class invalid_deck : public std::exception {
   const char * what () const throw () {
      return "invalid deck of cards";
   }
};

class invalid_index : public std::exception {
   const char * what () const throw () {
      return "invalid index for pile type";
   }
};

class invalid_availability : public std::exception {
   const char * what () const throw () {
      return "no card available";
   }
};

class invalid_move : public std::exception {
   const char * what () const throw () {
      return "invalid move";
   }
};

#endif