
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


TEST_F(SystemsDataTypes, Struct_Byte_Alignment_Using_Padding)
{
    /**
    * @desc By manually reordering the members of MyStruct we decrease alignment requirement
    * and halve the size of the struct. The compiler adds padding to meet alignment as such:
    * struct MyStruct {
    *     char byte_1;
    *     char pad[7]
    *     int *byte_8;
    *     short byte_2;
    *     char pad[6]
    *};
    */

    struct MyStruct {
        char byte_1;
        int *byte_8;
        short byte_2;
    };

    ASSERT_EQ(24, sizeof(MyStruct));

    struct MyStructReorder{
        int *byte_8;
        char byte_1;
        short byte_2;
    };

    ASSERT_EQ(16, sizeof(MyStructReorder));
}


TEST_F(SystemsDataTypes, Struct_Cache_Alignment) {
    /**
    * @desc The pack command gives a minimum granularity of 1 byte to the compiler
     * creating a byte aligned struct. However this does not guarantee that the structure
     * is also cache aligned. Using alignas we can enforce this.
    */

    #pragma pack(push, 1)
    struct MyStruct {
        std::uint16_t value_1 = 0; //2 bytes
        std::uint64_t value_2 = 0; //8 bytes
    };
    #pragma pack(pop)


    #pragma pack(push, 1)
    struct alignas(16) MyStructCacheAligned {
        std::uint16_t value_1 = 0; //2 bytes
        std::uint64_t value_2 = 0; //8 bytes
    };
    #pragma pack(pop)


    MyStruct instance;
    MyStructCacheAligned cache_aligned_instance;

    auto instance_address = reinterpret_cast<uintptr_t> (&instance);
    auto nibble = instance_address % 16;

    auto cache_aligned_instance_address = reinterpret_cast<uintptr_t> (&cache_aligned_instance);
    auto cache_aligned_nibble = cache_aligned_instance_address % 16;

    ASSERT_TRUE(nibble != 0);
    ASSERT_TRUE(cache_aligned_nibble == 0);
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
    my_struct.value_1 += 3;

    // increments the instance for the sys_prog.cpp translation unit.
    increment_variable();
    auto return_pair = return_namespace_state();

    ASSERT_TRUE((my_struct.value_1 - return_pair.second) == 2);
}

