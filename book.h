#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <string>

class Book : public Product {
    public:
        // Constructor
        Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author);
    
        // Destructor
        ~Book();
    
        // returns set of keywords associated with book
        std::set<std::string> keywords() const;

        // display book's details
        std::string displayString() const;
    
        // writes book info to output stream
        void dump(std::ostream& os) const;
    
    protected:
        std::string isbn_;
        std::string author_;
    };
    
    #endif