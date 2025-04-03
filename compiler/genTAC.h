#ifndef GENTAC_H
#define GENTAC_H

#include "def.h"
#include "AST.h"
#include "scope.h"
#include <variant>
#include <vector>
#include <memory>

class TAC {
public:
    std::string op;
    std::string arg1, arg2, result;
};

class TACList {
private:
    TAC tac;
    TACList* nextTAC;
public:
    TACList(TAC tac) {
        this->tac = tac;
        this->nextTAC = this;
    }
    void merge(std::shared_ptr<TACList> other) {
        std::swap(nextTAC, other->nextTAC);
    }
};

class SemaChunck{
public:
    std::optional<std::shared_ptr<ConstChunk> > initval;
    std::optional<std::shared_ptr<Var> > var;
    std::shared_ptr<TACList> truelist, falselist, nextlist;

    SemaChunck() : initval(std::nullopt), truelist(nullptr), falselist(nullptr), nextlist(nullptr) {}
};


class GenTACVisitor : public Visitor {
private:
    std::shared_ptr<SemaChunck> semaChunk;
    bool Assign;

public:
    GenTACVisitor() = default;

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
    void visit(vectorNode &node) override;
    void visit(DeclNode &node) override;
    void visit(ConstIntNode &node) override;
    void visit(ConstFloatNode &node) override;
    void visit(IdentifierNode &node) override;
    void visit(SimpleTokenNode &node) override;
    void visit(BlockGroupNode &node) override;
    void visit(LvalNode &node) override;
};

#endif