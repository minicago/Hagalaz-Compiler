#include "type.h"

bool SysyType::isSimpleType() const {
    return dynamic_cast<const SimpleType*>(this) != nullptr;
}

bool SysyType::isArrayType() const {
    return dynamic_cast<const ArrayType*>(this) != nullptr;
}

bool SysyType::isVoidType() const {
    return dynamic_cast<const SimpleType*>(this) && static_cast<const SimpleType*>(this)->type == VOID;
}

bool SysyType::matchType(const SysyType &other) const {
    if (isSimpleType() && other.isSimpleType()) {
        return static_cast<const SimpleType*>(this)->type != VOID && static_cast<const SimpleType*>(&other)->type != VOID;
    } else if (isArrayType() && other.isArrayType()) {
        return static_cast<const ArrayType*>(this)->InnerType->matchType(*static_cast<const ArrayType*>(&other)->InnerType) && 
                (static_cast<const ArrayType*>(this)->length == static_cast<const ArrayType*>(&other)->length 
                || static_cast<const ArrayType*>(&other)->length == type::VARIANT_SIZE 
                || static_cast<const ArrayType*>(this)->length == type::VARIANT_SIZE);
    }
    return false;
}