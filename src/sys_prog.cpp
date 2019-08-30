#include "../include/sys_prog.h"

std::pair<const char *, int> SystemProgrammingPractice::SystemTypes::return_namespace_state()
{
    return {msg, my_struct.value_1};
}

void SystemProgrammingPractice::SystemTypes::increment_variable()
{
    ++my_struct.value_1;
}
