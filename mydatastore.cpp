#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <fstream>

MyDataStore::MyDataStore(){

}

MyDataStore::~MyDataStore(){
    
}

void MyDataStore::addProduct(Product* product) {
    products_.push_back(product);

    // get associated keywords
    std::set<std::string> keywords = product->keywords();

    // associate product with its keywords
    std::set<std::string>::iterator it;
    for (it = keywords.begin(); it != keywords.end(); ++it) {
        keywordMap_[*it].insert(product);
    }
}

void MyDataStore::addUser(User* user) {
    users_[user->getName()] = user;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> resultSet;
    for (size_t i = 0; i < terms.size(); i++) {
        std::string term = convToLower(terms[i]);
        if (keywordMap_.find(term) != keywordMap_.end()) { // found term 
            // first search
            if (resultSet.empty()) {
                resultSet = keywordMap_[term];
            } else { 
                if(type == 1) {
                    resultSet = setUnion(resultSet, keywordMap_[term]);
                }
                else {
                    resultSet = setIntersection(resultSet, keywordMap_[term]);
                }
            }
        }
    }
    // convert to a vector 
    return std::vector<Product*>(resultSet.begin(), resultSet.end());
}

void MyDataStore::addToCart(const std::string& username, Product* product) {
  if(users_.find(username) == users_.end()){
    std::cout << "Invalid request" << std::endl;
  }
  else {
    userCart_[username].push_back(product);
  }
}

void MyDataStore::viewCart(const std::string& username) {
    // cannot find username
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username\n";
        return;
    }
    // get user's cart
    std::vector<Product*> cart = userCart_[username];
    for(size_t i = 0; i < cart.size(); i++){
      std::cout << "Item " << i+1 << "\n" << cart[i]->displayString() << std::endl;
    }
}

void MyDataStore::buyCart(const std::string& username) {
    // cannot find username
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username\n";
        return;
    }

    // get user's cart
    std::vector<Product*>& cart = userCart_[username];
    std::vector<Product*> newCart;
    
    for(size_t i = 0; i <cart.size(); i++){
      Product* p = cart[i];
       // item is available and user has enough money
        if (p->getQty() > 0 && users_[username]->getBalance() >= p->getPrice()) {
            // update user's balance and item's inventory 
            p->subtractQty(1);
            users_[username]->deductAmount(p->getPrice());
        } else { 
            // keep item in user's cart 
            newCart.push_back(p);
        }
    }
    // update user's cart to be remaining (if any) items
    userCart_[username] = newCart;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (std::vector<Product*>::iterator it = products_.begin(); it != products_. end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>\n";
    
    ofile << "<users>\n";
    for(std::unordered_map<std::string, User*>::iterator it = users_.begin(); it != users_.end(); ++it) {
        User* u = it->second;
        u->dump(ofile);
    }
    ofile << "</users>\n";

    // deallocate 
    for(size_t i = 0; i < products_.size(); i++){
      delete products_[i];
    }
    for (std::unordered_map<std::string, User *>::iterator it = users_.begin(); it != users_.end(); ++it){
        delete (it->second);
    }
    users_.clear();
}
