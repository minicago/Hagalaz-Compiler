/***********定义结点类型和给出函数说明*********/
#ifndef __DEF_H__
#define __DEF_H__

#include "output.h"
#include <variant>
#include <vector>
#include <string>
#include <optional>
#include <valarray>

class Var{
public:
    int id;
};


typedef std::variant<int, float> Const; 


typedef std::vector<int> IntList;


class ConstChunk{
public:
    std::variant<Const, std::vector<ConstChunk> > value;

    ConstChunk(){ value = std::vector<ConstChunk>(); }
    ConstChunk(std::variant<Const, std::vector<ConstChunk> > value):value(value){}
};


typedef std::variant<Const, Var> Value;


class ValueChunk{

public:
    std::variant<Value, std::vector<ValueChunk> > value;


};
class Visitor;

class Node{
public:
    virtual void accept(Visitor &v) = 0;
    Node() = default;
    virtual ~Node() = default;
};

#include <memory>

#define LOG(msg) *output.log << msg << std::endl
#define REPORT_ERROR(msg) std::cerr << "Error: " << msg << std::endl

#define YYSTYPE std::shared_ptr<Node>
#include "y.tab.h"


#endif 