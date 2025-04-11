#include "def.h"
#include "AST.h"
#include "displayAST.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

void DisplayASTVisitor::visit(ExprNode &node) {
    *output.log << "ExprNode: op=" << node.op << std::endl;
    if (node.val1) node.val1->accept(*this);
    if (node.val2) node.val2->accept(*this);
}

void DisplayASTVisitor::visit(SimpleTokenNode &node) {
    *output.log << "SimpleTokenNode: type=" << node.type << std::endl;
}

void DisplayASTVisitor::visit(IdentifierNode &node) {
    *output.log << "IdentifierNode: id=" << node.getId() << std::endl;
}

void DisplayASTVisitor::visit(FuncCallNode &node) {
    *output.log << "FuncCallNode: id=" << node.id << std::endl;
    if (node.param) node.param->accept(*this);
}

void DisplayASTVisitor::visit(FuncCallParamNode &node) {
    *output.log << "FuncCallParamNode: params=" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void DisplayASTVisitor::visit(ParamNode &node) {
    *output.log << "ParamNode: type=" << node.type << ", id=" << node.id << ", isptr=" << node.isptr << std::endl;
    if (node.arraySize) node.arraySize->accept(*this);
}

void DisplayASTVisitor::visit(ParamListNode &node) {
    *output.log << "ParamListNode: params=" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void DisplayASTVisitor::visit(CompUnitNode &node) {
    *output.log << "CompUnitNode: definitions=" << std::endl;
    for (auto &def : node.deflist) {
        def->accept(*this);
    }
}

void DisplayASTVisitor::visit(BlockGroupNode &node) {
    *output.log << "BlockGroupNode: blocks=" << std::endl;
    for (auto &block : node.blocklist) {
        block->accept(*this);
    }
}

void DisplayASTVisitor::visit(LvalNode &node) {
    *output.log << "LvalNode: id=" << node.getId() << std::endl;
    if (node.arrayIndex) node.arrayIndex->accept(*this);
}

void DisplayASTVisitor::visit(IfElseNode &node) {
    *output.log << "IfElseNode: condition=" << std::endl;
    if (node.cond) node.cond->accept(*this);
    *output.log << "If branch:" << std::endl;
    if (node.ifstmt) node.ifstmt->accept(*this);
    if (node.elsestmt) {
        *output.log << "Else branch:" << std::endl;
        node.elsestmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(WhileNode &node) {
    *output.log << "WhileNode: condition=" << std::endl;
    if (node.cond) node.cond->accept(*this);
    *output.log << "Body:" << std::endl;
    if (node.stmt) node.stmt->accept(*this);
}

void DisplayASTVisitor::visit(BreakNode &node) {
    *output.log << "BreakNode" << std::endl;
}

void DisplayASTVisitor::visit(ContinueNode &node) {
    *output.log << "ContinueNode" << std::endl;
}

void DisplayASTVisitor::visit(ReturnNode &node) {
    *output.log << "ReturnNode: expr=" << std::endl;
    if (node.expr) node.expr->accept(*this);
}

void DisplayASTVisitor::visit(FuncDefNode &node) {
    *output.log << "FuncDefNode: type=" << node.type << ", id=" << node.id << std::endl;
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
    *output.log << "StmtListNode: statements=" << std::endl;
    for (auto &stmt : node.stmtlist) {
        stmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(AssignNode &node) {
    *output.log << "AssignNode: left=" << std::endl;
    if (node.left) node.left->accept(*this);
    *output.log << "Expression:" << std::endl;
    if (node.expr) node.expr->accept(*this);
}

void DisplayASTVisitor::visit(VectorNode &node) {
    *output.log << "vectorNode: elements=" << std::endl;
    for (auto &element : node.list) {
        element->accept(*this);
    }
}

void DisplayASTVisitor::visit(DeclNode &node) {
    *output.log << "DeclNode: isConst=" << node.isConst << ", type=" << node.type << ", id=" << node.id << std::endl;
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
    *output.log << "ConstIntNode: value=" << node.val << std::endl;
}

void DisplayASTVisitor::visit(ConstFloatNode &node) {
    *output.log << "ConstFloatNode: value=" << node.val << std::endl;
}

