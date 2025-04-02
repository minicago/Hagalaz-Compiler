/***********定义结点类型和给出函数说明*********/
#ifndef __DEF_H__
#define __DEF_H__

class Visitor;

class Node{
public:
    virtual void accept(Visitor &v) = 0;
    Node() = default;
    virtual ~Node() = default;
};

#include <memory>

#define YYSTYPE std::shared_ptr<Node>
#include "y.tab.h"


#endif 