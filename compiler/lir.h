#ifndef LIR_H
#define LIR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include "ir.h"

#define FLOAT1 1065353216
class LIRLabel;
class LIRImmediate;
class LIRRegister;
class LIRAddress;

class LIROperand {
public :
    virtual bool isLabel(){
        return false;
    }
    virtual bool isImm(){
        return false;
    }
    virtual bool isReg(){
        return false;
    }
    virtual bool isAddr(){
        return false;
    }
    virtual std::string toString() = 0;
};



class LIRLabel : public LIROperand {
public:
    std::string label;
    LIRLabel(std::string label) : label(label) {}
    bool isLabel() override{
        return true;
    }
    std::string toString() {
        return label;
    }
};

class LIRImmediate : public LIROperand {
public:
    int value;
    LIRImmediate(int value) : value(value) {}
    LIRImmediate(float value) : value(*(int*)&value) {}
    bool isImm() override{
        return true;
    }
    std::string toString() {
        return "#" + std::to_string(value);
    }
};

class LIRRegister : public LIROperand {
public:
    int reg;
    LIRRegister(int reg) : reg(reg) {}
    bool isReg() override{
        return true;
    }
    std::string toString() {
        return "r" + std::to_string(reg);
    }
};

class LIRAddress : public LIROperand {
public:
    int reg;
    int offset;
    bool isAddr() override{
        return true;
    }
    LIRAddress() = default;
    LIRAddress(int reg, int offset) : reg(reg), offset(offset) {}
    LIRAddress(int offset) : reg(7), offset(offset) {}



    std::string toString() {
        return "[r" + std::to_string(reg) + ", #" + std::to_string(offset)+']';
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
        available[7] = false;
        // available[0] = false;
        used[7] = true;
    }

    std::shared_ptr<LIROperand> get_r(){
        for (int i = 4; i < 16; i++) {
            if (available[i]) {
                available[i] = false;
                used[i] = true;
                return std::make_shared<LIRRegister>(i);
            }
        }        
    }

    std::shared_ptr<LIROperand> get_r(int i){
        return std::make_shared<LIRRegister>(i);
    }

    void return_r(std::shared_ptr<LIROperand> r){
        if (r->isReg()){
            int reg = std::dynamic_pointer_cast<LIRRegister>(r)->reg;
            available[reg] = true;
        }
    }

    std::string allUsedRegister() const{
        std::string result;
        for (int i = 0; i < 16; i++) {
            if (used[i]) {
                result += "r" + std::to_string(i) + ", ";
            }
        }
        return result;
    }
    int getUsedRegisterCount() const{
        int count = 0;
        for (int i = 0; i < 16; i++) {
            if (used[i]) {
                count++;
            }
        }
        return count;
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
    LIRGlobalVarInstruction(std::shared_ptr<LIROperand> label, int size) : label(label), size(size) {}
    std::string toString () const override{
        std::string result;
        result = label->toString() + ":\n";
        result += "\t.space " + std::to_string(size) + "\n";
        return result;
    }
};

class LIRBinaryInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> dest;
    std::shared_ptr<LIROperand> src1;
    std::shared_ptr<LIROperand> src2;
    Instruction::OpType op;
    bool isFloat;
    LIRBinaryInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src1, std::shared_ptr<LIROperand> src2, Instruction::OpType op, bool isFloat = false) 
        : dest(dest), src1(src1), src2(src2), op(op), isFloat(isFloat) {}
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
                result += Instruction::opTypeToString[op] + " " + dest->toString() + ", " + src1->toString() + ", " + src2->toString() + "\n";
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
        return result;
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
        } else if (op == Instruction::ASSIGN_OP) {
            result += "mov " + dest->toString() + ", " + src->toString() + "\n";
        } else {
            throw std::invalid_argument("Invalid unary operation");
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
               "bne " + target->toString() + "\n";
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
            if (i < 4) {
                resultStr += "mov r" + std::to_string(i) + ", " + params[i]->toString() + "\n";
            }
            resultStr += "push {" + params[i]->toString() + "}\n";
        }
        resultStr +=  "bl " + funcName + "(PLT)" + "\n";
        resultStr += "add sp, sp, #" + std::to_string(params.size() * 4) + "\n";
        
        if (result) {
            resultStr += "mov " + result->toString() + ", r0\n";
        }
        // resultStr += "add sp, sp, #" + std::to_string(params.size() * 4) + "\n";
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
        std::string destStr = dest->toString();
        if (dest->isReg()) {
            destStr = "[" + destStr + "]";
        }
        return "str " + src->toString() + ", " + destStr + "\n";
    }
};

class LIRLoadInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> src;
    std::shared_ptr<LIROperand> dest;
    LIRLoadInstruction(std::shared_ptr<LIROperand> src, std::shared_ptr<LIROperand> dest) : src(src), dest(dest) {}
    std::string toString() const override {
        std::string srcStr = src->toString();
        if (src->isReg()) {
            srcStr = "[" + srcStr + "]";
        }        
        return "ldr " + dest->toString() + ", " + srcStr + "\n";
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

class LIRMovInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> dest;
    std::shared_ptr<LIROperand> src;
    LIRMovInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src) : dest(dest), src(src) {}
    std::string toString() const override {
        if (src ->isImm()) {
            if (auto x = std::dynamic_pointer_cast<LIRImmediate>(src)->value){
                int high = (x >> 16) & 0xFFFF;
                int low = x & 0xFFFF;
                if (high != 0) {
                    return "movw " + dest->toString() + ", #" + std::to_string(low) + "\n" +
                           "movt " + dest->toString() + ", #" + std::to_string(high) + "\n";
                }
                else return "mov " + dest->toString() + ", #" + std::to_string(low) + "\n";
            }
        } else return "mov " + dest->toString() + ", " + src->toString() + "\n";
    }
};

class LIRLDRPseudoInstruction : public LIRInstruction {
public:
    std::shared_ptr<LIROperand> dest;
    std::shared_ptr<LIROperand> src;
    LIRLDRPseudoInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src) : dest(dest), src(src) {}
    std::string toString() const override {
        return "ldr " + dest->toString() + ", =" + src->toString() + "\n";
    }
};


class LIRCodeBlock {
public:
    std::string name;
    RegisterManager rm;
    std::vector<std::shared_ptr<LIRInstruction>> instructions;
    int size;
    int argNum;

    std::string onlyInstructions() const {
        std::string result;
        for (const auto& instruction : instructions) {
            result += instruction->toString();
        }
        return result;
    }

    std::string toString() const{
        std::string result;
        result += ".align 1\n";
        result += ".global " + name + "\n";
        result += ".syntax unified \n";
        result += ".thumb\n";
        result += ".thumb_func\n";
        result += ".type " + name + ", %function\n";
        result += name + ":\n";

        result += "sub sp, sp, #" + std::to_string(size - 4 * argNum) + "\n";

        result += "push {" + rm.allUsedRegister() + "lr}\n";

        result += "add	r7, sp, #"+std::to_string(4 * rm.getUsedRegisterCount() + 4)+"\n";
        

        for (const auto& instruction : instructions) {
            
            result += instruction->toString();
        }

        result += "."+name+".ret:\n";

        result += "pop {" + rm.allUsedRegister() + "pc}\n";
        result += "add sp, sp, #" + std::to_string(size - 4 * argNum) + "\n";
        result += "bx lr\n";
        result += ".size " + name + ", .-" + name + "\n";

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
	                ".fpu vfpv3-d16\n"
                    ".eabi_attribute 28, 1\n"
                    ".eabi_attribute 20, 1\n"
                    ".eabi_attribute 21, 1\n"
                    ".eabi_attribute 23, 3\n"
                    ".eabi_attribute 24, 1\n"
                    ".eabi_attribute 25, 1\n"
                    ".eabi_attribute 26, 2\n"
                    ".eabi_attribute 30, 6\n"
                    ".eabi_attribute 34, 1\n"
                    ".eabi_attribute 18, 4\n";

        result += ".data\n";
        result += globalBlock->onlyInstructions() + "\n";  
        result += ".text\n";

        for (const auto& block : codeBlocks) {
            result += block->toString() + "\n";
        }
        return result;
    }
};


class LIRBuilder : public Builder{
public:
    Module module;
    LIRModule lirModule;
    std::shared_ptr<LIRCodeBlock> currentBlock;
    std::shared_ptr<LIROperand> returnLabel;

    std::map<std::shared_ptr<Value>, std::shared_ptr<LIROperand>, Value::ValueCompare> vm;

    LIRBuilder(Module module) : module(module) {
        currentBlock = lirModule.globalBlock;
    }

    void addInstruction(std::shared_ptr<LIRInstruction> instruction) {
        currentBlock->instructions.push_back(instruction);
    }

    void addGlobalVar(std::shared_ptr<LIROperand> label, int size) {
        auto instruction = std::make_shared<LIRGlobalVarInstruction>(label, size);
        addInstruction(instruction);
    }

    void addBinaryInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src1, std::shared_ptr<LIROperand> src2, Instruction::OpType op, bool isFloat = false) {
        if(src1->isImm()) {
            std::swap(src1, src2);
        }
        auto instruction = std::make_shared<LIRBinaryInstruction>(dest, src1, src2, op, isFloat);
        addInstruction(instruction);
   
    }

    void addUnaryInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src, Instruction::OpType op) {
        auto instruction = std::make_shared<UnaryLIRInstruction>(dest, src, op);
        addInstruction(instruction);
    }

    void addBranchInstruction(std::shared_ptr<LIROperand> condition, std::shared_ptr<LIROperand> target) {
        auto instruction = std::make_shared<LIRBranchInstruction>(condition, target);
        addInstruction(instruction);
    }

    void addFuncCallInstruction(std::string funcName, std::vector<std::shared_ptr<LIROperand>> params, std::shared_ptr<LIROperand> result) {
        auto instruction = std::make_shared<LIRFuncCallInstruction>(funcName, params, result);
        addInstruction(instruction);
    }

    void addGotoInstruction(std::shared_ptr<LIROperand> target) {
        auto instruction = std::make_shared<LIRGotoInstruction>(target);
        addInstruction(instruction);
    }

    void addLabelInstruction(std::shared_ptr<LIROperand> label) {
        auto instruction = std::make_shared<LIRLabelInstruction>(label);
        addInstruction(instruction);
    }

    void addStoreInstruction(std::shared_ptr<LIROperand> src, std::shared_ptr<LIROperand> dest) {
        auto instruction = std::make_shared<LIRStoreInstruction>(src, dest);
        addInstruction(instruction);
    }

    void addLoadInstruction(std::shared_ptr<LIROperand> src, std::shared_ptr<LIROperand> dest) {
        auto instruction = std::make_shared<LIRLoadInstruction>(src, dest);
        addInstruction(instruction);
    }

    void addReturnInstruction(std::shared_ptr<LIROperand> value) {
        auto instruction = std::make_shared<LIRReturnInstruction>(value, returnLabel);
        addInstruction(instruction);
    }

    void addMovInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src) {
        auto instruction = std::make_shared<LIRMovInstruction>(dest, src);
        addInstruction(instruction);
    }

    void addLDRPseudoInstruction(std::shared_ptr<LIROperand> dest, std::shared_ptr<LIROperand> src) {
        auto instruction = std::make_shared<LIRLDRPseudoInstruction>(dest, src);
        addInstruction(instruction);
    }

    


    std::shared_ptr<LIROperand>  toRegister(std::shared_ptr<LIROperand> op ){
        if (op->isReg()) {
            return op;
        } else if (op->isLabel()) {
            auto r = currentBlock->rm.get_r();
            addMovInstruction(r, op);
            return r;
        } else if (op->isImm()) {
            auto imm = std::dynamic_pointer_cast<LIRImmediate>(op);
            auto reg = currentBlock->rm.get_r();
            addMovInstruction(reg, imm);
            return reg;

        } else if (op->isAddr()) {
            auto addr = std::dynamic_pointer_cast<LIRAddress>(op);
            auto reg = currentBlock->rm.get_r();
            addBinaryInstruction(reg, std::make_shared<LIRImmediate>(addr->offset), std::make_shared<LIRRegister>(addr->reg), Instruction::ADD_OP);
            return reg;
        } else {
            REPORT_ERROR("toRegister Error");
        }
    }

    std::shared_ptr<LIROperand> noLabel(std::shared_ptr<LIROperand> op) {
        if (op->isReg()) {
            return op;
        } else if (op->isLabel()) {
            auto label = std::dynamic_pointer_cast<LIRLabel>(op);
            auto reg = currentBlock->rm.get_r();
            addLDRPseudoInstruction(reg, label);
            return reg;
        } else if (op->isImm()) {
            return op;
        } else if (op->isAddr()){
            return op;
        } else {
            REPORT_ERROR("noLabel Error");
        }
    }

    std::shared_ptr<LIROperand> AddressToNum(std::shared_ptr<LIROperand> op) {
        if (op->isAddr()) {
            auto addr = std::dynamic_pointer_cast<LIRAddress>(op);
            auto reg = currentBlock->rm.get_r();
            addBinaryInstruction(reg, std::make_shared<LIRImmediate>(addr->offset), std::make_shared<LIRRegister>(addr->reg), Instruction::ADD_OP);
            return reg;
        } else if (op->isReg()) {
            return op;
        } else if (op->isLabel()) {
            auto label = std::dynamic_pointer_cast<LIRLabel>(op);
            auto reg = currentBlock->rm.get_r();
            addLDRPseudoInstruction(reg, label);
            return reg;
        } else if (op->isImm()) {
            return op;
        } else {
            REPORT_ERROR("AddressToNum Error");
        }
    }

    std::shared_ptr<LIROperand> getLabel(Operand op) {
        if(std::holds_alternative<std::shared_ptr<Value>>(op)) {
            auto label = std::make_shared<LIRLabel> (".L"+std::to_string(std::get<std::shared_ptr<Value>>(op)->no));
            return label;
        } else return nullptr;
    }

    int prepareMalloc(CodeBlock & block, bool global = false) {
        int size = 0;
        for (const auto& instruction : block.instructions) {
            if (auto mallocInst = std::dynamic_pointer_cast<MallocInstruction>(instruction)) {
                if (global) {
                    vm[std::get<std::shared_ptr<Value>>(mallocInst->result)] = getLabel(mallocInst->result);
                } else {
                    vm[std::get<std::shared_ptr<Value>>(mallocInst->result)] = std::make_shared<LIRAddress>(size);
                }
                size += OperandToInt(mallocInst->size);
            }
        }
        return size;
    }

    int OperandToInt(Operand op){
        if ( std::holds_alternative<ConstType>(op)) {
            auto f = std::get<ConstType>(op);
            if (std::holds_alternative<int>(f)) {
                return std::get<int>(f);
            } else if (std::holds_alternative<float>(f)) {
                return static_cast<int>(std::get<float>(f));
            } 
        } else if (std::holds_alternative<std::shared_ptr<Value>>(op)) {
            throw std::bad_variant_access();
        }
        throw std::bad_variant_access();
    }

    std::shared_ptr<LIROperand> OperandToLIR(Operand op){
        if (std::holds_alternative<ConstType>(op)) {
            auto f = std::get<ConstType>(op);
            if (std::holds_alternative<int>(f)) {
                return std::make_shared<LIRImmediate>(std::get<int>(f));
            } else if (std::holds_alternative<float>(f)) {
                return std::make_shared<LIRImmediate>(std::get<float>(f));
            }
        } else if (std::holds_alternative<std::shared_ptr<Value>>(op)) {
            if (vm.count(std::get<std::shared_ptr<Value>>(op))) {
                return vm[std::get<std::shared_ptr<Value>>(op)];
            } else {
                auto r = currentBlock->rm.get_r();
                vm[std::get<std::shared_ptr<Value>>(op)] = r;
                return r;
            }
        }
        throw std::bad_variant_access();
    }

    void build(BinaryInstruction& instruction) override{
        auto dest = OperandToLIR(instruction.result);
        auto src1 = AddressToNum(OperandToLIR(instruction.operand1));
        auto src2 = AddressToNum(OperandToLIR(instruction.operand2));
        
        if(src1->isImm() && src2->isImm()){
            src1 = toRegister(src1);
        }  
        

        addBinaryInstruction(dest, src1, src2, instruction.op, instruction.isFloat);
        currentBlock->rm.return_r(src1);
        currentBlock->rm.return_r(src2);
    }

    void build(UnaryInstruction& instruction) override{
        auto dest = OperandToLIR(instruction.result);
        auto src = OperandToLIR(instruction.operand);
        addUnaryInstruction(dest, src, instruction.op);
        currentBlock->rm.return_r(src);
    }
    void build(MallocInstruction& instruction) override{
        auto size = OperandToLIR(instruction.size);
        auto result = OperandToLIR(instruction.result);
        addBinaryInstruction(result, size, std::make_shared<LIRImmediate>(0), Instruction::ADD_OP);
        currentBlock->rm.return_r(size);
    }
    void build(LoadInstruction& instruction) override{
        auto dest = toRegister(OperandToLIR(instruction.result));
        auto src = noLabel( OperandToLIR(instruction.address));
        addLoadInstruction(src, dest);
        currentBlock->rm.return_r(src);
        currentBlock->rm.return_r(dest);
    }
    void build(StoreInstruction& instruction) override{
        auto src = toRegister( OperandToLIR(instruction.value));
        auto dest = noLabel( OperandToLIR(instruction.address) );
        addStoreInstruction(src, dest);
        currentBlock->rm.return_r(src);
        currentBlock->rm.return_r(dest);
    }
    void build(FuncCallInstruction & instruction) override{
        std::vector<std::shared_ptr<LIROperand>> params;
        for (const auto& param : instruction.params) {
            params.push_back(toRegister(AddressToNum(OperandToLIR(param))));
        }
        auto result = OperandToLIR(instruction.result);
        addFuncCallInstruction(instruction.funcName, params, result);
        for (const auto& param : params) {
            currentBlock->rm.return_r(param);
        }
    }

    void build(GotoInstruction& instruction) override{
        auto target = getLabel(instruction.target);
        addGotoInstruction(target);
    }

    void build(BranchInstruction& instruction) override{
        auto condition = OperandToLIR(instruction.condition);
        auto target = getLabel(instruction.target);
        addBranchInstruction(condition, target);
        currentBlock->rm.return_r(condition);
    }

    void build(LabelInstruction& instruction) override{
        auto label = getLabel(instruction.label);
        addLabelInstruction(label);
    }
    void build(ReturnInstruction& instruction) override{
        auto value = OperandToLIR(instruction.value);
        addReturnInstruction(value);
        currentBlock->rm.return_r(value);
    }

    void buildLIR() {
        *output.log << "Building LIR" << std::endl;
        std::shared_ptr<CodeBlock> mainBlock = std::make_shared<CodeBlock>(); 
        prepareMalloc(*module.global, true);
        for (const auto& global : module.global->instructions) {
            if (auto globalVar = std::dynamic_pointer_cast<MallocInstruction>(global)) {
                auto _size = OperandToInt(globalVar->size);
                auto _label = std::make_shared<LIRLabel> (".L"+std::to_string(std::get<std::shared_ptr<Value>>(globalVar->result)->no));
                addGlobalVar(_label, _size);
            }
        }
        *output.log << "Finished building global variables" << std::endl;
        for (const auto& func : module.func) {
            auto block = std::make_shared<LIRCodeBlock>();
            lirModule.codeBlocks.push_back(block);
            currentBlock = block;
            currentBlock->size = prepareMalloc(*func.second);
            currentBlock->argNum = func.second->args_.size();
            returnLabel = std::make_shared<LIRLabel>("."+func.first + ".ret");
            currentBlock->name = func.first;

            if (func.first == "main") {
                for(const auto& global : module.global->instructions) {
                    if (!std::dynamic_pointer_cast<MallocInstruction>(global)) {
                        *output.log << "Building1: " << global->toString() << std::endl;
                        global->build(*this);
                    }
                }
            }
            for (const auto& instruction : func.second->instructions) {
                if(!std::dynamic_pointer_cast<MallocInstruction>(instruction)) {
                    *output.log << "Building2: " << instruction->toString() << std::endl;
                    instruction->build(*this);
                }
            }
        }
        *output.log << "Finished building LIR" << std::endl;

    }
};



#endif // LIR_H