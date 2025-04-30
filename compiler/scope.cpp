#include "scope.h"
#include "def.h"
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>



Scope::Scope() {}

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