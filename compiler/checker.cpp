#include "checker.h"
#include "output.h"
#include "tool.h"
#include <cstring>

void Checker::visit(ExprNode &node) {
    if (node.val1){
       node.val1->accept(*this); 
    } 
    
    node.val2->accept(*this);
    auto val1Result = node.val1 ? result[node.val1] : checkerResult({}, TypeValue(std::make_shared<SimpleType>(INT), 0));
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
    

    result[std::make_shared<ExprNode>(node)] = checkerResult();



    // Check if the result is a constant
    if (val1Result.value->isConst() && val2Result.value->isConst()) {
        if (node.op == NE || node.op == GE || node.op == LE || node.op == GT || node.op == LT || node.op == AND || node.op == OR || node.op == EQ || node.op == NOT) { 
            auto val1Float = std::get<float>(val1Result.value->value);
            auto val2Float = std::get<float>(val2Result.value->value);
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(INT), op_bool(node.op, val1Float, val2Float));

        } else {
            if (val1Type->type == INT && val2Type->type == INT){
                auto val1Int = std::get<int>(val1Result.value->value);
                auto val2Int = std::get<int>(val2Result.value->value);
                result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(INT), op_int(node.op, val1Int, val2Int));
            } else if (val1Type->type == FLOAT || val2Type->type == FLOAT) {
                auto val1Float = std::get<float>(val1Result.value->value);
                auto val2Float = std::get<float>(val2Result.value->value);
                result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(FLOAT), op_float(node.op, val1Float, val2Float));
            }   else {
                throw std::runtime_error("Invalid type in expression.");
                return;
            }      
        } 
    } else {
    // Determine the result type
        if (node.op == NE || node.op == GE || node.op == LE || node.op == GT || node.op == LT || val1Type->type == INT && val2Type->type == INT) {
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(INT));
        } else if (val1Type->type == FLOAT || val2Type->type == FLOAT) {
            result[std::make_shared<ExprNode>(node)].value = TypeValue(std::make_shared<SimpleType>(FLOAT));
        } else {
            throw std::runtime_error("Invalid type in expression.");
            return;
        }
    }
    
    *output.log << "Finished visiting ExprNode" << std::endl;
}

void Checker::visit(IfElseNode &node) {
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
        node.ifstmt->accept(*this);
        if (node.elsestmt) {
            node.elsestmt->accept(*this);
        }
    }
    *output.log << "Finished visiting IfElseNode" << std::endl;
}

void Checker::visit(WhileNode &node) {
    *output.log << "Visiting WhileNode" << std::endl;
    node.cond->accept(*this);

    auto loopLabel = std::make_shared<WhileNode>(node); // Create a new Node for the loop label
    loopStack.push(loopLabel);

    node.stmt->accept(*this);

    loopStack.pop();
    *output.log << "Finished visiting WhileNode" << std::endl;
}

void Checker::visit(BreakNode &node) {
    *output.log << "Visiting BreakNode" << std::endl;
    if (loopStack.empty()) {
        REPORT_ERROR("Break statement outside of a loop.");
        return;
    }

    result[std::make_shared<BreakNode>(node)] = checkerResult();
    result[std::make_shared<BreakNode>(node)].jumpTarget = loopStack.top(); // Use shared_ptr<Node>
    *output.log << "Finished visiting BreakNode" << std::endl;
}

void Checker::visit(ContinueNode &node) {
    *output.log << "Visiting ContinueNode" << std::endl;
    if (loopStack.empty()) {
        REPORT_ERROR("Continue statement outside of a loop.");
        return;
    }

    result[std::make_shared<ContinueNode>(node)] = checkerResult();
    result[std::make_shared<ContinueNode>(node)].jumpTarget = loopStack.top(); // Use shared_ptr<Node>
    *output.log << "Finished visiting ContinueNode" << std::endl;
}

void Checker::visit(ReturnNode &node) {
    *output.log << "Visiting ReturnNode" << std::endl;
    if (!currentFunction) {
        REPORT_ERROR("Return statement outside of a function.");
        return;
    }

    if (node.expr) {
        node.expr->accept(*this);
        auto exprResult = result[node.expr];// Access function ID from Node
    }

    result[std::make_shared<ReturnNode>(node)] = checkerResult();
    result[std::make_shared<ReturnNode>(node)].jumpTarget = currentFunction; // Use shared_ptr<Node>
    *output.log << "Finished visiting ReturnNode" << std::endl;
}

void Checker::visit(FuncDefNode &node) {
    *output.log << "Visiting FuncDefNode" << std::endl;
    *output.log << "Function definition: " << node.id << std::endl;
    currentFunction = std::make_shared<FuncDefNode>(node); // Assign current function as a Node
    auto funcDecl = std::make_shared<FuncDecl>(node.type, node.id);
    scope.addFunc(node.id, funcDecl);
    scope.enterBlock();

    if (node.param) {
        node.param->accept(*this);
        funcDecl->paramList = std::make_shared<std::vector<std::shared_ptr<VarDecl>>>();
        for (auto &param : std::dynamic_pointer_cast<ParamListNode> (node.param) ->paramlist) {
            auto paramResult = result[param];
            if (std::holds_alternative<std::shared_ptr<VarDecl>>(paramResult.decl)) {
                funcDecl->paramList->push_back(std::get<std::shared_ptr<VarDecl>>(paramResult.decl));
            }
        }
    }
    if (node.stmt) {
        node.stmt->accept(*this);
        funcDecl->stmt = node.stmt;
    }

    scope.exitBlock();
    currentFunction.reset(); // Clear current function
    *output.log << "Finished visiting FuncDefNode" << std::endl;
}

void Checker::visit(FuncCallNode &node) {
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
    for (size_t i = 0; i < func->paramList->size(); ++i) {
        auto paramDecl = func->paramList->at(i);
        auto argResult = params->paramlist[i];
        auto argType = result[argResult].value;
        if (!argType) {
            REPORT_ERROR("Function " + node.id + " argument type mismatch.");
            return;
        }
        if (paramDecl->typeValue.type->matchType(*argType->type)) {
            REPORT_ERROR("Function " + node.id + " parameter type mismatch.");
            return;
        }
    }
    result[std::make_shared<FuncCallNode>(node)] = checkerResult();
    result[std::make_shared<FuncCallNode>(node)].value = TypeValue(std::make_shared<SimpleType> (func->returnType));
    *output.log << "Finished visiting FuncCallNode" << std::endl;
}

void Checker::visit(ParamNode &node) {   
    *output.log << "Visiting ParamNode" << std::endl;
    auto type = std::make_shared<SimpleType>(node.type);
    constructingType = type;
    if (node.arraySize) {
        node.arraySize->accept(*this);
    }
    auto varDecl = std::make_shared<VarDecl>(node.id, TypeValue(type));

    scope.addVar(node.id, varDecl);
    result[std::make_shared<ParamNode>(node)] = checkerResult(varDecl);
    *output.log << "Finished visiting ParamNode" << std::endl;
}

void Checker::visit(ParamListNode &node) {
    *output.log << "Visiting ParamListNode" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
    *output.log << "Finished visiting ParamListNode" << std::endl;
}

void Checker::visit(FuncCallParamNode &node) {
    *output.log << "Visiting FuncCallParamNode" << std::endl;
    for (auto &param : node.paramlist) {
        param->accept(*this);
    }
    *output.log << "Finished visiting FuncCallParamNode" << std::endl;
}

void Checker::visit(CompUnitNode &node) {
    *output.log << "Visiting CompUnitNode" << std::endl;
    *output.log<<"checking"<<std::endl;
    for (auto &def : node.deflist) {
        *output.log<<"comp1"<<std::endl;
        def->accept(*this);
        *output.log<<"comp2"<<std::endl;
    }
    *output.log << "Finished visiting CompUnitNode" << std::endl;
}

void Checker::visit(StmtListNode &node) {
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

void Checker::visit(AssignNode &node) {
    *output.log << "Visiting AssignNode" << std::endl;
    node.left->accept(*this);
    node.expr->accept(*this);
    // ...existing code for assignment validation...
    *output.log << "Finished visiting AssignNode" << std::endl;
}

void Checker::visit(VectorNode &node) {
    *output.log << "Visiting vectorNode" << std::endl;
    if (constructingType){
        for (auto element = node.list.rbegin(); element != node.list.rend(); ++element) {
            (*element)->accept(*this);
            if (!result[*element].value) {
                REPORT_ERROR("Invalid value in vector initialization.");
                return;
            }
            auto elementResult = result[*element];
            int length = elementResult.value->getInt();
            constructingType = std::make_shared<ArrayType>(constructingType, length);
        }
        constructingType = nullptr;
    }
    if (constructingValue){
        bool init = false;
        int initIndex = 0;
        if (!constructingValue->isConst()){
            init = true;
             
            
            constructingValue->value = new char[constructingValue->type->size]();
            // constructingValue->value = std::make_shared<void>(std::get<void*> (constructingValue->value));
            memset(std::get<void*> (constructingValue->value), 0, constructingValue->type->size);
            constructingIndex = 0;
        } else {
            if (constructingIndex % constructingValue->type->size != 0) {
                constructingIndex += constructingValue->type->size - constructingIndex % constructingValue->type->size;
            } 
            initIndex = constructingIndex;
        }
        auto simpleType = std::dynamic_pointer_cast<ArrayType>(constructingValue->type)->getSimpleType();
        
        for (auto &element : node.list) {
            auto tmpType = constructingValue->type;
            constructingValue->type = std::dynamic_pointer_cast<ArrayType>(constructingValue->type)->InnerType;
            element->accept(*this);
            constructingValue->type = tmpType;
            if (result.count(element)) {
                if (!result[element].value) {
                    REPORT_ERROR("Invalid value in vector initialization.");
                    return;
                }
                if(result[element].value->isConst()){
                    if(simpleType == INT){
                        auto val = result[element].value->getInt();
                        memcpy(std::get<void*> (constructingValue->value) + constructingIndex, &val, sizeof(int));
                        constructingIndex += sizeof(int);
                    } else if(simpleType == FLOAT){
                        auto val = result[element].value->getFloat();
                        memcpy(std::get<void*> (constructingValue->value) + constructingIndex, &val, sizeof(float));
                        constructingIndex += sizeof(float);
                    }   
                } else {
                    REPORT_ERROR("Invalid value in vector initialization.");
                }            
            }
        }
        if (init) {
            if (constructingIndex >= constructingValue->type->size) {
                REPORT_ERROR("Vector initialization size mismatch.");
                return;
            }
            constructingIndex = 0;
            constructingValue = nullptr;            
            
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

void Checker::visit(DeclNode &node) {
    *output.log << "Visiting DeclNode" << std::endl;
    
    auto type = std::make_shared<SimpleType>(node.type);
    

    if (node.isConst) {
        constructingType = type;
    }
    if (node.arraySize) {
        node.arraySize->accept(*this);
    }
    auto value = std::make_shared<TypeValue>(type);
    
    if (node.isConst) {
        constructingValue = value;
    }   
        
    if (node.initval) {
        node.initval->accept(*this);
    }
    
    auto decl = std::make_shared<VarDecl>(node.id, *value);

    scope.addVar(node.id, decl);
    
    result[std::make_shared<DeclNode>(node)] = checkerResult(decl);
    
    *output.log << "Finished visiting DeclNode" << std::endl;
}

void Checker::visit(ConstIntNode &node) {
    *output.log << "Visiting ConstIntNode" << std::endl;
    result[std::make_shared<ConstIntNode>(node)] = checkerResult({}, TypeValue(std::make_shared<SimpleType>(INT), node.val));
    *output.log << "Finished visiting ConstIntNode" << std::endl;
}

void Checker::visit(ConstFloatNode &node) {
    *output.log << "Visiting ConstFloatNode" << std::endl;
    result[std::make_shared<ConstFloatNode>(node)] = checkerResult({}, TypeValue(std::make_shared<SimpleType>(FLOAT), node.val));
    *output.log << "Finished visiting ConstFloatNode" << std::endl;
}

void Checker::visit(IdentifierNode &node) {
    *output.log << "Visiting IdentifierNode" << std::endl;
    auto var = scope.findVar(node.id);
    if (!var) {
        REPORT_ERROR("Variable " + node.id + " not declared.");
        return;
    }
    result[std::make_shared<IdentifierNode>(node)] = 
        checkerResult({} ,var->typeValue);
    *output.log << "Finished visiting IdentifierNode" << std::endl;
}

void Checker::visit(SimpleTokenNode &node) {
    *output.log << "Visiting SimpleTokenNode" << std::endl;
    // ...existing code for handling simple tokens...
    *output.log << "Finished visiting SimpleTokenNode" << std::endl;
}

void Checker::visit(BlockGroupNode &node) {
    *output.log << "Visiting BlockGroupNode" << std::endl;
    scope.enterBlock();
    for (auto &block : node.blocklist) {
        block->accept(*this);
    }
    scope.exitBlock();
    *output.log << "Finished visiting BlockGroupNode" << std::endl;
}

void Checker::visit(LvalNode &node) {
    *output.log << "Visiting LvalNode" << std::endl;
    auto var = scope.findVar(node.id);
    if (!var) {
        REPORT_ERROR("Variable " + node.id + " not declared.");
        return;
    }
    bool allConst = var->typeValue.isConst();
    if (node.arrayIndex) {
        for(auto &index : std::dynamic_pointer_cast<VectorNode> (node.arrayIndex)->list) {
            index->accept(*this);
            auto indexResult = result[index];
            if (!indexResult.value) {
                REPORT_ERROR("Invalid array index.");
                return;
            }
            if (std::dynamic_pointer_cast<SimpleType>(indexResult.value->type)->type != INT) {
                REPORT_ERROR("Array index must be an integer.");
                return;
            }
            auto typeValue = var->typeValue;
            if(indexResult.value->isConst()){
                auto indexValue = indexResult.value->getInt();
                if (indexValue < 0 || indexValue >= typeValue.get_index(indexValue
                ).get_index(0).getInt()) {
                    REPORT_ERROR("Array index out of bounds.");
                    return;
                } else {
                    typeValue = typeValue.get_index(indexValue);
                }
            } else {
                typeValue = typeValue.get_index(0);
                allConst = false;
            }
            if(allConst) {
                result[std::make_shared<LvalNode>(node)] = checkerResult({}, typeValue);
            } else {
                result[std::make_shared<LvalNode>(node)] = checkerResult({}, TypeValue(typeValue.type));
            }
        }
    }
    
    *output.log << "Finished visiting LvalNode" << std::endl;
}
