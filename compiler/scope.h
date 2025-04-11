#ifndef SCOPE_H
#define SCOPE_H
#include "def.h"
#include <map>
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <set>
#include <optional>
#include <stack>

#include "type.h"

class VarDecl{
public:
    std::string id;
    
    TypeValue typeValue;

    VarDecl(std::string id, TypeValue typeValue)
        : id(id), typeValue(typeValue) {}


};

class FuncDecl{
public:
    SimpleType returnType;
    std::string id;
    std::shared_ptr<std::vector<std::shared_ptr<VarDecl> > > paramList;
    std::shared_ptr<Node> stmt;
    FuncDecl(yytokentype returnType, std::string id)
        : returnType(returnType), id(id), paramList(std::make_shared<std::vector<std::shared_ptr<VarDecl> > >()), stmt(nullptr) {}
};

class Scope{
public:

    std::map<std::string, std::shared_ptr<FuncDecl> > funcTable;
    std::map<std::string, std::shared_ptr<VarDecl> > globalTable;
    std::map<std::string, std::shared_ptr<VarDecl> > localTable;

    std::stack<std::set<std::string> > currentTable;
    
    void enterBlock();
    void exitBlock();
    void addGlobalVar(std::string id, std::shared_ptr<VarDecl> var);
    void addVar(std::string id, std::shared_ptr<VarDecl> var);
    void addFunc(std::string id, std::shared_ptr<FuncDecl> func);
    std::shared_ptr<VarDecl> findVar(std::string id);
    std::shared_ptr<FuncDecl> findFunc(std::string id);

    Scope();
    ~Scope();
};



#endif