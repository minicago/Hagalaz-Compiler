#include "def.h"
#include "AST.h"

yytokentype decl_type;
std::shared_ptr<Node> AST_root;


void ExprNode::accept(Visitor &v)
{
    v.visit(*this);
}
void SimpleTokenNode::accept(Visitor &v)
{
    v.visit(*this);
}
void IdentifierNode::accept(Visitor &v)
{
    v.visit(*this);
}
void FuncCallNode::accept(Visitor &v)
{
    v.visit(*this);
}
void FuncCallParamNode::accept(Visitor &v)
{
    v.visit(*this);
}
void ParamNode::accept(Visitor &v)
{
    v.visit(*this);
}
void ParamListNode::accept(Visitor &v)
{
    v.visit(*this);
}
void CompUnitNode::accept(Visitor &v)
{
    v.visit(*this);
}
void BlockGroupNode::accept(Visitor &v)
{
    v.visit(*this);
}
void LvalNode::accept(Visitor &v)
{
    v.visit(*this);
}
void IfElseNode::accept(Visitor &v)
{
    v.visit(*this);
}
void WhileNode::accept(Visitor &v)
{
    v.visit(*this);
}
void BreakNode::accept(Visitor &v)
{
    v.visit(*this);
}
void ContinueNode::accept(Visitor &v)
{
    v.visit(*this);
}
void ReturnNode::accept(Visitor &v)
{
    v.visit(*this);
}
void FuncDefNode::accept(Visitor &v)
{
    v.visit(*this);
}
void StmtListNode::accept(Visitor &v)
{
    v.visit(*this);
}
void AssignNode::accept(Visitor &v)
{
    v.visit(*this);
}
void vectorNode::accept(Visitor &v)
{
    v.visit(*this);
}
void DeclNode::accept(Visitor &v)
{
    v.visit(*this);
}
void ConstIntNode::accept(Visitor &v)
{
    v.visit(*this);
}
void ConstFloatNode::accept(Visitor &v)
{
    v.visit(*this);
}