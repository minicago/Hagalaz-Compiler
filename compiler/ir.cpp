#include "ir.h"
#include <map>
#include <string>

std::map<Instruction::OpType, std::string> Instruction::opTypeToString = {
    {ADD_OP, "add"},
    {SUB_OP, "sub"},
    {MUL_OP, "mul"},
    {DIV_OP, "div"},
    {MOD_OP, "mod"},
    {AND_OP, "and"},
    {OR_OP, "or"},
    {NOT_OP, "not"},
    {EQ_OP, "eq"},
    {NE_OP, "ne"},
    {GE_OP, "ge"},
    {LE_OP, "le"},
    {F2I_OP, "f2i"},
    {I2F_OP, "i2f"},
    {ASSIGN_OP, "assign"},
};