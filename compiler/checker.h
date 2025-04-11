#ifndef CHECKER_H
#define CHECKER_H

#include "def.h"
#include "AST.h"
#include "scope.h"
#include <optional>
#include <stack>
#include "type.h"

class checkerResult {
public:
    std::variant<std::shared_ptr<FuncDecl>, std::shared_ptr<VarDecl>> decl; // Changed to use shared_ptr
    std::optional<TypeValue> value; // Changed to std::optional<std::shared_ptr<ConstChunk>>
    std::shared_ptr<Node> relocateNode; // For conditional jumps
    std::shared_ptr<Node> jumpTarget;   // Changed to std::shared_ptr<Node>

    checkerResult(std::variant<std::shared_ptr<FuncDecl>, std::shared_ptr<VarDecl>> decl)
        : decl(decl), value(), relocateNode(nullptr), jumpTarget(nullptr) {}

    checkerResult(std::variant<std::shared_ptr<FuncDecl>, std::shared_ptr<VarDecl>> decl, TypeValue value)
        : decl(decl), value(value), relocateNode(nullptr), jumpTarget(nullptr) {}

    checkerResult() = default;
};

class Checker : public Visitor {
public:
    Scope scope;
    std::map<std::shared_ptr<Node>, checkerResult, Node::NodeCompare> result;

    std::stack<std::shared_ptr<Node>> loopStack; // Changed to std::shared_ptr<Node>
    std::shared_ptr<Node> currentFunction;      // Changed to std::shared_ptr<Node>

    size_t constructingIndex;
    std::shared_ptr<TypeValue> constructingValue;
    std::shared_ptr<SysyType> constructingType;

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

    Checker() = default;
};

#endif