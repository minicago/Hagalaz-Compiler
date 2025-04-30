#ifndef _IR_H_
#define _IR_H_

#include "type.h"
#include <variant>
#include <map>

class BinaryInstruction;
class UnaryInstruction;
class BranchInstruction;
class FuncCallInstruction;
class GotoInstruction;
class MallocInstruction;
class LoadInstruction;
class StoreInstruction;


class Builder;

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
        GT_OP,
        LT_OP,
        LE_OP,
        F2I_OP,
        I2F_OP,
        ASSIGN_OP,
    };
    static OpType reserveOp(OpType op) {
        if (op == EQ_OP) {
            return NE_OP;
        } else if (op == NE_OP) {
            return EQ_OP;
        } else if (op == GE_OP) {
            return LT_OP;
        } else if (op == GT_OP) {
            return LE_OP;
        } else if (op == LT_OP) {
            return GE_OP;
        } else if (op == LE_OP) {
            return GT_OP;
        }
    }
    static Operand constInt(int a){
        return a;
    }
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
    virtual void build(Builder &builder) = 0;
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
    virtual void build(Builder &builder) override;
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
    virtual void build(Builder &builder) override;
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
    virtual void build(Builder &builder) override;
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
    virtual void build(Builder &builder) override;
};

class GotoInstruction : public Instruction {
public:
    Operand target;

    GotoInstruction(Operand target)
        : target(target) {}

    std::string toString() const override {
        return "goto " + operandToString(target);
    }
    virtual void build(Builder &builder) override;
};

class LabelInstruction : public Instruction {
public:
    Operand label;

    LabelInstruction(Operand label)
        : label(label) {}

    std::string toString() const override {
        return "label " + operandToString(label);
    }
    virtual void build(Builder &builder) override;
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
    virtual void build(Builder &builder) override;
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
    virtual void build(Builder &builder) override;
};

class ReturnInstruction : public Instruction {
public:
    Operand value;

    ReturnInstruction(Operand value)
        : value(value) {}

    std::string toString() const override {
        return "return " + operandToString(value);
    }
    virtual void build(Builder &builder) override;
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
    virtual void build(Builder &builder) override;
};

class CodeBlock {
public:
    std::vector<std::shared_ptr<Value>> args_;
    std::vector<std::shared_ptr<Instruction>> instructions;
    std::string toString() const {
        std::string result;
        result += "(";
        for (const auto &arg : args_) {
            result += Instruction::operandToString(arg) + ",";
        }
        result += ")\n";
        
        for (const auto &instruction : instructions) {
            *output.log << instruction->toString() <<std::endl;
            result += instruction->toString() + "\n";

        }
        return result;
    }
    
};

class Module {
public:
    std::shared_ptr<CodeBlock> global;
    std::map<std::string, std::shared_ptr<CodeBlock>>  func;

    std::string toString() const {
        std::string result;
        
        result += global->toString();
        for (const auto &pair : func) {
            // *output.log << (pair.first + "\n" + pair.second->toString() + '\n') <<std::endl;
            result += pair.first + "\n" + pair.second->toString() + '\n';
            
        }
        return result;
    }

};

class IRBuilder {
public:
    std::shared_ptr<Module> module;
    std::shared_ptr<CodeBlock> currentBlock;

    Operand newValue() {
        return std::make_shared<Value>();
    }

    void addInstruction(std::shared_ptr<Instruction> instruction) {
        // *output.log << "add" << instruction->toString() << std::endl;
        currentBlock->instructions.push_back(instruction);
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
        
        // *output.log << "addBinaryInstruction1" << Instruction::operandToString(operand1) << std::endl;
        // *output.log << "addBinaryInstruction2" << Instruction::operandToString(operand2) << std::endl;
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

    void addMallocInstruction(Operand size, Operand result) {
        addInstruction(std::make_shared<MallocInstruction>(size, result));
    }

    Operand getIntOperand(TypeValue& tv){
        if(!tv.type->isSimpleType()) {
            REPORT_ERROR("getIntOperand Error");
        }
        if(std::dynamic_pointer_cast<SimpleType> (tv.type)->type == SysyType::IntegerTyID) {
            return tv.getOperand();
        }
        if(std::dynamic_pointer_cast<SimpleType> (tv.type)->type == SysyType::FloatTyID){
            if (tv.hasConst()) {
                return tv.getInt();
            } else {
                auto tmp = newValue();
                f2i(tv.getOperand(), tmp);
                return tmp;
            }
        }
        REPORT_ERROR("getIntOperand Error");
    }

    Operand getFloatOperand(TypeValue& tv){
        if(!tv.type->isSimpleType()) {
            REPORT_ERROR("getFloatOperand Error");
        }
        if(std::dynamic_pointer_cast<SimpleType> (tv.type)->type == SysyType::FloatTyID) {
            return tv.getOperand();
        }
        if(std::dynamic_pointer_cast<SimpleType> (tv.type)->type == SysyType::IntegerTyID){
            if (tv.hasConst()) {
                return tv.getFloat();
            } else {
                auto tmp = newValue();
                i2f(tv.getOperand(), tmp);
                return tmp;
            }
        }
        REPORT_ERROR("getFloatOperand Error");
    }


    std::string toString() const {
        std::string result;
        *output.log << "IRBuilder toString" << std::endl;
        return module->toString();
    }

    void newBlock(std::string name) {
        module->func[name] = std::make_shared<CodeBlock>();
        currentBlock = module->func[name];
    }

    void addFuncArg(std::shared_ptr<Value> v){
        currentBlock->args_.push_back(v);
    }

    void switchToGlobal() {
        
        currentBlock = module->global;
    }

    IRBuilder() {
        module = std::make_shared<Module>();
        module->global = std::make_shared<CodeBlock>();
        switchToGlobal();
    }

    
};

class Builder{
public:
    virtual void build(BinaryInstruction& Instruction) = 0;
    virtual void build(UnaryInstruction& Instruction) = 0;
    virtual void build(BranchInstruction& Instruction) = 0;
    virtual void build(FuncCallInstruction& Instruction) = 0;
    virtual void build(GotoInstruction& Instruction) = 0;
    virtual void build(MallocInstruction& Instruction) = 0;
    virtual void build(LoadInstruction& Instruction) = 0;
    virtual void build(StoreInstruction& Instruction) = 0;
    virtual void build(LabelInstruction& Instruction) = 0;
    virtual void build(ReturnInstruction& Instruction) = 0;

};

#endif