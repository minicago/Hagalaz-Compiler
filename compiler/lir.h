#ifndef LIR_H
#define LIR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "ir.h"

#define FLOAT1 1065353216

class LIROperand {
public :
    bool isLabel() {
        if (dynamic_cast<LIRLabel*>(this) != nullptr) {
            return true;
        }
        return false;
    }
    bool isImm(){
        if (dynamic_cast<LIRImmediate*>(this) != nullptr) {
            return true;
        }
        return false;
    }
    bool isReg(){
        if (dynamic_cast<LIRRegister*>(this) != nullptr) {
            return true;
        }
        return false;
    }
    virtual std::string toString() = 0;
};

class LIRLabel : public LIROperand {
public:
    std::string label;
    LIRLabel(std::string label) : label(label) {}
    std::string toString() {
        return label;
    }
};

class LIRImmediate : public LIROperand {
public:
    int value;
    LIRImmediate(int value) : value(value) {}
    std::string toString() {
        return "#" + std::to_string(value);
    }
};

class LIRRegister : public LIROperand {
public:
    int reg;
    LIRRegister(int reg) : reg(reg) {}
    std::string toString() {
        return "r" + std::to_string(reg);
    }
};




class RegisterManager {
public:
    bool available[16], used[16];

    RegisterManager() {
        for (int i = 0; i < 16; i++) {
            available[i] = true;
            used[i] = false;
        }
    }

    int get_r(){
        for (int i = 7; i < 16; i++) {
            if (available[i]) {
                available[i] = false;
                used[i] = true;
                return i;
            }
        }        
    }

    int return_r(int i){
        available[i] = true;
    }



};

class LIRInstruction {
public:
    virtual std::string toString() const = 0;
};

class LIRGlobalVarInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> label;
    int size;
    std::string toString () const override{
        std::string result;
        result = label->toString() + ":";
        result += "\t.space " + std::to_string(size);
    }
};

class LIRExprInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> dest;
    std::shared_ptr<LIROperand> src1;
    std::shared_ptr<LIROperand> src2;
    Instruction::OpType op;
    bool isFloat;
    LIRExprInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src1, std::shared_ptr<LIROperand> src2, Instruction::OpType op) : dest(dest), src1(src1), src2(src2), op(op) {}
    std::string toString() const override {
        std::string result;
        if (isFloat) {
            result += "vmov s14, " + src1->toString() + "\n" ;
            result += "vmov s15, " + src2->toString() + "\n" ;

            if(op == Instruction::ADD_OP || op == Instruction::SUB_OP || op == Instruction::MUL_OP || op == Instruction::DIV_OP) {
                result += "v" + Instruction::opTypeToString[op] + ".f32 s15, s15, s14" + "\n";
                result += "vstr.f32 s15, " + dest->toString() + "\n";
            }
            else if(op == Instruction::EQ_OP || op == Instruction::NE_OP || op == Instruction::GE_OP || op == Instruction::LE_OP || op == Instruction::GT_OP || op == Instruction::LT_OP) {
                result += "vcmpe.f32 s15, s14\n"
                            "vmrs APSR_nzcv, fpscr\n";
            }

        } else {
            if(op == Instruction::ADD_OP || op == Instruction::SUB_OP || op == Instruction::MUL_OP || op == Instruction::DIV_OP || op == Instruction::MOD_OP) {
                result += Instruction::opTypeToString[op] + "s " + dest->toString() + ", " + src1->toString() + ", " + src2->toString() + "\n";
            }
            if (op == Instruction::EQ_OP || op == Instruction::NE_OP || op == Instruction::GE_OP || op == Instruction::LE_OP || op == Instruction::GT_OP || op == Instruction::LT_OP) {
                result += "cmp " + src1->toString() + ", " + src2->toString() + "\n";
            }
            
        }
        if (op == Instruction::EQ_OP || op == Instruction::NE_OP || op == Instruction::GE_OP || op == Instruction::LE_OP || op == Instruction::GT_OP || op == Instruction::LT_OP) {
           
            result += "ite " + Instruction::opTypeToString[op] + "\n";

            result += "mov" + Instruction::opTypeToString[op] + " " + dest->toString() + ", #1\n";
            result += "mov" + Instruction::opTypeToString[Instruction::reserveOp(op)] + " " + dest->toString() + ", #0\n";
            
            result += "uxtb " + dest->toString() + ", " + dest->toString() + "\n";
        }
    }
};

class UnaryLIRInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> dest;
    std::shared_ptr<LIROperand> src;
    Instruction::OpType op;

    UnaryLIRInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src, Instruction::OpType op) : dest(dest), src(src), op(op) {}
    std::string toString() const override {
        std::string result;

        if (op == Instruction::NOT_OP) {
            result += "cmp " + src->toString() + ", #0\n";
            result += "ite eq";
            result += "moveq " + dest->toString() + ", #1\n";
            result += "movne " + dest->toString() + ", #0\n";
        } else if (op == Instruction::F2I_OP) {
            result += "vmov s14, " + src->toString() + "\n";
            result += "vcvt.s32.f32 s14, s14\n";
            result += "vmov " + dest->toString() + ", s14\n";
        } else if (op == Instruction::I2F_OP) {
            result += "vmov s14, " + src->toString() + "\n";
            result += "vcvt.f32.s32 s14, s14\n";
            result += "vmov " + dest->toString() + ", s14\n";
        } 

        return result;
    }
};

class LIRBranchInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> condition;
    std::shared_ptr<LIROperand> target;
    LIRBranchInstruction(std::shared_ptr<LIROperand> condition, std::shared_ptr<LIROperand> target) : condition(condition), target(target) {}
    std::string toString() const override {
        return "cmp " + condition->toString() + ", #0\n" +
               "beq " + target->toString() + "\n";
    }
};

class LIRFuncCallInstruction : public LIRInstruction {
public:
    std::string funcName;
    std::vector<std::shared_ptr<LIROperand>> params;
    std::shared_ptr<LIROperand> result;

    LIRFuncCallInstruction(std::string funcName, std::vector<std::shared_ptr<LIROperand>> params, std::shared_ptr<LIROperand> result)
        : funcName(funcName), params(params), result(result) {}

    std::string toString() const override {
        std::string resultStr;
        for (size_t i = 0; i < params.size(); ++i) {
            resultStr += "push {" + params[i]->toString() + "}\n";
        }
        resultStr +=  "bl " + funcName + "\n";
        if (result) {
            resultStr += "mov " + result->toString() + ", r0\n";
        }
        resultStr += "add sp, sp, #" + std::to_string(params.size() * 4) + "\n";
        return resultStr;
    }
};

class LIRGotoInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> target;
    LIRGotoInstruction(std::shared_ptr<LIROperand> target) : target(target) {}
    std::string toString() const override {
        return "b " + target->toString() + "\n";
    }
};

class LIRLabelInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> label;
    LIRLabelInstruction(std::shared_ptr<LIROperand> label) : label(label) {}
    std::string toString() const override {
        return label->toString() + ":\n";
    }
};

class LIRStoreInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> src;
    std::shared_ptr<LIROperand> dest;
    LIRStoreInstruction(std::shared_ptr<LIROperand> src, std::shared_ptr<LIROperand> dest) : src(src), dest(dest) {}
    std::string toString() const override {
        return "str " + src->toString() + ", " + dest->toString() + "\n";
    }
};

class LIRLoadInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> src;
    std::shared_ptr<LIROperand> dest;
    LIRLoadInstruction(std::shared_ptr<LIROperand> src, std::shared_ptr<LIROperand> dest) : src(src), dest(dest) {}
    std::string toString() const override {
        return "ldr " + dest->toString() + ", " + src->toString() + "\n";
    }
};

class LIRReturnInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> value;
    std::shared_ptr<LIROperand> retLabel;
    LIRReturnInstruction(std::shared_ptr<LIROperand> value, std::shared_ptr<LIROperand> retLabel) : value(value), retLabel(retLabel) {}
    std::string toString() const override {
        std::string result;
        if (value) {
            result += "mov r0, " + value->toString() + "\n";
        }
        result += "b " + retLabel->toString() + "\n";
        return result;
    }
};



class LIRCodeBlock {
public:
    RegisterManager rm;
    std::vector<LIRInstruction> instructions;

    std::string toString() const{
        std::string result;
        for (const auto& instruction : instructions) {
            result += instruction.toString();
        }
        return result;
    }
};

class LIRModule{
public:
    std::vector<std::shared_ptr<LIRCodeBlock>> codeBlocks;
    std::shared_ptr<LIRCodeBlock> globalBlock;

    LIRModule() {
        globalBlock = std::make_shared<LIRCodeBlock>();
    }

    std::string toString() const {

        std::string result;
        result += "	.arch armv7-a\n"
	                ".fpu vfpv3-d16\n";
        result += ".data\n";
        result += globalBlock->toString() + "\n";  
        result += ".text\n";

        for (const auto& block : codeBlocks) {
            for (const auto& instruction : block->instructions) {
                result += instruction.toString();
            }
        }
        return result;
    }
};

class LIRBuilder{
public:
    Module module;
    LIRModule lirModule;
    std::shared_ptr<LIRCodeBlock> currentBlock;
    std::shared_ptr<LIROperand> returnLabel;

    std::map<std::shared_ptr<Value>, std::shared_ptr<LIROperand>, Value::ValueCompare> vm;

    LIRBuilder(Module module) : module(module) {
        currentBlock = lirModule.globalBlock;
    }
};



#endif // LIR_H