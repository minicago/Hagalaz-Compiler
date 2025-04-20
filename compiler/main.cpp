#include "def.h"
#include "displayAST.h"
#include "genIR.h"
#include "AST.h"
#include "output.h"
#include "lir.h"

int __main(){
    if (AST_root == nullptr) {
        *output.err << "Error: AST root is null." << std::endl;
        return -1;
    }
    *output.log << std::dynamic_pointer_cast<CompUnitNode> (AST_root)->deflist.size() << std::endl;
    *output.log << "Starting the compiler?" << std::endl;
    DisplayASTVisitor display;
    AST_root->accept(display);
    GenIR genIR;
    AST_root->accept(genIR);
    *output.output<< genIR.builder.toString() << std::endl;
    LIRBuilder lirBuilder(*genIR.builder.module);
    lirBuilder.buildLIR();
    *output.output << lirBuilder.lirModule.toString() << std::endl;
    return 0;

}