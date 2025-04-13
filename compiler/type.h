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
    virtual ~SysyType() = default;
    virtual std::string toString() const = 0;

    bool isSimpleType() const;
    bool isArrayType() const;
    bool isVoidType() const; 

    bool matchType(const SysyType &other) const;

    virtual bool isConst() = 0;
    virtual yytokentype getSimpleType() = 0;
};

class SimpleType : public SysyType {
public:
    yytokentype type;
    bool _isConst;

    SimpleType(yytokentype type, bool isConst = false) : type(type), _isConst(isConst) {
        if (type == INT) {
            size = sizeof(int);
        } else if (type == FLOAT) {
            size = sizeof(float);
        } else if (type == VOID) {
            size = 0;
        } else {
            throw std::invalid_argument("Invalid type");
        }
    }
    std::string toString() const override {
        switch (type) {
            case INT: return _isConst ? "const int" : "int";
            case FLOAT: return _isConst ? "const float" : "float";
            case VOID: return "void";
            default: return "unknown";
        }
    }

    bool isConst() override {
        return _isConst;
    }

    yytokentype getSimpleType() override {
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

    yytokentype getSimpleType() override {
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

class TypeValue {
public:
    std::shared_ptr<SysyType> type;
    std::shared_ptr<char[]> data;
    ConstType value;

    bool isConst(){
        return type->isConst();
    }

    bool hasValue(){
        return std::holds_alternative<std::monostate>(value) == false;
    }   

    TypeValue(std::shared_ptr<SysyType> type, ConstType value)
        : type(type), value(value) {}

    TypeValue(std::shared_ptr<SysyType> type)
        : type(type), value() {}

    std::string toString() const {
        std::string s = type->toString();
        if (std::holds_alternative<int>(value)) {
            s += " = " + std::to_string(std::get<int>(value));
        } else if (std::holds_alternative<float>(value)) {
            s += " = " + std::to_string(std::get<float>(value));
        } else if (std::holds_alternative<void*>(value)) {
            s += " = " + std::to_string(reinterpret_cast<uintptr_t>(std::get<void*>(value)));
        }
        return s;
    }
    
    ~TypeValue() = default;

    float getFloat() const {
        if (std::holds_alternative<float>(value)) {
            return std::get<float>(value);
        } else if (std::holds_alternative<int>(value)) {
            return static_cast<float>(std::get<int>(value));
        } else {
            throw std::bad_variant_access();
        }
    }

    int getInt() const {
        if (std::holds_alternative<int>(value)) {
            return std::get<int>(value);
        } else if (std::holds_alternative<float>(value)) {
            return static_cast<int>(std::get<float>(value));
        } else {
            throw std::bad_variant_access();
        }
    }

    TypeValue get_index(int index){
        *output.log << "get_index" << std::endl;
        *output.log << "index: " << index << std::endl;
        *output.log << "type: " << type->toString() << std::endl;
        if (type->isArrayType()){
            auto arrayType = std::dynamic_pointer_cast<ArrayType>(type);
            if (arrayType->length > index){
                auto ptr = type->isConst()? std::get<void* >(value) : nullptr;
                if (arrayType->innerType->isSimpleType()){
                    auto simpleType = std::dynamic_pointer_cast<SimpleType>(arrayType->innerType);
                    if (simpleType->type == INT){
                        if(type->isConst()) return TypeValue(arrayType->innerType,  ((int*)(ptr))[index]);
                        else return TypeValue(arrayType->innerType);
                    } else if (simpleType->type == FLOAT){
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
    
};



#endif