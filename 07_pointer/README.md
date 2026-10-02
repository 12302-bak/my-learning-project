
* ## 数据类型


* ## 位宽限制 intN_t

    查看 GCC 内置的隐藏宏定义：`gcc -dM -E - < /dev/null | grep -E "INT.*_TYPE"`
    <br>标准预定义宏（Standard Predefined Macros）：`__LINE__、__FILE__、__func__、__TIME__、 __DATE__`等。
    <br>由外部“动态注入”的宏：`gcc -Dmacro[=defn]`

    所以流程可能为：
    <br>为在处理 stdint.h 头文件预处理时，将预定义宏 `__INT32_TYPE__` 替换为目标平台 ABI 中对应的[size:type], 比如 16bit [32:long], 32bit [32:int]
    <br>然后代码中的`int32_t` 根据别名` typedef [long/int] int32_t` 找到正确的类型。

    当然也有可能为：在编译器内部直接写死，比如`typedef __int32_t int32_t;`、`typedef signed int __int32_t;`

    ```c
    /* stdint.h 的简化实现逻辑 */

    /* 1. 编译器/ABI 已经确定了基础类型的实际宽度 */
    /* 在 16 位平台上：char=8位, short=16位, int=16位, long=32位 */
    /* 在 32/64 位平台上：char=8位, short=16位, int=32位, long=32/64位 */

    /* 2. stdint.h 通过条件编译，选择恰好匹配的基础类型 */
    typedef signed char        int8_t;    // 所有平台 char 都是 8 位，直接映射
    typedef short int          int16_t;   // 所有平台 short 都是 16 位，直接映射

    /* int32_t 的映射：根据平台动态选择 */
    #if defined(__INT32_TYPE__)
        typedef __INT32_TYPE__ int32_t;   // GCC/Clang 内置宏，直接指向恰好 32 位的类型
    #else
        /* 传统实现方式：手动判断 */
        #if INT_MAX == 2147483647
            typedef int        int32_t;   // 如果 int 恰好是 32 位（32/64 位平台）
        #elif LONG_MAX == 2147483647
            typedef long       int32_t;   // 如果 long 恰好是 32 位（16 位平台）
        #else
            #error "No 32-bit integer type available"
        #endif
    #endif
    ```