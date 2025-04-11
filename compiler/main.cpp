#include "def.h"
#include "displayAST.h"
#include "checker.h"
#include "AST.h"

int __main(){
    DisplayASTVisitor display;
    AST_root->accept(display);
    Checker check;
    AST_root->accept(check);
    return 0;

}