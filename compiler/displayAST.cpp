#include "def.h"
#include "AST.h"
#include "displayAST.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

void DisplayASTVisitor::visit(ExprNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.val1) node.val1->accept(*this);
    if (node.val2) node.val2->accept(*this);
}

void DisplayASTVisitor::visit(SimpleTokenNode &node) {
    *output.log << node.toString() << std::endl;
}

void DisplayASTVisitor::visit(IdentifierNode &node) {
    *output.log << node.toString() << std::endl;
}

void DisplayASTVisitor::visit(FuncCallNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.param) node.param->accept(*this);
}

void DisplayASTVisitor::visit(FuncCallParamNode &node) {
    *output.log << node.toString() << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void DisplayASTVisitor::visit(ParamNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.arraySize) node.arraySize->accept(*this);
}

void DisplayASTVisitor::visit(ParamListNode &node) {
    *output.log << node.toString() << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void DisplayASTVisitor::visit(CompUnitNode &node) {
    *output.log << node.toString() << std::endl;
    for (auto &def : node.deflist) {
        def->accept(*this);
    }
}

void DisplayASTVisitor::visit(BlockGroupNode &node) {
    *output.log << node.toString() << std::endl;
    for (auto &block : node.blocklist) {
        block->accept(*this);
    }
}

void DisplayASTVisitor::visit(LvalNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.arrayIndex) node.arrayIndex->accept(*this);
}

void DisplayASTVisitor::visit(IfElseNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.cond) node.cond->accept(*this);
    *output.log << "If branch:" << std::endl;
    if (node.ifstmt) node.ifstmt->accept(*this);
    if (node.elsestmt) {
        *output.log << "Else branch:" << std::endl;
        node.elsestmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(WhileNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.cond) node.cond->accept(*this);
    *output.log << "Body:" << std::endl;
    if (node.stmt) node.stmt->accept(*this);
}

void DisplayASTVisitor::visit(BreakNode &node) {
    *output.log << node.toString() << std::endl;
}

void DisplayASTVisitor::visit(ContinueNode &node) {
    *output.log << node.toString() << std::endl;
}

void DisplayASTVisitor::visit(ReturnNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.expr) node.expr->accept(*this);
}

void DisplayASTVisitor::visit(FuncDefNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.param) {
        *output.log << "Parameters:" << std::endl;
        node.param->accept(*this);
    }
    if (node.stmt) {
        *output.log << "Body:" << std::endl;
        node.stmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(StmtListNode &node) {
    *output.log << node.toString() << std::endl;
    for (auto &stmt : node.stmtlist) {
        stmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(AssignNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.left) node.left->accept(*this);
    *output.log << "Expression:" << std::endl;
    if (node.expr) node.expr->accept(*this);
}

void DisplayASTVisitor::visit(VectorNode &node) {
    *output.log << node.toString() << std::endl;
    for (auto &element : node.list) {
        element->accept(*this);
    }
}

void DisplayASTVisitor::visit(DeclNode &node) {
    *output.log << node.toString() << std::endl;
    if (node.arraySize) {
        *output.log << "Array size:" << std::endl;
        node.arraySize->accept(*this);
    }
    if (node.initval) {
        *output.log << "Initial value:" << std::endl;
        node.initval->accept(*this);
    }
}

void DisplayASTVisitor::visit(ConstIntNode &node) {
    *output.log << node.toString() << std::endl;
}

void DisplayASTVisitor::visit(ConstFloatNode &node) {
    *output.log << node.toString() << std::endl;
}

