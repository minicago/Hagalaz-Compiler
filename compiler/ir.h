#ifndef _IR_H_
#define _IR_H_

#include "type.h"
#include <variant>
#include <map>

class Instruction {
public:
    enum OpType {
        ADD_OP,
        SUB_OP,
        MUL_OP,
        DIV_OP,
        MOD_OP,
        AND_OP,
        OR_OP,
        NOT_OP,
        EQ_OP,
        NE_OP,
        GE_OP,
        LE_OP,
        F2I_OP,
        I2F_OP,
        ASSIGN_OP,
    };
    static std::map<OpType, std::string> opTypeToString;
    static std::string operandToString(Operand op)  {
        if (std::holds_alternative<std::shared_ptr<Value>>(op)) {
            return "$"+std::to_string(std::get<std::shared_ptr<Value>>(op)->no);
        } else if (std::holds_alternative<ConstType>(op)) {
            if (std::holds_alternative<int>(std::get<ConstType>(op))) {
                return std::to_string(std::get<int>(std::get<ConstType>(op)));
            } else if (std::holds_alternative<float>(std::get<ConstType>(op))) {
                return std::to_string(std::get<float>(std::get<ConstType>(op)));
            }
        }
        return "";
    }
    virtual std::string toString() const = 0;
    Instruction() = default;
};

class BinaryInstruction : public Instruction {
public:
    Operand operand1;
    Operand operand2;
    Operand result;
    OpType op;
    bool isFloat;

    
    BinaryInstruction(Operand operand1, Operand operand2, Operand result, OpType op, bool isFloat = false)
        : operand1(operand1), operand2(operand2), result(result), op(op), isFloat(isFloat) {}
    BinaryInstruction(Operand operand1, Operand operand2, Operand result, yytokentype op, bool isFloat = false)
        : operand1(operand1), operand2(operand2), result(result), isFloat(isFloat) {
        switch (op) {
            case ADD: this->op = ADD_OP; break;
            case SUB: this->op = SUB_OP; break;
            case MUL: this->op = MUL_OP; break;
            case DIV: this->op = DIV_OP; break;
            case MOD: this->op = MOD_OP; break;
            case AND: this->op = AND_OP; break;
            case OR: this->op = OR_OP; break;
            case EQ: this->op = EQ_OP; break;
            case NE: this->op = NE_OP; break;
            case GE: this->op = GE_OP; break;
            case LE: this->op = LE_OP; break;
            case GT: this->op = GE_OP; break;
            case LT: this->op = LE_OP; break;

            default: throw std::invalid_argument("Invalid operator");
        }
    }

    std::string toString() const override {
        return opTypeToString[op] + " " + operandToString(operand1) + ", " + operandToString(operand2) + " -> " + operandToString(result);
    }
};

class UnaryInstruction : public Instruction {
public:
    Operand operand;
    Operand result;
    OpType op;

    UnaryInstruction(Operand operand, Operand result, OpType op)
        : operand(operand), result(result), op(op) {}
    UnaryInstruction(Operand operand, Operand result, yytokentype op)
        : operand(operand), result(result) {
        switch (op) {
            case NOT: this->op = NOT_OP; break;
            default: throw std::invalid_argument("Invalid operator");
        }
    }
    

    std::string toString() const override {
        return opTypeToString[op] + " " + operandToString(operand) + " -> " + operandToString(result);
    }
};


class BranchInstruction : public Instruction {
public:
    Operand condition;
    Operand target;

    BranchInstruction(Operand condition, Operand target)
        : condition(condition), target(target) {}
    std::string toString() const override {
        return "if " + operandToString(condition) + " goto " + operandToString(target);
    }
};

class FuncCallInstruction : public Instruction {
public:
    std::string funcName;
    std::vector<Operand> params;
    Operand result;

    FuncCallInstruction(std::string funcName, std::vector<Operand> params, Operand result)
        : funcName(funcName), params(params), result(result) {}

    std::string toString() const override {
        std::string paramStr = "";
        for (auto &param : params) {
            paramStr += operandToString(param) + ", ";
        }
        return "call " + funcName + "(" + paramStr + ") -> " + operandToString(result);
    }
};

class GotoInstruction : public Instruction {
public:
    Operand target;

    GotoInstruction(Operand target)
        : target(target) {}

    std::string toString() const override {
        return "goto " + operandToString(target);
    }
};

class LabelInstruction : public Instruction {
public:
    Operand label;

    LabelInstruction(Operand label)
        : label(label) {}

    std::string toString() const override {
        return "label " + operandToString(label);
    }
};

class StoreInstruction : public Instruction {
public:
    Operand value;
    Operand address;

    StoreInstruction(Operand value, Operand address)
        : value(value), address(address) {}

    std::string toString() const override {
        return "store " + operandToString(value) + " -> " + operandToString(address);
    }
};

class LoadInstruction : public Instruction {
public:
    Operand address;
    Operand result;

    LoadInstruction(Operand address, Operand result)
        : address(address), result(result) {}

    std::string toString() const override {
        return "load " + operandToString(address) + " -> " + operandToString(result);
    }
};

class ReturnInstruction : public Instruction {
public:
    Operand value;

    ReturnInstruction(Operand value)
        : value(value) {}

    std::string toString() const override {
        return "return " + operandToString(value);
    }
};

class FuncDefInstruction : public Instruction {
public:
    std::string funcName;
    std::vector<std::string> params;
    Operand label;

    FuncDefInstruction(std::string funcName, std::vector<std::string> params, Operand label)
        : funcName(funcName), params(params), label(label) {}
    std::string toString() const override {
        std::string paramStr = "";
        for (auto &param : params) {
            paramStr += param + ", ";
        }
        return "func " + funcName + "(" + paramStr + ") -> " + operandToString(label);
    }
};

class MallocInstruction : public Instruction {
public:
    Operand size;
    Operand result;

    MallocInstruction(Operand size, Operand result)
        : size(size), result(result) {}

    std::string toString() const override {
        return "malloc " + operandToString(size) + " -> " + operandToString(result);
    }
};

class IRBuilder {
public:
    std::vector<std::shared_ptr<Instruction>> instructions;

    Operand newValue() {
        return std::make_shared<Value>();
    }

    void addInstruction(std::shared_ptr<Instruction> instruction) {
        instructions.push_back(instruction);
    }

    void f2i(Operand operand, Operand result) {
        addInstruction(std::make_shared<UnaryInstruction>(operand, result, UnaryInstruction::F2I_OP));
    }

    void i2f(Operand operand, Operand result) {
        addInstruction(std::make_shared<UnaryInstruction>(operand, result, UnaryInstruction::I2F_OP));
    }

    void assign(Operand src, Operand dest) {
        addInstruction(std::make_shared<UnaryInstruction>(src, dest, UnaryInstruction::ASSIGN_OP));
    }

    void addBinaryInstruction(Operand operand1, Operand operand2, Operand result, yytokentype op, bool isFloat = false) {
        addInstruction(std::make_shared<BinaryInstruction>(operand1, operand2, result, op, isFloat));
    }

    void addUnaryInstruction(Operand operand, Operand result, yytokentype op) {
        addInstruction(std::make_shared<UnaryInstruction>(operand, result, op));
    }

    void addBranchInstruction(Operand condition, Operand target) {
        addInstruction(std::make_shared<BranchInstruction>(condition, target));
    }

    void addFuncCallInstruction(std::string funcName, std::vector<Operand> params, Operand result) {
        addInstruction(std::make_shared<FuncCallInstruction>(funcName, params, result));
    }

    void addGotoInstruction(Operand target) {
        addInstruction(std::make_shared<GotoInstruction>(target));
    }

    void addLabelInstruction(Operand label) {
        addInstruction(std::make_shared<LabelInstruction>(label));
    }

    void addStoreInstruction(Operand value, Operand address) {
        addInstruction(std::make_shared<StoreInstruction>(value, address));
    }

    void addLoadInstruction(Operand address, Operand result) {
        addInstruction(std::make_shared<LoadInstruction>(address, result));
    }

    void addReturnInstruction(Operand value) {
        addInstruction(std::make_shared<ReturnInstruction>(value));
    }

    void addFuncDefInstruction(std::string funcName, std::vector<std::string> params, Operand label) {
        addInstruction(std::make_shared<FuncDefInstruction>(funcName, params, label));
    }

    void addMallocInstruction(Operand size, Operand result) {
        addInstruction(std::make_shared<MallocInstruction>(size, result));
    }

    std::string toString() const {
        std::string result;
        for (const auto &instruction : instructions) {
            result += instruction->toString() + "\n";
        }
        return result;
    }
};

#endif