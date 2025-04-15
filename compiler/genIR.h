#ifndef GENIR_H
#define GENIR_H

#include "def.h"
#include "AST.h"
#include "scope.h"
#include <optional>
#include <stack>
#include "type.h"
#include "ir.h"

class CheckerResult {
public:
    std::shared_ptr<Node> decl; 
    std::optional<TypeValue> value; 
    std::shared_ptr<Node> relocateNode; 
    std::shared_ptr<Node> jumpTarget;   

    CheckerResult(std::shared_ptr<FuncDecl> decl)
        : decl(decl->node), value(decl->returnType), relocateNode(nullptr), jumpTarget(nullptr)  {}
    CheckerResult(std::shared_ptr<VarDecl> decl)
        : decl(decl->node), value(decl->typeValue), relocateNode(nullptr), jumpTarget(nullptr) {}

    CheckerResult(TypeValue value)
        : decl(nullptr), value(value), relocateNode(nullptr), jumpTarget(nullptr) {}

    CheckerResult() = default;
};

class GenIR : public Visitor {
public:
    Scope scope;
    std::map<std::shared_ptr<Node>, CheckerResult, Node::NodeCompare> result;

    std::stack<std::shared_ptr<Node>> loopStack; // Changed to std::shared_ptr<Node>
    std::shared_ptr<Node> currentFunction;      // Changed to std::shared_ptr<Node>

    size_t constructingIndex;
    std::shared_ptr<TypeValue> constructingValue;
    std::shared_ptr<SysyType> constructingType;
    IRBuilder builder;

    bool isAssign;

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

    GenIR() = default;
};

#endif