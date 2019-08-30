
#include <gtest/gtest.h>
#include <array>
#include "../include/sys_prog.h"

class SystemsDataTypes : public testing::Test {

public:
    void SetUp() {

    }

    void TearDown() {

    }
};


TEST_F(SystemsDataTypes, Struct_Byte_Granularity)
{
    /**
  * @desc The pack command gives a minimum granularity of 1 byte to the compiler.
  * This is in order to stop the compiler to optimize the uint16_t to uint64_t,
  * consecutively increasing the struct size to 16 (instead of 10).
*/

    #pragma pack(push, 1)
    struct MyStruct {
        std::uint16_t value_1 = 0; //2 bytes
        std::uint64_t value_2 = 0; //8 bytes
    };
    #pragma pack(pop)

    ASSERT_EQ(sizeof(MyStruct), 10);
}

TEST_F(SystemsDataTypes, Internal_Linkage_in_Namespace)
{
    /**
  * @desc This test verifies the effects of internal linkage. The static struct
  * in the sys_prog.h is unique to the translation unit. Therefor the instance
  * used in sys_prog.cpp is different to the one here. the increments below show this.
*/

    using namespace SystemProgrammingPractice::SystemTypes;

    // instance for this translation unit
    my_struct.value_1 += 0;

    // increments the instance for the sys_prog.cpp translation unit.
    increment_variable();
    auto return_pair = return_namespace_state();

    ASSERT_TRUE((my_struct.value_1 - return_pair.second) == 2);
}
