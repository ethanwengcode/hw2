#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    
    void addProduct(Product* product);
    void addUser(User* user);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    
    // Shopping cart functions
    void addToCart(const std::string& username, Product* product);
    void viewCart(const std::string& username);
    void buyCart(const std::string& username);

private:
    std::vector<Product*> products_;
    std::unordered_map<std::string, User*> users_;
    std::unordered_map<std::string, std::set<Product*>> keywordMap_;
    std::unordered_map<std::string, std::queue<Product*>> userCart_;
};

#endif
