#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <string>
#include <set>

class Clothing : public Product {
public:
    // Constructor
    Clothing(const std::string& name, double price, int qty, 
             const std::string& size, const std::string& brand);

    // Destructor
    ~Clothing();

    // returns set of keywords associated with clothing
    std::set<std::string> keywords() const;

    // display clothing's details
    std::string displayString() const;

    // writes clothing item info to output stream
    void dump(std::ostream& os) const;

private:
    std::string size_;
    std::string brand_;
};

#endif