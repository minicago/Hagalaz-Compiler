#ifndef DISPLAYAST_H
#define DISPLAYAST_H
#include "def.h"
#include "AST.h"
#include <iostream>

class DisplayASTVisitor: public Visitor
{
public:
    DisplayASTVisitor() = default;

    // Override all virtual functions from Visitor
    void visit(ExprNode &node) override;
    void visit(IfElseNode &node) override;
    void visit(WhileNode &node) override;
    void visit(BreakNode &node) override;
    void visit(ContinueNode &node) override;
    void visit(ReturnNode &node) override;
    void visit(FuncDefNode &node) override;
    void visit(FuncCallNode &node) override;
    void visit(ParamNode &node) override;
    void visit(ParamListNode &node) override;
    void visit(FuncCallParamNode &node) override;
    void visit(CompUnitNode &node) override;
    void visit(StmtListNode &node) override;
    void visit(AssignNode &node) override;
    void visit(VectorNode &node) override;
    void visit(DeclNode &node) override;
    void visit(ConstIntNode &node) override;
    void visit(ConstFloatNode &node) override;
    void visit(IdentifierNode &node) override;
    void visit(SimpleTokenNode &node) override;
    void visit(BlockGroupNode &node) override;
    void visit(LvalNode &node) override;
};

#endif