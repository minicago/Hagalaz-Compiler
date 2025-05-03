#include "def.h"
#include "displayAST.h"
#include "genIR.h"
#include "AST.h"
#include "output.h"
#include "lir.h"

#include <unistd.h>

int __main(int argc, char** argv){

    extern FILE* yyin;

    const char* optstring = "o:";

    char *filename = nullptr;
    int print_ir = false;
    int print_asm = false;
  
    std::string outputFile = "";
  
    int opt;
    bool isO2 = false;
    while ((opt = getopt(argc, argv, "Sco:O::")) != -1) {
      switch (opt) {
      case 'S':
        print_asm = true;
        print_ir = false;
        break;
      case 'c':
        print_ir = true;
        print_asm = false;
        break;
      case 'o':
      outputFile = optarg;
        break;
      case 'O':
        isO2 = true;
        break;
      default:
        break;
      }
    }
    filename = argv[optind];

    yyin = fopen(filename, "r");
    if (yyin == nullptr) {
      std::cout << "yyin open" << filename << "failed" << std::endl;
      return -1;
    }

    // if(argc == 2){
    //     if((yyin = fopen(argv[1], "r")) == NULL){
    //         printf("Can't open file %s\n", argv[1]);
    //         return 1;
    //     }
    // }
    yyparse();

    
    
	fclose(yyin);


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
    *output.log<< genIR.builder.toString() << std::endl;
    LIRBuilder lirBuilder(*genIR.builder.module);



    lirBuilder.buildLIR();
    output.setOutput(outputFile);

    if (print_ir) {
        *output.output << genIR.builder.toString() << std::endl;
    }
    if (print_asm) {
        *output.output << lirBuilder.lirModule.toString() << std::endl;
    }

    return 0;

}