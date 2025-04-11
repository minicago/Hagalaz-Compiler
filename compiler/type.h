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
};

class SimpleType : public SysyType {
public:
    yytokentype type;

    SimpleType(yytokentype type) : type(type) {
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
            case INT: return "int";
            case FLOAT: return "float";
            case VOID: return "void";
            default: return "unknown";
        }
    }
};

class ArrayType : public SysyType {
public:
    std::shared_ptr<SysyType> InnerType;
    int length;
    std::string toString() const override {
        return "[" + std::to_string(length) + "]" + InnerType->toString();
    }

    ArrayType(std::shared_ptr<SysyType> InnerType, int length) : InnerType(InnerType), length(length) {
        if (length <= 0) {
            throw std::invalid_argument("Array length must be positive");
        }
        size = InnerType->size * length;
    }
    ArrayType(std::shared_ptr<SysyType> InnerType) : InnerType(InnerType), length(type::VARIANT_SIZE) {
        size = type::VARIANT_SIZE;
    }
    yytokentype getSimpleType() {
        if (InnerType->isSimpleType()) {
            return std::dynamic_pointer_cast<SimpleType>(InnerType)->type;
        } else {
            return std::dynamic_pointer_cast<ArrayType>(InnerType)->getSimpleType();
        }
    }
};

typedef std::variant<std::monostate, int, float, void* > ConstType;

class TypeValue {
public:
    std::shared_ptr<SysyType> type;
    std::shared_ptr<char[]> data;
    ConstType value;

    TypeValue(std::shared_ptr<SysyType> type, ConstType value)
        : type(type), value(value) {}

    TypeValue(std::shared_ptr<SysyType> type)
        : type(type), value() {}

    ~TypeValue() = default;
    
    bool isConst() const {
        return not std::holds_alternative<std::monostate>(value);
    }

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
                auto ptr = std::get<void* >(value);
                if (arrayType->InnerType->isSimpleType()){
                    auto simpleType = std::dynamic_pointer_cast<SimpleType>(arrayType->InnerType);
                    if (simpleType->type == INT){
                        if(isConst()) return TypeValue(arrayType->InnerType,  ((int*)(ptr))[index]);
                        else return TypeValue(arrayType->InnerType);
                    } else if (simpleType->type == FLOAT){
                        if(isConst()) return TypeValue(arrayType->InnerType,  ((float*)(ptr))[index]);
                        else return TypeValue(arrayType->InnerType);
                    } 
                }  else {
                    if(isConst()) return TypeValue(arrayType->InnerType,  ptr + index * arrayType->InnerType->size);
                    else return TypeValue(arrayType->InnerType); 
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