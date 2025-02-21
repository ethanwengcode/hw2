#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <string>
#include <set>

class Movie : public Product {
public:
    // Constructor
    Movie(const std::string& name, double price, int qty, 
          const std::string& genre, const std::string& rating);

    // Destructor
    ~Movie();

    // returns set of keywords associated with movie
    std::set<std::string> keywords() const override;

    // display movie's details
    std::string displayString() const override;

    // writes movie to output stream
    void dump(std::ostream& os) const override;

private:
    std::string genre_;
    std::string rating_;
};

#endif
