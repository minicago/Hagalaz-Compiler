#include "def.h"
#include "AST.h"
#include "displayAST.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

void DisplayASTVisitor::visit(ExprNode &node) {
    std::cout << "ExprNode: op=" << node.op << std::endl;
    if (node.val1) node.val1->accept(*this);
    if (node.val2) node.val2->accept(*this);
}

void DisplayASTVisitor::visit(SimpleTokenNode &node) {
    std::cout << "SimpleTokenNode: type=" << node.type << std::endl;
}

void DisplayASTVisitor::visit(IdentifierNode &node) {
    std::cout << "IdentifierNode: id=" << node.getId() << std::endl;
}

void DisplayASTVisitor::visit(FuncCallNode &node) {
    std::cout << "FuncCallNode: id=" << node.id << std::endl;
    if (node.param) node.param->accept(*this);
}

void DisplayASTVisitor::visit(FuncCallParamNode &node) {
    std::cout << "FuncCallParamNode: params=" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void DisplayASTVisitor::visit(ParamNode &node) {
    std::cout << "ParamNode: type=" << node.type << ", id=" << node.id << ", isptr=" << node.isptr << std::endl;
    if (node.arraySize) node.arraySize->accept(*this);
}

void DisplayASTVisitor::visit(ParamListNode &node) {
    std::cout << "ParamListNode: params=" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
}

void DisplayASTVisitor::visit(CompUnitNode &node) {
    std::cout << "CompUnitNode: definitions=" << std::endl;
    for (auto &def : node.deflist) {
        def->accept(*this);
    }
}

void DisplayASTVisitor::visit(BlockGroupNode &node) {
    std::cout << "BlockGroupNode: blocks=" << std::endl;
    for (auto &block : node.blocklist) {
        if (block == nullptr) {
            std::cout << "BlockGroupNode: block is null" << std::endl;
            continue;
        }
        block->accept(*this);
    }
}

void DisplayASTVisitor::visit(LvalNode &node) {
    std::cout << "LvalNode: id=" << node.getId() << std::endl;
    if (node.arrayIndex) node.arrayIndex->accept(*this);
}

void DisplayASTVisitor::visit(IfElseNode &node) {
    std::cout << "IfElseNode: condition=" << std::endl;
    if (node.cond) node.cond->accept(*this);
    std::cout << "If branch:" << std::endl;
    if (node.ifstmt) node.ifstmt->accept(*this);
    if (node.elsestmt) {
        std::cout << "Else branch:" << std::endl;
        node.elsestmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(WhileNode &node) {
    std::cout << "WhileNode: condition=" << std::endl;
    if (node.cond) node.cond->accept(*this);
    std::cout << "Body:" << std::endl;
    if (node.stmt) node.stmt->accept(*this);
}

void DisplayASTVisitor::visit(BreakNode &node) {
    std::cout << "BreakNode" << std::endl;
}

void DisplayASTVisitor::visit(ContinueNode &node) {
    std::cout << "ContinueNode" << std::endl;
}

void DisplayASTVisitor::visit(ReturnNode &node) {
    std::cout << "ReturnNode: expr=" << std::endl;
    if (node.expr) node.expr->accept(*this);
}

void DisplayASTVisitor::visit(FuncDefNode &node) {
    std::cout << "FuncDefNode: type=" << node.type << ", id=" << node.id << std::endl;
    if (node.param) {
        std::cout << "Parameters:" << std::endl;
        node.param->accept(*this);
    }
    if (node.stmt) {
        std::cout << "Body:" << std::endl;
        node.stmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(StmtListNode &node) {
    std::cout << "StmtListNode: statements=" << std::endl;
    for (auto &stmt : node.stmtlist) {
        stmt->accept(*this);
    }
}

void DisplayASTVisitor::visit(AssignNode &node) {
    std::cout << "AssignNode: left=" << std::endl;
    if (node.left) node.left->accept(*this);
    std::cout << "Expression:" << std::endl;
    if (node.expr) node.expr->accept(*this);
}

void DisplayASTVisitor::visit(VectorNode &node) {
    std::cout << "VectorNode: elements=" << std::endl;
    for (auto &element : node.list) {
        element->accept(*this);
    }
}

void DisplayASTVisitor::visit(DeclNode &node) {
    std::cout << "DeclNode: isConst=" << node.isConst << ", type=" << node.type << ", id=" << node.id << std::endl;
    if (node.arraySize) {
        std::cout << "Array size:" << std::endl;
        node.arraySize->accept(*this);
    }
    if (node.initval) {
        std::cout << "Initial value:" << std::endl;
        node.initval->accept(*this);
    }
}

void DisplayASTVisitor::visit(ConstIntNode &node) {
    std::cout << "ConstIntNode: value=" << node.val << std::endl;
}

void DisplayASTVisitor::visit(ConstFloatNode &node) {
    std::cout << "ConstFloatNode: value=" << node.val << std::endl;
}

