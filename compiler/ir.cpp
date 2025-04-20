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
    {GT_OP, "gt"},
    {LT_OP, "lt"},
    {F2I_OP, "f2i"},
    {I2F_OP, "i2f"},
    {ASSIGN_OP, "assign"},
};

void BinaryInstruction::build(Builder &builder) {
    builder.build(*this);
}

void UnaryInstruction::build(Builder &builder) {
    builder.build(*this);
}

void BranchInstruction::build(Builder &builder) {
    builder.build(*this);
}

void FuncCallInstruction::build(Builder &builder) {
    builder.build(*this);
}

void GotoInstruction::build(Builder &builder) {
    builder.build(*this);
}

void MallocInstruction::build(Builder &builder) {
    builder.build(*this);
}

void LoadInstruction::build(Builder &builder) {
    builder.build(*this);
}

void StoreInstruction::build(Builder &builder) {
    builder.build(*this);
}

void LabelInstruction::build(Builder &builder) {
    builder.build(*this);
}

void ReturnInstruction::build(Builder &builder) {
    builder.build(*this);
}

