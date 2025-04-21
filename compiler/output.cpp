#include "output.h"
#include <iostream>
#include <fstream>
#include <memory>

Output::Output() {


    // Redirecting to standard output and error
    log = std::make_shared<std::ofstream>();
    err = std::make_shared<std::ofstream>();
    output = std::make_shared<std::ofstream>();
    log->open("compiler.log");
    err->open("compiler.err");


}

void Output::setOutput(std::string filename) {
    output->open(filename);
   
}

Output output;