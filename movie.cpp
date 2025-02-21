#include "movie.h"
#include "util.h"

Movie::Movie(const std::string& name, double price, int qty, 
             const std::string& genre, const std::string& rating) 
    : Product("movie", name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie() {}

std::set<std::string> Movie::keywords() const {
    // convert to lower case
    std::string lowerName = convToLower(name_);

    // get associated keywords
    std::set<std::string> keywords = parseStringToWords(lowerName);
    
    // also, add genre as a keyword
    keywords.insert(genre_);

    return keywords;
}

std::string Movie::displayString() const {
    std::string result = name_ + "\n";
    result += "Genre: " + genre_ + " Rating: " + rating_ + "\n";
    result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return result;
}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << std::endl;
}