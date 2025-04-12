#ifndef AST_H
#define AST_H

#include "def.h"
#include <vector>
#include <string>
#include <memory>
extern std::shared_ptr<Node> AST_root;

class Node{
    private:
        static int count;
        int index;
    
    public:
        class NodeCompare
        {
        public:
            bool operator()(const std::shared_ptr<Node>& lhs, const std::shared_ptr<Node>& rhs) const
            {
                return lhs->index < rhs->index;
            }
        };
    
        virtual void accept(Visitor &v) = 0;
        virtual std::string toString() const = 0;
        Node(){
            index = count++;
        }
        virtual ~Node() = default;
};


class StmtListNode: public Node
{
public:
    std::vector<std::shared_ptr<Node>> stmtlist;

    StmtListNode(){}
    StmtListNode(std::vector<std::shared_ptr<Node>> stmtlist):stmtlist(stmtlist){}
    void addStmt(std::shared_ptr<Node> stmt)
    {
        stmtlist.push_back(stmt);
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "StmtListNode";
    }
};

class ExprNode: public Node
{
public:
    yytokentype op;
    std::shared_ptr<Node> val1;
    std::shared_ptr<Node> val2;

    ExprNode(yytokentype op, std::shared_ptr<Node> val1, std::shared_ptr<Node> val2):op(op),val1(val1),val2(val2){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "ExprNode: op=" + std::to_string(op);
    }
};

class IfElseNode: public Node
{
public:
    std::shared_ptr<Node> cond;
    std::shared_ptr<Node> ifstmt;
    std::shared_ptr<Node> elsestmt;

    IfElseNode(std::shared_ptr<Node> cond, std::shared_ptr<Node> ifstmt, std::shared_ptr<Node> elsestmt):cond(cond),ifstmt(ifstmt),elsestmt(elsestmt){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "IfElseNode";
    }
};

class WhileNode: public Node
{
public:
    std::shared_ptr<Node> cond;
    std::shared_ptr<Node> stmt;

    WhileNode(std::shared_ptr<Node> cond, std::shared_ptr<Node> stmt):cond(cond),stmt(stmt){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "WhileNode";
    }
};

class BreakNode: public Node
{
public:
    BreakNode(){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "BreakNode";
    }
};

class ContinueNode: public Node
{
public:
    ContinueNode(){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "ContinueNode";
    }
};

class ReturnNode: public Node
{
public:
    std::shared_ptr<Node> expr;

    ReturnNode(std::shared_ptr<Node> expr):expr(expr){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "ReturnNode";
    }
};

class FuncDefNode: public Node
{
public:
    yytokentype type;
    std::string id;
    std::shared_ptr<Node> param;
    std::shared_ptr<Node> stmt;

    FuncDefNode(yytokentype type, const std::string &id, std::shared_ptr<Node> param, std::shared_ptr<Node> stmt):type(type),id(id),param(param),stmt(stmt){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "FuncDefNode: type=" + std::to_string(type) + ", id=" + id;
    }
};

class FuncCallNode: public Node
{
public:
    std::string id;
    std::shared_ptr<Node> param;

    FuncCallNode(const std::string &id, std::shared_ptr<Node> param):id(id),param(param){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "FuncCallNode: id=" + id;
    }
};

class ParamNode: public Node
{
public:
    yytokentype type;
    std::string id;
    bool isptr;
    std::shared_ptr<Node> arraySize;
    
    ParamNode(yytokentype type, const std::string &id, bool isptr, std::shared_ptr<Node> arraySize):type(type),id(id),isptr(isptr),arraySize(arraySize){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "ParamNode: type=" + std::to_string(type) + ", id=" + id + ", isptr=" + std::to_string(isptr);
    }
};
    
class ParamListNode: public Node
{
public:
    std::vector<std::shared_ptr<Node>> paramlist;

    ParamListNode(){}
    ParamListNode(std::vector<std::shared_ptr<Node>> paramlist):paramlist(paramlist){}
    void addParam(std::shared_ptr<Node> param)
    {
        paramlist.push_back(param);
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "ParamListNode";
    }
};

class FuncCallParamNode: public Node
{
public:
    std::vector<std::shared_ptr<Node>> paramlist;

    FuncCallParamNode(){}
    FuncCallParamNode(std::vector<std::shared_ptr<Node>> paramlist):paramlist(paramlist){}
    void addParam(std::shared_ptr<Node> param)
    {
        paramlist.push_back(param);
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "FuncCallParamNode";
    }
};


class CompUnitNode: public Node
{
public:
    std::vector<std::shared_ptr<Node>> deflist;

    CompUnitNode(){}
    CompUnitNode(std::vector<std::shared_ptr<Node>> deflist):deflist(deflist){}
    void addDef(std::shared_ptr<Node>& def)
    {
        if (typeid(*def) == typeid(StmtListNode))
        {
            auto stmtlist = std::dynamic_pointer_cast<StmtListNode>(def);
            for (auto &stmt: stmtlist->stmtlist)
                deflist.push_back(stmt);
            return;
        }
        else deflist.push_back(def);
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "CompUnitNode";
    }
};

class AssignNode: public Node
{
public:
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> expr;

    AssignNode(std::shared_ptr<Node> left, std::shared_ptr<Node> expr):left(left),expr(expr){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "AssignNode";
    }
};

class VectorNode: public Node
{
public:
    std::vector<std::shared_ptr<Node>> list;
    VectorNode(){}
    VectorNode(std::vector<std::shared_ptr<Node>> list):list(list){}
    void addNode(std::shared_ptr<Node> node)
    {
        list.push_back(node);
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "VectorNode";
    }
};


class DeclNode: public Node
{
public:
    bool isConst;
    yytokentype type;
    std::string id;
    std::shared_ptr<Node> arraySize;
    std::shared_ptr<Node> initval;

    DeclNode(bool isConst, yytokentype type, const std::string &id, std::shared_ptr<Node> arraySize, std::shared_ptr<Node> initval):
        isConst(isConst),type(type),id(id),arraySize(arraySize),initval(initval){}
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "DeclNode: isConst=" + std::to_string(isConst) + ", type=" + std::to_string(type) + ", id=" + id;
    }
};

class ConstIntNode: public Node
{
public:
    int val;

    ConstIntNode(int val):val(val){}
    int getVal()
    {
        return val;
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "ConstIntNode: val=" + std::to_string(val);
    }
};

class ConstFloatNode: public Node
{
public:
    float val;

    ConstFloatNode(float val):val(val){}
    float getVal()
    {
        return val;
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "ConstFloatNode: val=" + std::to_string(val);
    }
};

#include "scope.h"

class IdentifierNode: public Node
{
public:
    std::string id;

    IdentifierNode(const std::string &id):id(id){}
    std::string getId()
    {
        return id;
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "IdentifierNode: id=" + id;
    }
};

class SimpleTokenNode: public Node
{
public:
    yytokentype type;

    SimpleTokenNode(yytokentype type):type(type){}
    yytokentype getType()
    {
        return type;
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "SimpleTokenNode: type=" + std::to_string(type);
    }
};

class BlockGroupNode: public Node
{
public:
    std::vector<std::shared_ptr<Node>> blocklist;

    BlockGroupNode(){}
    BlockGroupNode(std::vector<std::shared_ptr<Node>> blocklist):blocklist(blocklist){}
    void addBlock(std::shared_ptr<Node> block)
    {
        if (typeid(*block) == typeid(StmtListNode))
        {
            auto stmtlist = std::dynamic_pointer_cast<StmtListNode>(block);
            for (auto &stmt: stmtlist->stmtlist)
                blocklist.push_back(stmt);
            return;
        }
        else blocklist.push_back(block);
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "BlockGroupNode";
    }
};

class LvalNode: public Node
{
public:
    std::string id;
    std::shared_ptr<Node> arrayIndex;

    LvalNode(const std::string &id, std::shared_ptr<Node> arrayIndex):id(id),arrayIndex(arrayIndex){}
    std::string getId()
    {
        return id;
    }
    virtual void accept(Visitor &v) override ;
    std::string toString() const override {
        return "LvalNode: id=" + id;
    }
};

class Visitor
{
public:
    virtual void visit(ExprNode &node) = 0;
    virtual void visit(IfElseNode &node) = 0;
    virtual void visit(WhileNode &node) = 0;
    virtual void visit(BreakNode &node) = 0;
    virtual void visit(ContinueNode &node) = 0;
    virtual void visit(ReturnNode &node) = 0;
    virtual void visit(FuncDefNode &node) = 0;
    virtual void visit(FuncCallNode &node) = 0;
    virtual void visit(ParamNode &node) = 0;
    virtual void visit(ParamListNode &node) = 0;
    virtual void visit(FuncCallParamNode &node) = 0;
    virtual void visit(CompUnitNode &node) = 0;
    virtual void visit(StmtListNode &node) = 0;
    virtual void visit(AssignNode &node) = 0;
    virtual void visit(VectorNode &node) = 0;
    virtual void visit(DeclNode &node) = 0;
    virtual void visit(ConstIntNode &node) = 0;
    virtual void visit(ConstFloatNode &node) = 0;
    virtual void visit(IdentifierNode &node) = 0;
    virtual void visit(SimpleTokenNode &node) = 0;
    virtual void visit(BlockGroupNode &node) = 0;
    virtual void visit(LvalNode &node) = 0;
};  

#endif