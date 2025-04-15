/***********定义结点类型和给出函数说明*********/
#ifndef __DEF_H__
#define __DEF_H__

#include "output.h"
#include <variant>
#include <vector>
#include <string>
#include <optional>
#include <valarray>
#include <stdexcept>

class Visitor;

class Node;

#include <memory>

#define LOG(msg) *output.log << msg << std::endl

#include <stdexcept>
#define REPORT_ERROR(msg) throw std::runtime_error(msg)

#define YYSTYPE std::shared_ptr<Node>
#include "y.tab.h"

int __main();

#endif 