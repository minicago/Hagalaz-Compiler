/***********定义结点类型和给出函数说明*********/
#ifndef __DEF_H__
#define __DEF_H__

#include "output.h"
#include <variant>
#include <vector>
#include <string>
#include <optional>
#include <valarray>

class Visitor;

class Node;

#include <memory>

#define LOG(msg) *output.log << msg << std::endl
#define REPORT_ERROR(msg) *output.err << "Error: " << msg << std::endl

#define YYSTYPE std::shared_ptr<Node>
#include "y.tab.h"

int __main();

#endif 