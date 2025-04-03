#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <iostream>
#include <memory>

class Output{
public:
    std::shared_ptr<std::ostream> log, err, output;
    Output() ;
};

extern Output output;
#endif
