
%locations
%{ 
    #include <iostream>
    #include<ctype.h>
    #include "def.h"
    #include "AST.h"
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
            
            $$ = std::make_shared<CompUnitNode>();
            AST_root = $$;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($1);
        }
        | CompUnit FuncDef {
            $$ = $1;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($2);
        }
        | 
        Decl {
            $$ = std::make_shared<CompUnitNode>();
            AST_root = $$;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDecl(($1));
        }
        | CompUnit Decl {
            $$ = $1;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDecl($2);
        }

Decl: ConstDecl
     |VarDecl

ConstDecl: CONST BType {
            decl_type = std::dynamic_pointer_cast<SimpleTokenNode>($2)->getType();
            $$ = std::make_shared<CompUnitNode>();
        } ConstDef ";" 
          |ConstDecl "," ConstDef {
            $$ = $1;
            std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($3);
          }

 
BType: INT 
     | FLOAT
     | VOID

ConstDef: Ident ArrayList ASSIGN InitVal {
            $$ = std::make_shared<DeclNode>(true, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, $2, $4);
        }
        | Ident ASSIGN InitVal{
            $$ = std::make_shared<DeclNode>(true, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr, $3);
        }

InitVal : Exp
        | "{" "}" {$$ = nullptr;}
        | "{" InitValGroup "}" {
            $$ = $2;
        }

InitValGroup: InitVal {
    $$ = std::make_shared<VectorNode> ();
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($1);
}| InitValGroup "," InitVal {
    $$ = $1;
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($3);    
}

VarDecl : BType VarDefGroup ";" {
    decl_type = std::dynamic_pointer_cast<SimpleTokenNode>($1)->getType();
    $$ = $2;
}

VarDefGroup: VarDef {
    $$ = std::make_shared<CompUnitNode>();
    std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($1);
}| VarDefGroup "," VarDef{
    $$ = $1;
    std::dynamic_pointer_cast<CompUnitNode>($$)->addDef($3);
}

VarDef : Ident {
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr, nullptr);
}| Ident ASSIGN InitVal {
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr, $3);
}| Ident ArrayList {
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, $2, nullptr);
}| Ident ArrayList ASSIGN InitVal {
    $$ = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>($1)->id, $2, $4);
}

ArrayList: "[" Exp "]"{
    $$ = std::make_shared<VectorNode> ();
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($2);
} | ArrayList "[" Exp "]" {
    $$ = $1;
    std::dynamic_pointer_cast<VectorNode> ($$)->addNode($3);  
}

FuncDef : BType Ident "(" ")" Block{
    $$ = std::make_shared<FuncDefNode> (
        std::dynamic_pointer_cast<SimpleTokenNode>($1)->type,
        std::dynamic_pointer_cast<IdentifierNode>($2)->id,
        nullptr,
        $5 );
} | BType Ident "(" FuncFParams ")" Block{
    $$ = std::make_shared<FuncDefNode> (
        std::dynamic_pointer_cast<SimpleTokenNode>($1)->type,
        std::dynamic_pointer_cast<IdentifierNode>($2)->id,
        $5,
        $6 );    
}

FuncFParams : FuncFParam {
    $$ = std::make_shared<ParamListNode> ();
    std::dynamic_pointer_cast<ParamListNode> ($$)->addParam($1);
} | FuncFParams "," FuncFParam {
    $$ = $1;
    std::dynamic_pointer_cast<ParamListNode> ($$)->addParam($3);
}

FuncFParam: BType Ident{
    $$ = std::make_shared<ParamNode> (std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, std::dynamic_pointer_cast<IdentifierNode>($2)->id, false, nullptr);
} | BType Ident '[' ']' {
    $$ = std::make_shared<ParamNode> (std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, std::dynamic_pointer_cast<IdentifierNode>($2)->id, true, nullptr);
} | BType Ident '[' ']' ArrayList {
    $$ = std::make_shared<ParamNode> (std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, std::dynamic_pointer_cast<IdentifierNode>($2)->id, true, $5);
}

Block : "{" "}" {$$ = nullptr;}| "{" BlockGroup "}" {$$ = $2;}

BlockGroup: BlockItem {
    $$ = std::make_shared<BlockGroupNode> ();
    std::dynamic_pointer_cast<BlockGroupNode> ($$)->addBlock($1);
}| BlockGroup BlockItem{
    $$ = $1;
    std::dynamic_pointer_cast<BlockGroupNode> ($$)->addBlock($2);
}

BlockItem : Decl | Stmt

Stmt :  LVal "=" Exp ";"{$$ = std::make_shared<AssignNode> ($1, $3);}
	| ";"  {$$ = nullptr;}
	| Exp ";" {$$ = $1;}
	| Block {$$ = $1;}
	| IF "(" Cond ")" Stmt {$$ = std::make_shared<IfElseNode> ($3, $5, nullptr);} 
	| IF "(" Cond ")" Stmt ELSE Stmt {$$ = std::make_shared<IfElseNode> ($3, $5, $7);}
	| WHILE "(" Cond ")" Stmt {$$ = std::make_shared<WhileNode>($3, $5);}
	| BREAK ";" {$$ = std::make_shared<BreakNode>(); }
	| CONTINUE ";" {$$ = std::make_shared<ContinueNode>(); }
	| RETURN ";" {$$ = std::make_shared<ReturnNode>(nullptr);}
	| RETURN Exp ";" {$$ = std::make_shared<ReturnNode>($2);} 

Exp : AddExp {$$ = $1;}

Cond : LOrExp {$$ = $1;}

LVal : Ident{
    $$ = std::make_shared<LvalNode> (std::dynamic_pointer_cast<IdentifierNode> ($1)->id, nullptr);
} | Ident ArrayList {
    $$ = std::make_shared<LvalNode> (std::dynamic_pointer_cast<IdentifierNode> ($1)->id, $2);
}

Number : INTNUM 
       | FLOATNUM

PrimaryExp : "(" Exp ")" {$$ = $2;}
           | LVal 
           | Number

UnaryExp : PrimaryExp
         | Ident "(" ")" {$$ = std::make_shared<FuncCallNode> (std::dynamic_pointer_cast<IdentifierNode>($1)->id, nullptr);} 
         | Ident "(" FuncParamsGroup ")"  {$$ = std::make_shared<FuncCallNode> (std::dynamic_pointer_cast<IdentifierNode>($1)->id, $3);}
         | UnaryOp UnaryExp {$$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($1)->type, $2, nullptr);}

UnaryOp : ADD
        | SUB 
        | NOT 

FuncParamsGroup: Exp {
    $$ = std::make_shared<FuncCallParamNode> ();
    std::dynamic_pointer_cast<FuncCallParamNode> ($$)->addParam($1);    
}
| FuncParamsGroup "," Exp{
    $$ = $1;
    std::dynamic_pointer_cast<FuncCallParamNode> ($$)->addParam($2);   
}

MulExp : UnaryExp
       | MulExp MUL UnaryExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | MulExp DIV UnaryExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | MulExp MOD UnaryExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

AddExp : MulExp
       | AddExp ADD MulExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       | AddExp SUB MulExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

RelExp : AddExp
       | RelExp LT AddExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       |RelExp GT AddExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       |RelExp LE AddExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }
       |RelExp GE AddExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

EqExp : RelExp | EqExp EQ RelExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }| EqExp NE RelExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

LAndExp : EqExp | LAndExp AND EqExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

LOrExp : LAndExp | LOrExp OR LAndExp {
            $$ =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>($2)->type, $1, $3);
       }

%%

#include "displayAST.h"

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
    DisplayASTVisitor display;
    AST_root->accept(display);
    return 0;
}

int yyerror(char* s)
{
    return 0;
}