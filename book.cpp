#include "book.h"
#include "util.h"

Book::Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author) 
    : Product("book", name, price, qty), isbn_(isbn), author_(author){}

Book::~Book(){}

std::set<std::string> Book::keywords() const {
    // convert to lower case
    std::string lowerName = convToLower(name_);
    std::string lowerAuthor = convToLower(author_);

    // get associated keywords
    std::set<std::string> keywords = parseStringToWords(lowerName);
    std::set<std::string> authorKeywords = parseStringToWords(lowerAuthor);

    keywords.insert(authorKeywords.begin(), authorKeywords.end());

    // also, add isbn as a keyword
    keywords.insert(isbn_);  

    return keywords;
}

std::string Book::displayString() const {
    std::string result = name_ + "\n";
    result += "Author: " + author_ + " ISBN: " + isbn_ + "\n";
    result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return result;
}

void Book::dump(std::ostream& os) const {
    Product::dump(os); 
    os << isbn_ << "\n" << author_ << std::endl;
}