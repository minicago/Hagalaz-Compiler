#ifndef SCOPE_H
#define SCOPE_H
#include "def.h"
#include <map>
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <optional>



class Decl{
public:
    yytokentype type;
    std::string id;
    bool isptr;
    std::optional<std::shared_ptr<ConstChunk> >initval;
    std::optional<std::shared_ptr<IntList> >arraySize;
    std::optional<Var> var;
    std::optional<std::vector<Decl> > param;

    Decl(std::string id, yytokentype type, bool isptr = false) 
        : id(id), type(type), isptr(isptr){}

    virtual ~Decl() = default;

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