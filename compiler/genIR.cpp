#include "genIR.h"
#include "output.h"
#include "tool.h"
#include <cstring>

void GenIR::visit(ExprNode &node) {
    if (node.val1){
       node.val1->accept(*this); 
    } 
    
    node.val2->accept(*this);
    auto val1Result = node.val1 ? result[node.val1] : CheckerResult( TypeValue(std::make_shared<SimpleType>(SysyType::IntegerTyID), 0));
    auto val2Result = result[node.val2];


    // check if val1 and val2 are valid
    if (!val1Result.value || !val2Result.value) {
        throw std::runtime_error("Invalid value in expression.");
        return;
    }

    if (!val1Result.value->type->isSimpleType() || !val2Result.value->type->isSimpleType()) {
        throw std::runtime_error("Invalid type in expression.");
        return;
    }

    

    auto val1Type = std::dynamic_pointer_cast<SimpleType>(val1Result.value->type);
    auto val2Type = std::dynamic_pointer_cast<SimpleType>(val2Result.value->type);

    auto op_int = [](yytokentype op, int v1, int v2){
        switch (op) {
            case ADD: return v1 + v2;
            case SUB: return v1 - v2;
            case MUL: return v1 * v2;
            case DIV: if (v2 == 0)  ; return v1 / v2;
            case MOD: if (v2 == 0)  ; return v1 % v2;


        }
        return 0;
    };
    auto op_float = [](yytokentype op, float v1, float v2){
        switch (op) {
            case ADD: return v1 + v2;
            case SUB: return v1 - v2;
            case MUL: return v1 * v2;
            case DIV: return v1 / v2;

        }
        return 0.0f;
    };

    auto op_bool = [](yytokentype op, float v1, float v2){
        switch (op) {
            case AND: return v1 && v2;
            case OR: return v1 || v2;
            case EQ: return v1 == v2;
            case NE: return v1 != v2;
            case GE: return v1 >= v2;
            case LE: return v1 <= v2;
            case GT: return v1 > v2;
            case LT: return v1 < v2;
            case NOT: return !v2;
        }
        return false;
    };
    

    result[std::make_shared<ExprNode>(node)] = CheckerResult();


    // *output.log << "val1" << val1Result.value->toString() << std::endl;
    // *output.log << "val2" << val2Result.value->toString() << std::endl;
    
    // Check if the result is a constant
    if (val1Result.value->isConst() && val2Result.value->isConst()) {
        if (node.op == NE || node.op == GE || node.op == LE || node.op == GT || node.op == LT || node.op == AND || node.op == OR || node.op == EQ || node.op == NOT) { 
            auto val1Float = val1Result.value->getInt();
            auto val2Float = val2Result.value->getInt();
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(SysyType::IntegerTyID, true), op_bool(node.op, val1Float, val2Float));

        } else {
            if (val1Type->type == SysyType::IntegerTyID && val2Type->type == SysyType::IntegerTyID){
                auto val1Int = std::get<int>(val1Result.value->const_);
                auto val2Int = std::get<int>(val2Result.value->const_);
                result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(SysyType::IntegerTyID, true), op_int(node.op, val1Int, val2Int));
            } else if (val1Type->type == SysyType::FloatTyID || val2Type->type == SysyType::FloatTyID) {
                auto val1Float = val1Result.value->getFloat();
                auto val2Float = val2Result.value->getFloat();
                result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(SysyType::FloatTyID, true), op_float(node.op, val1Float, val2Float));
            }   else {
                throw std::runtime_error("Invalid type in expression.");
                return;
            }      
        } 
    } else {
    // Determine the result type
        if (node.op == NOT){
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(SysyType::IntegerTyID));
            builder.addUnaryInstruction(val2Result.value->getOperand(), result[std::make_shared<ExprNode>(node)].value->value, node.op);
        } else if (node.op == NE || node.op == GE || node.op == LE || node.op == GT || node.op == LT || node.op == AND || node.op == OR || node.op == EQ || node.op == NOT) {
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(SysyType::IntegerTyID));
            if(val1Type->type == SysyType::IntegerTyID && val2Type->type == SysyType::IntegerTyID){
                builder.addBinaryInstruction(builder.getIntOperand(*val1Result.value), builder.getIntOperand(*val2Result.value), result[std::make_shared<ExprNode>(node)].value->value, node.op);
            } else {
                builder.addBinaryInstruction(builder.getFloatOperand(*val1Result.value), builder.getFloatOperand(*val2Result.value), result[std::make_shared<ExprNode>(node)].value->value, node.op, true);
            }
            
            
        } else if (val1Type->type == SysyType::FloatTyID || val2Type->type == SysyType::FloatTyID) {
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(SysyType::FloatTyID));
            builder.addBinaryInstruction(builder.getFloatOperand(*val1Result.value), builder.getFloatOperand(*val2Result.value), result[std::make_shared<ExprNode>(node)].value->value, node.op, true);
            
        } else if (val1Type->type == SysyType::IntegerTyID && val2Type->type == SysyType::IntegerTyID) {
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(SysyType::IntegerTyID));
            builder.addBinaryInstruction(builder.getIntOperand(*val1Result.value), builder.getIntOperand(*val2Result.value), result[std::make_shared<ExprNode>(node)].value->value, node.op);
        } else {
            throw std::runtime_error("Invalid type in expression.");
            return;
        }
        
    }
    
    *output.log << "Finished visiting ExprNode" << std::endl;
}

void GenIR::visit(IfElseNode &node) {
    *output.log << "Visiting IfElseNode" << std::endl;

    node.cond->accept(*this);

    auto condResult = result[node.cond];

    if (condResult.value->isConst()) {
        // If condition is constant, set relocateNode to the corresponding branch
        condResult.relocateNode = (condResult.value->getFloat()) ? node.ifstmt : node.elsestmt;
        if (condResult.relocateNode) {
            condResult.relocateNode->accept(*this);
        }
    } else {
        // Regular handling of IfElseNode
        auto iflabel = builder.newValue(), finallabel = builder.newValue(); // Create a new Node for the if label
        builder.addBranchInstruction(condResult.value->value, iflabel);
        if (node.elsestmt) {
            node.elsestmt->accept(*this);
        }
        builder.addGotoInstruction(finallabel);
        builder.addLabelInstruction(iflabel);
        node.ifstmt->accept(*this);
        builder.addLabelInstruction(finallabel);
    }
    *output.log << "Finished visiting IfElseNode" << std::endl;
}

void GenIR::visit(WhileNode &node) {
    *output.log << "Visiting WhileNode" << std::endl;
    
    auto loopLabel = builder.newValue(); // Create a new Node for the loop label
    auto loopEndLabel = builder.newValue(); // Create a new Node for the loop end label
    
    breakStack.push(loopEndLabel);
    continueStack.push(loopLabel);

    builder.addLabelInstruction(loopLabel);
    node.cond->accept(*this);
    auto reverseCond = builder.newValue();
    builder.addUnaryInstruction(result[node.cond].value->value, reverseCond, NOT);
    builder.addBranchInstruction(reverseCond, loopEndLabel);
    
    node.stmt->accept(*this);

    builder.addGotoInstruction(loopLabel);
    
    builder.addLabelInstruction(loopEndLabel); 

    breakStack.pop();
    continueStack.pop();

    *output.log << "Finished visiting WhileNode" << std::endl;
}

void GenIR::visit(BreakNode &node) {
    *output.log << "Visiting BreakNode" << std::endl;
    if (breakStack.empty()) {
        REPORT_ERROR("Break statement outside of a loop.");
        return;
    }

    result[std::make_shared<BreakNode>(node)] = CheckerResult();
    builder.addGotoInstruction(breakStack.top());// Use shared_ptr<Node>
    *output.log << "Finished visiting BreakNode" << std::endl;
}

void GenIR::visit(ContinueNode &node) {
    *output.log << "Visiting ContinueNode" << std::endl;
    if (continueStack.empty()) {
        REPORT_ERROR("Continue statement outside of a loop.");
        return;
    }

    result[std::make_shared<ContinueNode>(node)] = CheckerResult();
    builder.addGotoInstruction(continueStack.top());
    *output.log << "Finished visiting ContinueNode" << std::endl;
}

void GenIR::visit(ReturnNode &node) {
    *output.log << "Visiting ReturnNode" << std::endl;
    if (!currentFunction) {
        REPORT_ERROR("Return statement outside of a function.");
        return;
    }


    if (node.expr) {
        node.expr->accept(*this);
        auto exprResult = result[node.expr];// Access function ID from Node
        if (!exprResult.value->type->matchType(*result[currentFunction].value->type)){
            REPORT_ERROR("return type mismatched");
        }
    }
    

    result[std::make_shared<ReturnNode>(node)] = CheckerResult();
    builder.addReturnInstruction(result[node.expr].value->getOperand());
    result[std::make_shared<ReturnNode>(node)].jumpTarget = currentFunction; // Use shared_ptr<Node>
    *output.log << "Finished visiting ReturnNode" << std::endl;
}

void GenIR::visit(FuncDefNode &node) {
    *output.log << "Visiting FuncDefNode" << std::endl;
    *output.log << "Function definition: " << node.id << std::endl;
    currentFunction = std::make_shared<FuncDefNode>(node); // Assign current function as a Node
    auto funcDecl = std::make_shared<FuncDecl>(node.type, node.id, node);
    
    scope.enterBlock();
    builder.newBlock(node.id);

    std::stack<Operand> argOperand;

    if (node.param) {
        node.param->accept(*this);
        
        funcDecl->paramList = std::make_shared<std::vector<std::shared_ptr<VarDecl>>>();
        for (auto &param : std::dynamic_pointer_cast<ParamListNode> (node.param) ->paramlist) {
            auto paramResult = result[param];
            auto arg = scope.findVar(std::dynamic_pointer_cast<ParamNode> (param)->id);
            funcDecl->paramList->push_back(arg);
            if (arg->typeValue.type->isArrayType()) {
                // auto newValue = builder.newValue();
                // builder.addLoadInstruction(arg->typeValue.getOperand(), newValue);
                // scope.addVar(arg->id, 
                //     std::make_shared<VarDecl>(arg->id, 
                //         TypeValue(std::get<std::shared_ptr<Value> >(newValue),
                //             arg->typeValue.type)
                //         ),
                //     true);
            }
            builder.addFuncArg(scope.findVar(std::dynamic_pointer_cast<ParamNode> (param)->id)->typeValue.value);
            argOperand.push(paramResult.value->getOperand());
        }
    }
    
    
    

    scope.addFunc(node.id, funcDecl);
    result[std::make_shared<FuncDefNode>(node)] = CheckerResult(funcDecl);


    if (node.stmt) {
        node.stmt->accept(*this);
        funcDecl->stmt = node.stmt;
    }
    while(!argOperand.empty()) {
        auto arg = argOperand.top();
        argOperand.pop();
        builder.addMallocInstruction(4, arg);
        
    }

    scope.exitBlock();
    currentFunction.reset(); // Clear current function
    builder.switchToGlobal();
    *output.log << "Finished visiting FuncDefNode" << std::endl;

}

void GenIR::visit(FuncCallNode &node) {
    *output.log << "Visiting FuncCallNode" << std::endl;
    auto func = scope.findFunc(node.id);
    if (!func) {
        REPORT_ERROR("Function " + node.id + " not declared.");
        return;
    }
    if (node.param) {
        node.param->accept(*this);
    }
    auto params = std::dynamic_pointer_cast<FuncCallParamNode> (node.param);
    if (func->paramList->size() != params->paramlist.size()) {
        REPORT_ERROR("Function " + node.id + " parameter count mismatch.");
        return;
    }
    
    std::vector<Operand> args;
    for (size_t i = 0; i < func->paramList->size(); ++i) {
        auto paramDecl = func->paramList->at(i);
        auto argResult = params->paramlist[i];
        auto argType = result[argResult].value;
        if (!argType) {
            REPORT_ERROR("Function " + node.id + " argument type mismatch.");
            return;
        }
        if (!paramDecl->typeValue.type->matchType(*argType->type)) {
            REPORT_ERROR("Function " + node.id + " parameter type mismatch.");
            return;
        }
        args.push_back(argType->getOperand());
    }
    result[std::make_shared<FuncCallNode>(node)] = CheckerResult(func);
    builder.addFuncCallInstruction(node.id, args, result[std::make_shared<FuncCallNode>(node)].value->value);
    *output.log << "Finished visiting FuncCallNode" << std::endl;
}

void GenIR::visit(ParamNode &node) {   
    *output.log << "Visiting ParamNode" << std::endl;
    std::shared_ptr<SysyType> type = std::make_shared<SimpleType>(node.type);
    
    if (node.arraySize) {
        constructingType = type;
        node.arraySize->accept(*this);
        type = constructingType;
        constructingType = nullptr;
    }

    
    if (node.isptr) {
        type = std::make_shared<ArrayType>(type);
    }
    auto varDecl = std::make_shared<VarDecl>(node.id, TypeValue(type), node);
   
    scope.addVar(node.id, varDecl); 
    
    result[std::make_shared<ParamNode>(node)] = CheckerResult(varDecl);
    *output.log << "Finished visiting ParamNode" << std::endl;
}

void GenIR::visit(ParamListNode &node) {
    *output.log << "Visiting ParamListNode" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
    *output.log << "Finished visiting ParamListNode" << std::endl;
}

void GenIR::visit(FuncCallParamNode &node) {
    *output.log << "Visiting FuncCallParamNode" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
    *output.log << "Finished visiting FuncCallParamNode" << std::endl;
}

void GenIR::visit(CompUnitNode &node) {
    *output.log << "Visiting CompUnitNode" << std::endl;
    for (auto &def : node.deflist) {
        def->accept(*this);
    }
    *output.log << "Finished visiting CompUnitNode" << std::endl;
}

void GenIR::visit(StmtListNode &node) {
    *output.log << "Visiting StmtListNode" << std::endl;
    for (auto &stmt : node.stmtlist) {
        stmt->accept(*this);
        if(result.count(stmt) && result[stmt].relocateNode != nullptr) {
            stmt = result[stmt].relocateNode;
            result[stmt].relocateNode = nullptr; // Reset after use
        }
    }
    *output.log << "Finished visiting StmtListNode" << std::endl;
}

void GenIR::visit(AssignNode &node) {
    *output.log << "Visiting AssignNode" << std::endl;
    isAssign = true;
    node.left->accept(*this);
    node.expr->accept(*this);
    builder.addStoreInstruction(result[node.expr].value->getOperand(), result[node.left].value->getOperand());
    // ...existing code for assignment validation...
    *output.log << "Finished visiting AssignNode" << std::endl;
}

void GenIR::visit(VectorNode &node) {
    *output.log << "Visiting vectorNode" << std::endl;
    if (constructingType){
        *output.log << "Constructing type: " << constructingType->toString() << std::endl;
        for (auto element = node.list.rbegin(); element != node.list.rend(); ++element) {
            (*element)->accept(*this);
            if (!result[*element].value) {
                REPORT_ERROR("Invalid value in vector initialization.");
                return;
            }
            
            *output.log << "Element type: " << result[*element].value->type->toString() << std::endl;

            if (!result[*element].value->type->isSimpleType() || result[*element].value->type->isVoidType()) {
                REPORT_ERROR("Invalid type in vector initialization.");
                return;
            }

            if (!result[*element].value->isConst() ){
                REPORT_ERROR("Invalid value in vector initialization.");
                return;
            }

            int length = result[*element].value->getInt();
            constructingType = std::make_shared<ArrayType>(constructingType, length);
            *output.log << "Constructing type: " << constructingType->toString() << std::endl;
        }
    }


    if (constructingValue){

        bool isConst = constructingValue->type->isConst();

        bool init = false;
        int initIndex = 0;
        if (!constructingValue->hasConst()) {
            init = true;
            if (isConst){
                
                constructingValue->data = std::shared_ptr<char[]>(new char[constructingValue->type->size]);
                constructingValue->const_ = &(constructingValue->data[0]);
                // constructingValue->value = std::make_shared<void>(std::get<void*> (constructingValue->value));
                memset(std::get<void*> (constructingValue->const_), 0, constructingValue->type->size);                
            }
            constructingIndex = 0;
        } else {
            if (constructingIndex % constructingValue->type->size != 0) {
                constructingIndex += constructingValue->type->size - constructingIndex % constructingValue->type->size;
            } 
            initIndex = constructingIndex;
        }
        auto simpleType = constructingValue->type->getSimpleType();
        
        for (auto &element : node.list) {
            // *output.log << "Constructing index1: " << constructingIndex << std::endl;
            auto tmpType = constructingValue->type;
            constructingValue->type = std::dynamic_pointer_cast<ArrayType>(constructingValue->type)->innerType;
            element->accept(*this);
            constructingValue->type = tmpType;
            if (result.count(element)) {
                if (!result[element].value) {
                    REPORT_ERROR("Invalid value in vector initialization.");
                    return;
                }
                *output.log << "Element type: " << result[element].value->type->toString() << std::endl;
                if (!result[element].value->type->isSimpleType() || result[element].value->type->isVoidType()) {
                    REPORT_ERROR("Invalid type in vector initialization.");
                    return;
                }

                auto ptr = builder.newValue();
                if(!isConst){
                    builder.addBinaryInstruction(constructingValue->getOperand(), Instruction::constInt(constructingIndex), ptr, ADD);
                    if(simpleType == SysyType::IntegerTyID){
                        builder.addStoreInstruction(builder.getIntOperand(*result[element].value) ,ptr);
                        constructingIndex += sizeof(int);
                    } else {
                        builder.addStoreInstruction(builder.getFloatOperand(*result[element].value) ,ptr);
                        constructingIndex += sizeof(float);
                    }
                } else if(result[element].value->isConst() && isConst){
                    if(simpleType == SysyType::IntegerTyID){
                        auto val = result[element].value->getInt();                        
                        memcpy(std::get<void*> (constructingValue->const_) + constructingIndex, &val, sizeof(int));
                        constructingIndex += sizeof(int);
                    } else if(simpleType == SysyType::FloatTyID){
                        auto val = result[element].value->getFloat();
                        memcpy(std::get<void*> (constructingValue->const_) + constructingIndex, &val, sizeof(float));
                        constructingIndex += sizeof(float);
                    }   
                } else if (isConst){
                    REPORT_ERROR("Invalid value in vector initialization.");
                }      
            }
        }
        if (init) {
            if (constructingIndex > constructingValue->type->size) {
                REPORT_ERROR("Vector initialization size mismatch. Expected " + std::to_string(constructingValue->type->size) + " but got " + std::to_string(constructingIndex) + ".");
                return;
            }
            constructingIndex = 0;
            // constructingValue = nullptr;            
            
        } else {
            
            if (constructingIndex == initIndex) {
                constructingIndex += constructingValue->type->size;
            }
            if (constructingIndex % constructingValue->type->size != 0) {
                constructingIndex += constructingValue->type->size - constructingIndex % constructingValue->type->size;
            } 
            
        }
    }

    *output.log << "Finished visiting vectorNode" << std::endl;
}

void GenIR::visit(DeclNode &node) {
    *output.log << "Visiting DeclNode" << std::endl;
    
    std::shared_ptr<SysyType> type = std::make_shared<SimpleType>(node.type, node.isConst);
    

    constructingType = type;

    if (node.arraySize) {
        node.arraySize->accept(*this);
        type = constructingType;
        *output.log << "type " << type->toString() << std::endl;
    }

    constructingType = nullptr;

    auto value = std::make_shared<TypeValue>(type);


    
    builder.addMallocInstruction(type->size, value->value);

    constructingValue = value;

        
    if (node.initval) {
        node.initval->accept(*this);
        if(result.count(node.initval)){
            if(!type->matchType(*result[node.initval].value->type) || !type->isSimpleType() ){
                REPORT_ERROR("NOT MATCH TYPE");
                return ;
            }
            if(std::dynamic_pointer_cast<SimpleType>(type)->type == SysyType::IntegerTyID ) {
                if(node.isConst) {
                    if (!result[node.initval].value->isConst()){
                        REPORT_ERROR("Invalid value in vector initialization.");
                    }
                    value->const_ = result[node.initval].value->getInt();
                } 
                builder.addStoreInstruction(builder.getIntOperand(*result[node.initval].value), value->value);
            } else  if(std::dynamic_pointer_cast<SimpleType>(type)->type == SysyType::FloatTyID ) {
                if(node.isConst) {
                    if (!result[node.initval].value->isConst()){
                        REPORT_ERROR("Invalid value in vector initialization.");
                    }
                    value->const_ = result[node.initval].value->getFloat();
                }
                builder.addStoreInstruction(builder.getFloatOperand(*result[node.initval].value), value->value);
            }
        }
    }

    constructingValue = nullptr;

    
    
    
    


    auto decl = std::make_shared<VarDecl>(node.id, *value, node);


    if (currentFunction) {
        scope.addVar(node.id, decl); 
     } else scope.addGlobalVar(node.id, decl);

    
    result[std::make_shared<DeclNode>(node)] = CheckerResult(decl);

    
    *output.log << "Finished visiting DeclNode" << std::endl;
}

void GenIR::visit(ConstIntNode &node) {
    *output.log << "Visiting ConstIntNode" << std::endl;
    result[std::make_shared<ConstIntNode>(node)] = CheckerResult(TypeValue(std::make_shared<SimpleType>(SysyType::IntegerTyID, true), node.val));
    *output.log << "Finished visiting ConstIntNode" << std::endl;
}

void GenIR::visit(ConstFloatNode &node) {
    *output.log << "Visiting ConstFloatNode" << std::endl;
    result[std::make_shared<ConstFloatNode>(node)] = CheckerResult(TypeValue(std::make_shared<SimpleType>(SysyType::FloatTyID, true), node.val));
    *output.log << "Finished visiting ConstFloatNode" << std::endl;
}

void GenIR::visit(IdentifierNode &node) {
    *output.log << "Visiting IdentifierNode" << std::endl;
    auto var = scope.findVar(node.id);
    if (!var) {
        REPORT_ERROR("Variable " + node.id + " not declared.");
        return;
    }
    result[std::make_shared<IdentifierNode>(node)] = 
        CheckerResult(var);
    *output.log << "Finished visiting IdentifierNode" << std::endl;
}

void GenIR::visit(SimpleTokenNode &node) {
    *output.log << "Visiting SimpleTokenNode" << std::endl;
    // ...existing code for handling simple tokens...
    *output.log << "Finished visiting SimpleTokenNode" << std::endl;
}

void GenIR::visit(BlockGroupNode &node) {
    *output.log << "Visiting BlockGroupNode" << std::endl;
    scope.enterBlock();
    for (auto &block : node.blocklist) {
        block->accept(*this);
    }
    scope.exitBlock();
    *output.log << "Finished visiting BlockGroupNode" << std::endl;
}

void GenIR::visit(LvalNode &node) {
    *output.log << isAssign << std::endl;
    bool isAssign_ = isAssign;
    isAssign = false;
    
    *output.log << "Visiting LvalNode" << std::endl;
    auto var = scope.findVar(node.id);
    if (!var) {
        REPORT_ERROR("Variable " + node.id + " not declared.");
        return;
    }
    auto typeValue = var->typeValue;
    if(var->typeValue.type->isArrayType() 
        && std::dynamic_pointer_cast<ArrayType> (var->typeValue.type)->length == type::VARIANT_SIZE){
            auto value = builder.newValue();
            builder.addLoadInstruction(var->typeValue.getOperand(), value);
            typeValue.value = std::get<std::shared_ptr<Value> > (value);
    }   
    bool allConst = var->typeValue.type->isConst();
    bool indexConst = true;

    if (node.arrayIndex) {
        
        size_t offset = 0;
        std::shared_ptr<Value> value = typeValue.value;
        for(auto &index : std::dynamic_pointer_cast<VectorNode> (node.arrayIndex)->list) {
            index->accept(*this);
            auto indexResult = result[index];
            if (!indexResult.value) {
                REPORT_ERROR("Invalid array index.");
                return;
            }

            if (indexResult.value->type->isSimpleType() == false) {
                REPORT_ERROR("Array index must be an integer.");
                return;
            }

            if (std::dynamic_pointer_cast<SimpleType>(indexResult.value->type)->type != SysyType::IntegerTyID
            && std::dynamic_pointer_cast<SimpleType>(indexResult.value->type)->type != SysyType::FloatTyID) {
                REPORT_ERROR("Array index must be an integer.");
                return;
            }

            if (indexResult.value->type->isConst()) {
                auto indexValue = indexResult.value->getInt();
                if (indexValue < 0 || indexValue >= std::dynamic_pointer_cast<ArrayType>(typeValue.type)->length) {
                    REPORT_ERROR("Array index out of bounds.");
                    return;
                }
            }

            allConst = allConst && indexResult.value->type->isConst(); 
            indexConst = indexConst && indexResult.value->type->isConst();

            if(indexConst){
                *output.log << "Array is constant." << std::endl;
                auto indexValue = indexResult.value->getInt();
                *output.log << typeValue.type->toString() << std::endl;
                
                typeValue = typeValue.get_index(indexValue);
                offset += typeValue.type->size * indexValue;
            } else {
                *output.log << "Array is not constant." << std::endl;
                if (offset) {
                    std::shared_ptr<Value>  tmp = std::make_shared<Value> ();
                    builder.addBinaryInstruction(Instruction::constInt(offset), value, tmp, ADD);
                    value = tmp;
                }
                typeValue = typeValue.get_index(0);

                std::shared_ptr<Value>  tmp1 = std::make_shared<Value> (), tmp2 = std::make_shared<Value> ();
                builder.addBinaryInstruction(Instruction::constInt(typeValue.type->size), indexResult.value->getOperand(), tmp1, MUL);
                builder.addBinaryInstruction(value, tmp1, tmp2, ADD);
                value = tmp2;               

                allConst = false;
            }

            *output.log << typeValue.type->toString() << std::endl;
             

        }
        if(indexConst&&!allConst){
            auto tmp = std::make_shared<Value> ();
            builder.addBinaryInstruction(Instruction::constInt(offset), value, tmp, ADD);
            value = tmp;
        } 
        if(allConst) {
            result[std::make_shared<LvalNode>(node)] = CheckerResult(typeValue);
        } else {
            result[std::make_shared<LvalNode>(node)] = CheckerResult(TypeValue(value ,typeValue.type));
        }
    }
    else result[std::make_shared<LvalNode>(node)] = CheckerResult( var->typeValue);
    *output.log << allConst << " " << isAssign_ << std::endl;
    if (allConst) {
        if(isAssign_) {
            REPORT_ERROR("assign a constant");
        } else {
            result[std::make_shared<LvalNode>(node)].value->value = nullptr;
        }
    } else if (!isAssign_ && result[std::make_shared<LvalNode>(node)].value->type->isSimpleType()) {
        std::shared_ptr<Value>  tmp = std::make_shared<Value> ();
        builder.addLoadInstruction(result[std::make_shared<LvalNode>(node)].value->value, tmp);
        result[std::make_shared<LvalNode>(node)].value->value = tmp;
    }
    *output.log << result[std::make_shared<LvalNode>(node)].value->toString() << std::endl;
    *output.log << "Finished visiting LvalNode" << std::endl;
}
