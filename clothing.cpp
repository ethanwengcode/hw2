#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string& name, double price, int qty, 
                   const std::string& size, const std::string& brand) 
    : Product("clothing", name, price, qty), size_(size), brand_(brand) {}

Clothing::~Clothing() {}

std::set<std::string> Clothing::keywords() const {
    // convert strings to lower case
    std::string lowerName = convToLower(name_);
    std::string lowerBrand = convToLower(brand_);

    // get associated keywords
    std::set<std::string> keywords = parseStringToWords(lowerName);
    std::set<std::string> brandKeywords = parseStringToWords(lowerBrand);

    keywords.insert(brandKeywords.begin(), brandKeywords.end());

    return keywords;
}

std::string Clothing::displayString() const {
    std::string result = name_ + "\n";
    result += " Size: " + size_ + " Brand: " + brand_ + "\n";
    result += std::to_string(price_) + " " + std::to_string(qty_) + " left.";
    return result;
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << std::endl;
}