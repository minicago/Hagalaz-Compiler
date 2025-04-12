#include "def.h"
#include "displayAST.h"
#include "checker.h"
#include "AST.h"
#include "output.h"

int __main(){
    if (AST_root == nullptr) {
        *output.err << "Error: AST root is null." << std::endl;
        return -1;
    }
    *output.log << std::dynamic_pointer_cast<CompUnitNode> (AST_root)->deflist.size() << std::endl;
    *output.log << "Starting the compiler?" << std::endl;
    DisplayASTVisitor display;
    AST_root->accept(display);
    Checker check;
    AST_root->accept(check);
    return 0;

}