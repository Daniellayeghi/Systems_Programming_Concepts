#ifndef UNTITLED2_SYS_PROG_H
#define UNTITLED2_SYS_PROG_H

#include <utility>
#include <cstdint>

namespace SystemProgrammingPractice::SystemTypes
{
    struct MyStruct {
        std::uint16_t value_1 = 0; //2 bytes
        std::uint64_t value_2 = 0; //8 bytes
    };

    //Namespace members
    static MyStruct my_struct = {0, 0};
    static auto msg = "This is a nested namespace with internal linkage!";

    //Namespace functions
    std::pair<const char *, int> return_namespace_state();
    void increment_variable();
}
#endif //UNTITLED2_SYS_PROG_H
