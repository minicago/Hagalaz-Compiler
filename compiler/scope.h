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
#include "AST.h"

class VarDecl{
public:
    std::shared_ptr<Node> node;
    std::string id;


    TypeValue typeValue;
    

    VarDecl(std::string id, TypeValue typeValue, DeclNode& node)
        : id(id), node(std::make_shared<DeclNode> (node)), typeValue(typeValue) {}
    
    VarDecl(std::string id, TypeValue typeValue, ParamNode& node)
        : id(id), node(std::make_shared<ParamNode> (node)), typeValue(typeValue) {}


};

class FuncDecl{
public:
    std::shared_ptr<Node> node;
    std::shared_ptr<SysyType> returnType;
    std::string id;
    std::shared_ptr<std::vector<std::shared_ptr<VarDecl> > > paramList;
    std::shared_ptr<Node> stmt;
    FuncDecl(yytokentype returnType, std::string id, FuncDefNode& node)
        : returnType(std::make_shared<SimpleType>(returnType)), id(id), node(std::make_shared<FuncDefNode> (node)), paramList(std::make_shared<std::vector<std::shared_ptr<VarDecl> > >()), stmt(nullptr) {}
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