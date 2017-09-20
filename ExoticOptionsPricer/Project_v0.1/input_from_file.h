#include <stdio.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include "input_valid_from_file.h"
#include "NewProcessMC.h"
#include "result_from_file.h"
#include "Process.h"


#ifndef input_from_file_hpp
#define input_from_file_hpp


bool read_one_asset(const Process& Process,string file);
bool read_Portfolio(const Process& Process,string file);


#endif
