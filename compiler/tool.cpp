#include "tool.h"
#include "def.h"

int getSize(IntList& arraySize){
    int size = 1;
    for(auto i: arraySize){
        size *= i;
    }
    return size;
}

bool internalMatchArraysize(IntList& arraySize, ConstChunk& initval, int currentSize, int index) {
    if (index >= arraySize.size()) {
        if(!std::holds_alternative<Const>(initval.value)){
            return false;
        }
        else return true;
    }

    if (std::holds_alternative<Const>(initval.value)) {
        ConstChunk tmp_layer;
        std::get<std::vector<ConstChunk> >(tmp_layer.value).push_back(initval);
    }
    
    ConstChunk current_layer, next_layer;
    bool empty_next_layer = true;

    if (currentSize < std::get<std::vector<ConstChunk> >(initval.value).size()) return false;

    for (auto constChunk: std::get<std::vector<ConstChunk> >(initval.value)){
        if ( index == arraySize.size() - 1 ) {
            next_layer = constChunk;
            if (!internalMatchArraysize(arraySize, next_layer, currentSize / arraySize[index], index + 1)){
                return false;
            }
            std::get<std::vector<ConstChunk> >(current_layer.value).push_back(next_layer); 
        }  else {
            if(std::get<std::vector<ConstChunk> >(next_layer.value).size() == currentSize / arraySize[index]
                || std::holds_alternative<std::vector<ConstChunk> >(constChunk.value)){
                    if (!empty_next_layer && !internalMatchArraysize(arraySize, next_layer, currentSize / arraySize[index], index + 1)){
                        return false;
                    }
                    if(!empty_next_layer) std::get<std::vector<ConstChunk> >(current_layer.value).push_back(next_layer);
                    next_layer = ConstChunk();
                    empty_next_layer = true;
                }   
            
            if (std::holds_alternative<Const>(constChunk.value)) {
                std::get<std::vector<ConstChunk> >(next_layer.value).push_back(constChunk);
            } else {
                next_layer = constChunk;
            }
            empty_next_layer = false;         
        }


    }

    if(!empty_next_layer) std::get<std::vector<ConstChunk> >(current_layer.value).push_back(next_layer);
    initval = current_layer;


    return true;


}

bool matchArraysize(IntList& arraySize, ConstChunk& initval) {
    internalMatchArraysize(arraySize, initval, getSize(arraySize), 0);

}

Const getConst(IntList& arrayIndex, ConstChunk& initval, int index = 0) {
    if (index >= arrayIndex.size()) {
        return std::get<Const>(initval.value);
    }
    if (arrayIndex[index] < std::get<std::vector<ConstChunk> >(initval.value).size()){
        return getConst(arrayIndex, std::get<std::vector<ConstChunk> >(initval.value)[arrayIndex[index]], index + 1);
    } else {
        return Const(0);
    }
}

std::shared_ptr<IntList> makeIntList(ConstChunk& initval){
    if (not std::holds_alternative<std::vector<ConstChunk> >(initval.value))
        return nullptr;
    
    IntList v;

    for(auto integer : std::get<std::vector<ConstChunk> >(initval.value)){
        if (not std::holds_alternative<Const>(integer.value)){
            return nullptr;
        } 
        if (not std::holds_alternative<int>(std::get<Const> (integer.value))){
            return nullptr;
        }
        v.push_back(std::get<int>(std::get<Const> (integer.value)));
    }
    return std::make_shared<IntList>(v);
}
