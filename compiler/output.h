#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>
#include <iostream>
#include <memory>

class Output{
public:
    std::shared_ptr<std::ofstream> log, err, output;
    Output() ;
    void setOutput(std::string filename);
};

extern Output output;
#endif
