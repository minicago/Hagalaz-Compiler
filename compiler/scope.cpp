#include "scope.h"
#include "def.h"
#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <vector>


bool Scope::addDecl(std::shared_ptr<Decl> decl) {
    if (currentScope->historyTable.find(decl->id) != currentScope->historyTable.end()) {
        std::cerr << "Error: Variable " << decl->id << " already declared in the current scope." << std::endl;
        return false;
    }
    if (currentTable.find(decl->id) != currentTable.end()) {
        currentScope->historyTable[decl->id] = currentTable[decl->id];
    } else {
        currentScope->historyTable[decl->id] = nullptr;
    }
    currentTable[decl->id] = decl;
    return true;
}

std::shared_ptr<Decl> Scope::getScope(std::string id) {
    if (currentTable.find(id) != currentTable.end()) {
        return currentTable[id];
    }
    return nullptr;
}

void Scope::enterScope() {
    currentScope = std::make_shared<Scope> (currentScope);
}

void Scope::exitScope() {
    for (auto &decl : currentScope->historyTable) {
        if (decl.second != nullptr) {
            currentTable[decl.first] = decl.second;
        } else {
            currentTable.erase(decl.first);
        }
    }
    currentScope = currentScope->parentScope;
}

