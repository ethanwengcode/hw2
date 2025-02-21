#include "mydatastore.h"
#include "util.h"
#include <iostream>
#include <fstream>

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {}

void MyDataStore::addProduct(Product* product) {
    products_.push_back(product);

    // get associated keywords
    std::set<std::string> keywords = product->keywords();

    // associate product with its keywords
    for (const std::string& key : keywords) {
        keywordMap_[key].insert(product);
    }
}

void MyDataStore::addUser(User* user) {
    users_[user->getName()] = user;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
    std::set<Product*> resultSet;
    for (std::string term : terms) {
        term = convToLower(term);
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
    // find username
    if (users_.find(username) != users_.end()) {
        // add product to user's cart
        userCart_[username].push(product);
    } else {
        std::cout << "Invalid request\n";
    }
}

void MyDataStore::viewCart(const std::string& username) {
    // cannot find username
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username\n";
        return;
    }
    // get user's cart
    std::queue<Product*> cart = userCart_[username];
    int index = 1;
    while (!cart.empty()) {
        std::cout << "Item " << index << "\n" << cart.front()->displayString() << std::endl;
        index++;
        cart.pop();
    }
}

void MyDataStore::buyCart(const std::string& username) {
    // cannot find username
    if (users_.find(username) == users_.end()) {
        std::cout << "Invalid username\n";
        return;
    }

    // get user's cart
    std::queue<Product*>& cart = userCart_[username];
    std::queue<Product*> newCart;
    
    while (!cart.empty()) {
        // get first item
        Product* p = cart.front();
        cart.pop();
        
        // item is available and user has enough money
        if (p->getQty() > 0 && users_[username]->getBalance() >= p->getPrice()) {
            // update user's balance and item's inventory 
            p->subtractQty(1);
            users_[username]->deductAmount(p->getPrice());
        } else { 
            // keep item in user's cart 
            newCart.push(p);
        }
    }
    // update user's cart to be remaining (if any) items
    userCart_[username] = newCart;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>\n";
    for (size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile);
    }
    ofile << "</products>\n";
    
    ofile << "<users>\n";
    std::unordered_map<std::string, User*>::iterator it;
    for(it = users_.begin(); it != users_.end(); ++it) {
        User* u = it->second;
        u->dump(ofile);
    }
    ofile << "</users>\n";
}
