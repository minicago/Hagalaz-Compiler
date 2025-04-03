#ifndef TOOL_H
#define TOOL_H
#include "def.h"

bool matchArraysize(IntList& arraySize, ConstChunk& initval) ;

Const getConst(IntList& arrayIndex, ConstChunk& initval, int index = 0) ;

std::shared_ptr<IntList> makeIntList(ConstChunk& initval);

#endif