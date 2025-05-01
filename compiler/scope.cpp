#include "scope.h"
#include "def.h"
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>

void defineLibFunc(Scope& scope, std::string id, yytokentype returnType) {
    auto funcDefNode = FuncDefNode(returnType, id, nullptr, nullptr);
    auto func = std::make_shared<FuncDecl>(returnType, id, funcDefNode);
    func->paramList = std::make_shared<std::vector<std::shared_ptr<VarDecl>>>();
    scope.addFunc(id, func);
}

void addLibFuncArg(Scope& scope, std::string id, std::shared_ptr<SysyType> type, std::string argId) {
    auto param = std::make_shared<VarDecl>(argId, TypeValue(type));
    auto func = scope.findFunc(id);
    if (func) {
        func->paramList->push_back(param);
    }
}

Scope::Scope() {
    defineLibFunc(*this, "getint", INT);
    defineLibFunc(*this, "getch", INT);
    defineLibFunc(*this, "getarray", INT);
        addLibFuncArg(*this, "getarray", std::make_shared<ArrayType>(std::make_shared<SimpleType>(SysyType::IntegerTyID)), "array");
    defineLibFunc(*this, "putint", VOID);
        addLibFuncArg(*this, "putint", std::make_shared<SimpleType>(SysyType::IntegerTyID), "value");
    defineLibFunc(*this, "putch", VOID);
        addLibFuncArg(*this, "putch", std::make_shared<SimpleType>(SysyType::IntegerTyID), "value");
    defineLibFunc(*this, "putarray", VOID);
        addLibFuncArg(*this, "putarray", std::make_shared<ArrayType>(std::make_shared<SimpleType>(SysyType::IntegerTyID)), "array");

}

Scope::~Scope() {}

void Scope::enterBlock() {
    currentTable.push(std::set<std::string>());
}

void Scope::exitBlock() {
    for (const auto& id : currentTable.top()) {
        localTable.erase(id);
    }
    currentTable.pop();
}

void Scope::addGlobalVar(std::string id, std::shared_ptr<VarDecl> var) {
    if (globalTable.find(id) != globalTable.end()) {
        *output.err << "Error: Variable " << id << " already declared globally." << std::endl;
        return;
    }
    globalTable[id] = var;
}

void Scope::addVar(std::string id, std::shared_ptr<VarDecl> var, bool replace) {
    if (localTable.find(id) != localTable.end()) {
        if(!replace){
            *output.err << "Error: Variable " << id << " already declared in this scope." << std::endl;
            return;
        } else {
            localTable[id] = var;
        }
    } else {
        currentTable.top().insert(id);
        localTable[id] = var;        
    }

}

void Scope::addFunc(std::string id, std::shared_ptr<FuncDecl> func) {
    if (funcTable.find(id) != funcTable.end()) {
        
        *output.err << "Error: Function " << id << " already declared." << std::endl;
        return;
    }
    funcTable[id] = func;
}

std::shared_ptr<VarDecl> Scope::findVar(std::string id) {
    if (localTable.find(id) != localTable.end()) {
        return localTable[id];
    }
    if (globalTable.find(id) != globalTable.end()) {
        return globalTable[id];
    }
    return nullptr;
}

std::shared_ptr<FuncDecl> Scope::findFunc(std::string id) {
    if (funcTable.find(id) != funcTable.end()) {
        return funcTable[id];
    }
    return nullptr;
}