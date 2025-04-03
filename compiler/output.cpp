#include "output.h"
#include <iostream>
#include <fstream>
#include <memory>

Output::Output() {


    // Redirecting to standard output and error
    log = std::make_shared<std::ostream> (std::cout.rdbuf());
    err = std::make_shared<std::ostream> (std::cerr.rdbuf()); 
    output = std::make_shared<std::ostream> (std::cout.rdbuf());


}

Output output;