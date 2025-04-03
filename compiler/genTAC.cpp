#include "genTAC.h"
#include "AST.h"
#include <iostream>
#include "scope.h"
#include "output.h"
#include "tool.h"

void GenTACVisitor::visit(ExprNode &node) {
    *output.log << "Generating TAC for ExprNode: op=" << node.op << std::endl;
    if (node.val1) node.val1->accept(*this);
    if (node.val2) node.val2->accept(*this);
}

void GenTACVisitor::visit(IfElseNode &node) {
    *output.log << "Generating TAC for IfElseNode" << std::endl;
    if (node.cond) node.cond->accept(*this);
    if (node.ifstmt) node.ifstmt->accept(*this);
    if (node.elsestmt) node.elsestmt->accept(*this);
}

void GenTACVisitor::visit(WhileNode &node) {
    *output.log << "Generating TAC for WhileNode" << std::endl;
    if (node.cond) node.cond->accept(*this);
    if (node.stmt) node.stmt->accept(*this);
}

void GenTACVisitor::visit(BreakNode &node) {
    *output.log << "Generating TAC for BreakNode" << std::endl;
}

void GenTACVisitor::visit(ContinueNode &node) {
    *output.log << "Generating TAC for ContinueNode" << std::endl;
}

void GenTACVisitor::visit(ReturnNode &node) {
    *output.log << "Generating TAC for ReturnNode" << std::endl;
    if (node.expr) node.expr->accept(*this);
}

void GenTACVisitor::visit(FuncDefNode &node) {
    *output.log << "Generating TAC for FuncDefNode: id=" << node.id << std::endl;
    if (node.param) node.param->accept(*this);
    if (node.stmt) node.stmt->accept(*this);
}

void GenTACVisitor::visit(FuncCallNode &node) {
    *output.log << "Generating TAC for FuncCallNode: id=" << node.id << std::endl;
    if (node.param) node.param->accept(*this);
}

void GenTACVisitor::visit(ParamNode &node) {
    *output.log << "Generating TAC for ParamNode: id=" << node.id << std::endl;
    if (node.arraySize) node.arraySize->accept(*this);
}

void GenTACVisitor::visit(ParamListNode &node) {
    *output.log << "Generating TAC for ParamListNode" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void GenTACVisitor::visit(FuncCallParamNode &node) {
    *output.log << "Generating TAC for FuncCallParamNode" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void GenTACVisitor::visit(CompUnitNode &node) {
    *output.log << "Generating TAC for CompUnitNode" << std::endl;
    for (auto &def : node.deflist) {
        def->accept(*this);
    }
}

void GenTACVisitor::visit(StmtListNode &node) {
    *output.log << "Generating TAC for StmtListNode" << std::endl;
    for (auto &stmt : node.stmtlist) {
        stmt->accept(*this);
    }
}

void GenTACVisitor::visit(AssignNode &node) {
    *output.log << "Generating TAC for AssignNode" << std::endl;
    if (node.left) node.left->accept(*this);
    if (node.expr) node.expr->accept(*this);
}

void GenTACVisitor::visit(vectorNode &node) {
    *output.log << "Generating TAC for vectorNode" << std::endl;
    for (auto &element : node.list) {
        element->accept(*this);
    }
}

void GenTACVisitor::visit(DeclNode &node) {
    std::shared_ptr<SemaChunck> arraySizeSema = nullptr, initvalSema = nullptr;
    *output.log << "Generating TAC for DeclNode: id=" << node.id << std::endl;
    
    if (node.arraySize) {
        node.arraySize->accept(*this);
        arraySizeSema = semaChunk;
        if (arraySizeSema->initval) {
            *output.log << "DeclNode has array size" << std::endl;
            // Handle array size initialization
        } else {
            *output.err << "Array size is not const" << std::endl;
            return;
        }
    }
    if (node.initval) {
        node.initval->accept(*this);
        initvalSema = semaChunk;
    }

    if (node.isConst) {
        *output.log << "DeclNode is constant" << std::endl;
        if (initvalSema) {
            if (initvalSema->initval) {
                *output.log << "DeclNode has initial value" << std::endl;
                // Handle constant initialization
                
            } else {
                *output.err << "Constant declaration without initial value" << std::endl;
                return;
            }
        } else {
            *output.err << "Array size is not initialized" << std::endl;
            return;
        }
    }
    std::shared_ptr<Decl> decl = 
        std::make_shared<Decl>(node.id, node.type, false, node.isConst);

    decl->arraySize = makeIntList( * (*arraySizeSema->initval) );

    if (not matchArraysize(* (*decl->arraySize), *(*initvalSema->initval))){
        *output.err << "Array size not matched" << std::endl;
        return;
    }

    if (node.isConst) {
        decl->initval = initvalSema->initval;
    }

    Scope::addDecl(decl);

        
    
}

void GenTACVisitor::visit(ConstIntNode &node) {
    *output.log << "Generating TAC for ConstIntNode: value=" << node.val << std::endl;
}

void GenTACVisitor::visit(ConstFloatNode &node) {
    *output.log << "Generating TAC for ConstFloatNode: value=" << node.val << std::endl;
}

void GenTACVisitor::visit(IdentifierNode &node) {
    *output.log << "Generating TAC for IdentifierNode: id=" << node.id << std::endl;

}

void GenTACVisitor::visit(SimpleTokenNode &node) {
    *output.log << "Generating TAC for SimpleTokenNode: type=" << node.type << std::endl;
}

void GenTACVisitor::visit(BlockGroupNode &node) {
    *output.log << "Generating TAC for BlockGroupNode" << std::endl;
    Scope::enterScope();
    for (auto &block : node.blocklist) {
        block->accept(*this);
    }
    Scope::exitScope();
}

void GenTACVisitor::visit(LvalNode &node) {
    *output.log << "Generating TAC for LvalNode: id=" << node.id << std::endl;
    if (node.arrayIndex) node.arrayIndex->accept(*this);
}
