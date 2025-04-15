#ifndef __TYPE_H__
#define __TYPE_H__

#include "def.h"
#include <memory>
#include "y.tab.h"
#include <string>
#include <vector>
#include <variant>
#include <stdexcept>

namespace type
{
    const int VARIANT_SIZE = INT32_MAX;

} // namespace type

class SysyType {
public:
    int size;    
    enum TypeID{
        
        VoidTyID,      // Void
             // Labels, e.g., BasicBlock
        IntegerTyID ,   // Integers, include 32 bits and 1 bit
        FloatTyID ,     // Floats, only 32 bits
        FunctionTyID,  // Functions
        LabelTyID,
    };
    virtual ~SysyType() = default;
    virtual std::string toString() const = 0;

    bool isSimpleType() const;
    bool isArrayType() const;
    bool isVoidType() const; 

    bool matchType(const SysyType &other) const;

    virtual bool isConst() = 0;
    virtual TypeID getSimpleType() = 0;
};

class SimpleType : public SysyType {
public:
    TypeID type;
    bool _isConst;

    SimpleType(TypeID type, bool isConst = false) : type(type), _isConst(isConst) {
        if (type == IntegerTyID) {
            size = sizeof(int);
        } else if (type == FloatTyID) {
            size = sizeof(float);
        } else {
            size = 0;
        }
    }

    SimpleType(yytokentype type, bool isConst = false) : _isConst(isConst) {
        if (type == INT) {
            this->type = IntegerTyID;
            size = sizeof(int);
        } else if (type == FLOAT) {
            this->type = FloatTyID;
            size = sizeof(float);
        } else if (type == VOID) {
            this->type = VoidTyID;
            size = 0;
        } else {
            throw std::invalid_argument("Invalid type");
        }
    }
    std::string toString() const override {
        switch (type) {
            case IntegerTyID: return _isConst ? "const int" : "int";
            case FloatTyID: return _isConst ? "const float" : "float";
            case VoidTyID: return "void";
            case LabelTyID: return "label";
            default: return "unknown";
        }
    }

    bool isConst() override {
        return _isConst;
    }

    TypeID getSimpleType() override {
        return type;
    }
};

class ArrayType : public SysyType {
public:
    std::shared_ptr<SysyType> innerType;
    int length;


    ArrayType(std::shared_ptr<SysyType> InnerType, int length) : innerType(InnerType), length(length) {
        if (length <= 0) {
            throw std::invalid_argument("Array length must be positive");
        }
        size = InnerType->size * length;
    }
    ArrayType(std::shared_ptr<SysyType> InnerType) : innerType(InnerType), length(type::VARIANT_SIZE) {
        size = type::VARIANT_SIZE;
    }

    TypeID getSimpleType() override {
        return innerType->getSimpleType();
    }
    std::string toString() const override {
        return "[" + std::to_string(length) + "]" + innerType->toString();
    }

    bool isConst() override {
        return innerType->isConst();
    }

};

typedef std::variant<std::monostate, int, float, void* > ConstType;

class Value{
private:
    static int count;
public:
    int no;
    Value() : no(count++) {}
};

typedef std::variant<std::shared_ptr<Value>, ConstType> Operand;

class TypeValue {
public:
    std::shared_ptr<SysyType> type;
    std::shared_ptr<char[]> data;
    ConstType const_;
    std::shared_ptr<Value> value;

    bool isConst(){
        return type->isConst();
    }

    bool hasConst(){
        return std::holds_alternative<std::monostate>(const_) == false;
    }   

    TypeValue(std::shared_ptr<SysyType> type, ConstType value)
        : type(type), const_(value), value(nullptr) {}

    TypeValue(std::shared_ptr<SysyType> type)
        : type(type), const_(), value(new Value()){}

    std::string toString() const {
        std::string s = type->toString();
        if (std::holds_alternative<int>(const_)) {
            s += " = " + std::to_string(std::get<int>(const_));
        } else if (std::holds_alternative<float>(const_)) {
            s += " = " + std::to_string(std::get<float>(const_));
        } else if (std::holds_alternative<void*>(const_)) {
            s += " = " + std::to_string(reinterpret_cast<uintptr_t>(std::get<void*>(const_)));
        }
        return s;
    }
    
    ~TypeValue() = default;

    float getFloat() const {
        if (std::holds_alternative<float>(const_)) {
            return std::get<float>(const_);
        } else if (std::holds_alternative<int>(const_)) {
            return static_cast<float>(std::get<int>(const_));
        } else {
            throw std::bad_variant_access();
        }
    }

    int getInt() const {
        if (std::holds_alternative<int>(const_)) {
            return std::get<int>(const_);
        } else if (std::holds_alternative<float>(const_)) {
            return static_cast<int>(std::get<float>(const_));
        } else {
            throw std::bad_variant_access();
        }
    }

    TypeValue get_index(int index){
        *output.log << "get_index" << std::endl;
        *output.log << "index: " << index << std::endl;
        *output.log << "type: " << (hasConst()?1:0) << std::endl;
        if (type->isArrayType()){
            auto arrayType = std::dynamic_pointer_cast<ArrayType>(type);
            if (arrayType->length > index){
                auto ptr = type->isConst()? std::get<void* >(const_) : nullptr;
                if (arrayType->innerType->isSimpleType()){
                    auto simpleType = std::dynamic_pointer_cast<SimpleType>(arrayType->innerType);
                    if (simpleType->type == SysyType::IntegerTyID){
                        if(type->isConst()) return TypeValue(arrayType->innerType,  ((int*)(ptr))[index]);
                        else return TypeValue(arrayType->innerType);
                    } else if (simpleType->type == SysyType::FloatTyID){
                        if(type->isConst()) return TypeValue(arrayType->innerType,  ((float*)(ptr))[index]);
                        else return TypeValue(arrayType->innerType);
                    } 
                }  else {
                    if(type->isConst()) return TypeValue(arrayType->innerType,  ptr + index * arrayType->innerType->size);
                    else return TypeValue(arrayType->innerType); 
                }
            } else {
                throw std::out_of_range("Index out of range");
            }
        } else {
            throw std::invalid_argument("Type is not an array");
        }
    } 
    Operand getOperand() {
        if (hasConst()) {
            return const_;
        } else if (value) {
            return value;
        } else {
            throw std::invalid_argument("No value or const");
        }
    }
    
};

#endif