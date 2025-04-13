
%locations
%{ 
    #include <iostream>
    #include<ctype.h>
    #include "def.h"
    #include "AST.h"
    #define __SHOW__BISON__ACTION__
    #ifdef __SHOW__BISON__ACTION__ 
        #define BISON_LOG(X) printf(X)
    #else
        #define BISON_LOG(X)  
    #endif
    int yylex();			//调用词法分析器，每次返回一个TOKEN
    int yyerror(char* s);   
    extern int line_no;
    extern yytokentype decl_type;
    extern std::shared_ptr<Node> AST_root;
%}

%token ASSIGN "=" 
%token LT 
%token LE 
%token GT 
%token GE 
%token EQ 
%token NE 
%token ADD "+"
%token SUB "-"
%token MUL "*" 
%token DIV "/" 
%token MOD "%"
%token NOT "!"
%token SEMI ";"
%token COLON ":" 
%token COMMA  ","
%token OB "{" 
%token CB "}"
%token LB "["
%token RB "]"
%token L "("
%token R ")"
%token CONST 
%token IF 
%token ELSE 
%token WHILE 
%token BREAK 
%token RETURN 
%token CONTINUE 
%token AND 
%token OR
%token const_String_Val Ident
%token INT
%token FLOAT
%token VOID
%token const_Int_Val INTNUM 
%token const_Float_Val FLOATNUM
 
%start CompUnit


%%
CompUnit: FuncDef { 
            BISON_LOG("CompUnit -> FuncDef\n");
            $$ = std::make_shared<CompUnitNode>();
            AST_root = $$;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($1);
        }
        | CompUnit FuncDef {
            BISON_LOG("CompUnit -> CompUnit FuncDef\n");
            $$ = $1;
            AST_root = $$;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($2);
        }
        | Decl {
            BISON_LOG("CompUnit -> Decl\n");
            $$ = std::make_shared<CompUnitNode>();
            AST_root = $$;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDef(($1));
        }
        | CompUnit Decl {
            BISON_LOG("CompUnit -> CompUnit Decl\n");
            $$ = $1;
            AST_root = $$;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($2);
        }

Decl: ConstDecl {
        BISON_LOG("Decl -> ConstDecl\n");
     }
     | VarDecl {
        BISON_LOG("Decl -> VarDecl\n");
     }

ConstDecl: CONST BType {
            BISON_LOG("ConstDecl -> CONST BType\n");
            decl_type = std::dynamic_pointer_cast<SimpleTokenNode>($2)->getType();
        } ConstDef ";" {
            BISON_LOG("ConstDecl -> CONST BType ConstDef ;\n");
            $$ = std::make_shared<StmtListNode>();
            std::dynamic_pointer_cast<StmtListNode>($$)->addStmt($4);
        }
          | ConstDecl "," ConstDef {
            BISON_LOG("ConstDecl -> ConstDecl , ConstDef\n");
            $$ = $1;
            std::dynamic_pointer_cast<StmtListNode>($$)->addStmt($3);
          }

BType: INT {
        BISON_LOG("BType -> INT\n");
     }
     | FLOAT {
        BISON_LOG("BType -> FLOAT\n");
     }
     | VOID {
        BISON_LOG("BType -> VOID\n");
     }

ConstDef: Ident ArrayList ASSIGN InitVal {
            BISON_LOG("ConstDef -> Ident ArrayList ASSIGN InitVal\n");
            $$ = std::make_shared<DeclNode>(true, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, $2, $4);
        }
        | Ident ASSIGN InitVal {
            BISON_LOG("ConstDef -> Ident ASSIGN InitVal\n");
            $$ = std::make_shared<DeclNode>(true, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr, $3);
        }

InitVal : Exp {
            BISON_LOG("InitVal -> Exp\n");
        }
        | "{" "}" {
            BISON_LOG("InitVal -> { }\n");
            $$ = nullptr;
        }
        | "{" InitValGroup "}" {
            BISON_LOG("InitVal -> { InitValGroup }\n");
            $$ = $2;
        }

InitValGroup: InitVal {
    BISON_LOG("InitValGroup -> InitVal\n");
    $$ = std::make_shared<VectorNode> ();
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($1);
}| InitValGroup "," InitVal {
    BISON_LOG("InitValGroup -> InitValGroup , InitVal\n");
    $$ = $1;
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($3);    
}

VarDecl : BType {
        BISON_LOG("VarDecl -> BType\n");
        decl_type = std::dynamic_pointer_cast<SimpleTokenNode>($1)->getType();
    } VarDefGroup ";" {
        BISON_LOG("VarDecl -> BType VarDefGroup ;\n");
        $$ = $3; 
}

VarDefGroup: VarDef {
    BISON_LOG("VarDefGroup -> VarDef\n");
    $$ = std::make_shared<StmtListNode>();
    std::dynamic_pointer_cast<StmtListNode>($$)->addStmt($1);
}| VarDefGroup "," VarDef {
    BISON_LOG("VarDefGroup -> VarDefGroup , VarDef\n");
    $$ = $1;
    std::dynamic_pointer_cast<StmtListNode>($$)->addStmt($3);
}

VarDef : Ident {
    BISON_LOG("VarDef -> Ident\n");
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr, nullptr);
}| Ident ASSIGN InitVal {
    BISON_LOG("VarDef -> Ident ASSIGN InitVal\n");
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr, $3);
}| Ident ArrayList {
    BISON_LOG("VarDef -> Ident ArrayList\n");
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, $2, nullptr);
}| Ident ArrayList ASSIGN InitVal {
    BISON_LOG("VarDef -> Ident ArrayList ASSIGN InitVal\n");
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, $2, $4);
}

ArrayList: "[" Exp "]" {
    BISON_LOG("ArrayList -> [ Exp ]\n");
    $$ = std::make_shared<VectorNode> ();
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($2);
} | ArrayList "[" Exp "]" {
    BISON_LOG("ArrayList -> ArrayList [ Exp ]\n");
    $$ = $1;
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($3);  
}

FuncDef : BType Ident "(" ")" Block {
    BISON_LOG("FuncDef -> BType Ident ( ) Block\n");
    $$ = std::make_shared<FuncDefNode> (
        std::dynamic_pointer_cast<SimpleTokenNode>($1)->type,
        std::dynamic_pointer_cast<IdentifierNode>($2)->id,
        nullptr,
        $5 );
} | BType Ident "(" FuncFParams ")" Block {
    BISON_LOG("FuncDef -> BType Ident ( FuncFParams ) Block\n");
    $$ = std::make_shared<FuncDefNode> (
        std::dynamic_pointer_cast<SimpleTokenNode>($1)->type,
        std::dynamic_pointer_cast<IdentifierNode>($2)->id,
        $4,
        $6 );    
}

FuncFParams : FuncFParam {
    BISON_LOG("FuncFParams -> FuncFParam\n");
    $$ = std::make_shared<ParamListNode> ();
    std::dynamic_pointer_cast<ParamListNode> ($$)->addParam($1);
} | FuncFParams "," FuncFParam {
    BISON_LOG("FuncFParams -> FuncFParams , FuncFParam\n");
    $$ = $1;
    std::dynamic_pointer_cast<ParamListNode> ($$)->addParam($3);
}

FuncFParam: BType Ident {
    BISON_LOG("FuncFParam -> BType Ident\n");
    $$ = std::make_shared<ParamNode> (std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, std::dynamic_pointer_cast<IdentifierNode>($2)->id, false, nullptr);
} | BType Ident "[" "]" {
    BISON_LOG("FuncFParam -> BType Ident [ ]\n");
    $$ = std::make_shared<ParamNode> ( std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, std::dynamic_pointer_cast<IdentifierNode>($2)->id, true, nullptr);
} | BType Ident "[" "]" ArrayList {
    BISON_LOG("FuncFParam -> BType Ident [ ] ArrayList\n");
    $$ = std::make_shared<ParamNode> (std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, std::dynamic_pointer_cast<IdentifierNode>($2)->id, true, $5);
}

Block : "{" "}" {
    BISON_LOG("Block -> { }\n");
    $$ = nullptr;
} | "{" BlockGroup "}" {
    BISON_LOG("Block -> { BlockGroup }\n");
    $$ = $2;
}

BlockGroup: BlockItem {
    BISON_LOG("BlockGroup -> BlockItem\n");
    $$ = std::make_shared<BlockGroupNode> ();
    std::dynamic_pointer_cast<BlockGroupNode> ($$)->addBlock($1);
}| BlockGroup BlockItem {
    BISON_LOG("BlockGroup -> BlockGroup BlockItem\n");
    $$ = $1;
    std::dynamic_pointer_cast<BlockGroupNode> ($$)->addBlock($2);
}

BlockItem : Decl {
    BISON_LOG("BlockItem -> Decl\n");
} | Stmt {
    BISON_LOG("BlockItem -> Stmt\n");
}

Stmt :  LVal "=" Exp ";" {
    BISON_LOG("Stmt -> LVal = Exp ;\n");
    $$ = std::make_shared<AssignNode> ($1, $3);
}
    | ";" {
        BISON_LOG("Stmt -> ;\n");
        $$ = nullptr;
    }
    | Exp ";" {
        BISON_LOG("Stmt -> Exp ;\n");
        $$ = $1;
    }
    | Block {
        BISON_LOG("Stmt -> Block\n");
        $$ = $1;
    }
    | IF "(" Cond ")" Stmt {
        BISON_LOG("Stmt -> IF ( Cond ) Stmt\n");
        $$ = std::make_shared<IfElseNode> ($3, $5, nullptr);
    } 
    | IF "(" Cond ")" Stmt ELSE Stmt {
        BISON_LOG("Stmt -> IF ( Cond ) Stmt ELSE Stmt\n");
        $$ = std::make_shared<IfElseNode> ($3, $5, $7);
    }
    | WHILE "(" Cond ")" Stmt {
        BISON_LOG("Stmt -> WHILE ( Cond ) Stmt\n");
        $$ = std::make_shared<WhileNode>($3, $5);
    }
    | BREAK ";" {
        BISON_LOG("Stmt -> BREAK ;\n");
        $$ = std::make_shared<BreakNode>();
    }
    | CONTINUE ";" {
        BISON_LOG("Stmt -> CONTINUE ;\n");
        $$ = std::make_shared<ContinueNode>();
    }
    | RETURN ";" {
        BISON_LOG("Stmt -> RETURN ;\n");
        $$ = std::make_shared<ReturnNode>(nullptr);
    }
    | RETURN Exp ";" {
        BISON_LOG("Stmt -> RETURN Exp ;\n");
        $$ = std::make_shared<ReturnNode>($2);
    }

Exp : AddExp {
    BISON_LOG("Exp -> AddExp\n");
    $$ = $1;
}

Cond : LOrExp {
    BISON_LOG("Cond -> LOrExp\n");
    $$ = $1;
}

LVal : Ident {
    BISON_LOG("LVal -> Ident\n");
    $$ = std::make_shared<LvalNode> (std::dynamic_pointer_cast<IdentifierNode> ($1)->id, nullptr);
} | Ident ArrayList {
    BISON_LOG("LVal -> Ident ArrayList\n");
    $$ = std::make_shared<LvalNode> (std::dynamic_pointer_cast<IdentifierNode> ($1)->id, $2);
}

Number : INTNUM {
    BISON_LOG("Number -> INTNUM\n");
} | FLOATNUM {
    BISON_LOG("Number -> FLOATNUM\n");
}

PrimaryExp : "(" Exp ")" {
    BISON_LOG("PrimaryExp -> ( Exp )\n");
    $$ = $2;
}
           | LVal {
    BISON_LOG("PrimaryExp -> LVal\n");
}
           | Number {
    BISON_LOG("PrimaryExp -> Number\n");
}

UnaryExp : PrimaryExp {
    BISON_LOG("UnaryExp -> PrimaryExp\n");
}
         | Ident "(" ")" {
    BISON_LOG("UnaryExp -> Ident ( )\n");
    $$ = std::make_shared<FuncCallNode> (std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr);
} 
         | Ident "(" FuncParamsGroup ")" {
    BISON_LOG("UnaryExp -> Ident ( FuncParamsGroup )\n");
    $$ = std::make_shared<FuncCallNode> (std::dynamic_pointer_cast<IdentifierNode>($1)->id, $3);
}
         | UnaryOp UnaryExp {
    BISON_LOG("UnaryExp -> UnaryOp UnaryExp\n");
    $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, nullptr, $2);
}

UnaryOp : ADD {
    BISON_LOG("UnaryOp -> ADD\n");
}
        | SUB {
    BISON_LOG("UnaryOp -> SUB\n");
}
        | NOT {
    BISON_LOG("UnaryOp -> NOT\n");
}

FuncParamsGroup: Exp {
    BISON_LOG("FuncParamsGroup -> Exp\n");
    $$ = std::make_shared<FuncCallParamNode> ();
    std::dynamic_pointer_cast<FuncCallParamNode> ($$)->addParam($1);    
}
| FuncParamsGroup "," Exp {
    BISON_LOG("FuncParamsGroup -> FuncParamsGroup , Exp\n");
    $$ = $1;
    std::dynamic_pointer_cast<FuncCallParamNode> ($$)->addParam($2);   
}

MulExp : UnaryExp {
    BISON_LOG("MulExp -> UnaryExp\n");
}
       | MulExp MUL UnaryExp {
            BISON_LOG("MulExp -> MulExp MUL UnaryExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | MulExp DIV UnaryExp {
            BISON_LOG("MulExp -> MulExp DIV UnaryExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | MulExp MOD UnaryExp {
            BISON_LOG("MulExp -> MulExp MOD UnaryExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

AddExp : MulExp {
    BISON_LOG("AddExp -> MulExp\n");
}
       | AddExp ADD MulExp {
            BISON_LOG("AddExp -> AddExp ADD MulExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | AddExp SUB MulExp {
            BISON_LOG("AddExp -> AddExp SUB MulExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

RelExp : AddExp {
    BISON_LOG("RelExp -> AddExp\n");
}
       | RelExp LT AddExp {
            BISON_LOG("RelExp -> RelExp LT AddExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | RelExp GT AddExp {
            BISON_LOG("RelExp -> RelExp GT AddExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | RelExp LE AddExp {
            BISON_LOG("RelExp -> RelExp LE AddExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | RelExp GE AddExp {
            BISON_LOG("RelExp -> RelExp GE AddExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

EqExp : RelExp {
    BISON_LOG("EqExp -> RelExp\n");
} | EqExp EQ RelExp {
            BISON_LOG("EqExp -> EqExp EQ RelExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }| EqExp NE RelExp {
            BISON_LOG("EqExp -> EqExp NE RelExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

LAndExp : EqExp {
    BISON_LOG("LAndExp -> EqExp\n");
} | LAndExp AND EqExp {
            BISON_LOG("LAndExp -> LAndExp AND EqExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

LOrExp : LAndExp {
    BISON_LOG("LOrExp -> LAndExp\n");
} | LOrExp OR LAndExp {
            BISON_LOG("LOrExp -> LOrExp OR LAndExp\n");
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

%%

int main(int argc, char** argv){
    
    extern FILE* yyin;
    if(argc == 2){
	if((yyin = fopen(argv[1], "r")) == NULL){
	    printf("Can't open file %s\n", argv[1]);
	    return 1;
	}
    }
    yyparse();
    
	fclose(yyin);

    __main();

    
    return 0;
}

int yyerror(char* s)
{
    return 0;
}