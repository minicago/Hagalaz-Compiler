#ifndef SCOPE_H
#define SCOPE_H
#include "def.h"
#include <map>
#include <string>
#include <memory>

class Decl{
public:
    yytokentype type;
    std::string id;
    bool isptr;
    bool isfunc;
    std::shared_ptr<Node> arraySize;


};


class Scope{
private:
    static std::map<std::string, std::shared_ptr<Decl> > currentTable;
    static std::shared_ptr<Scope> currentScope;
    std::map<std::string, std::shared_ptr<Decl> > historyTable;
    std::shared_ptr<Scope> parentScope;

public:
    Scope() = default;
    Scope(std::shared_ptr<Scope> parentScope) : parentScope(parentScope) {}

    static bool addDecl(std::shared_ptr<Decl> decl);
    static std::shared_ptr<Decl> getScope(std::string id);
    static void enterScope() ;
    static void exitScope() ;
};

#endif