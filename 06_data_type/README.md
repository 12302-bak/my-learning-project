
* ## 数据类型

    格式化符号 [参考:02_README.md](./../02_basic_syntax/README.md#格式符)

    | 类型 | 简写 | 大小 | 有效数字/范围 | 格式化符号 | 说明 |
    |:---|:---|:---|:---|:---|:---|
    | _Bool | | 1 | 0 或 1 | %d | C99 引入的布尔类型，是语言关键字 |
    | char | | 1 | (-128 ~ 127)/(0 ~ 255) | %c | 本质是整数，存储 ASCII 码值，符号性由编译器实现决定 |
    | signed char | | 1 | -128 ~ 127 | %hhd | 明确有符号 |
    | unsigned char | | 1 | 0 ~ 255 | %hhu | 明确无符号 |
    | short int | short | 2 | -32768 ~ 32767 | %hd | 短整型 |
    | unsigned short int | unsigned short | 2 | 0 ~ 65535 | %hu | 无符号短整型 |
    | int | | 4 | -2147483648 ~ 2147483647 | %d | 机器最自然的整数长度 |
    | unsigned int | | 4 | 0 ~ 4294967295 | %u | 无符号整型 |
    | long int | long | 4或8 | 取决于ABI | %ld | Linux 64位下为8字节，Windows 64位下为4字节 |
    | unsigned long int | unsigned long | 4或8 | 取决于ABI | %lu | 无符号长整型 |
    | long long int | long long | 8 | -9.2×10¹⁸ ~ 9.2×10¹⁸ | %lld | C99 引入 |
    | unsigned long long int | unsigned long long | 8 | 0 ~ 1.8×10¹⁹ | %llu | 无符号长长整型 |
    | float | | 4 | 6~7位有效数字，±3.4×10³⁸ | %f | IEEE 754 单精度 |
    | double | | 8 | 15~16位有效数字，±1.7×10³⁰⁸ | %lf、%f | C99 引入(%lf)，在 printf 与 %f 等价，scanf 需要使用 %lf |
    | long double | | 8/10/12/16 | 高于 double | %Lf | 平台相关，x86 上 GCC 通常为 80 位扩展精度 |

* ## 控制字符

    | 控制字符 | 说明                                                                                  |
    | ------ | ------------------------------------------------------------------------------------- |
    | `\a`   | 警报，这会使得终端发出警报声或出现闪烁，或者两者同时发生。|
    | `\b`   | 退格键，光标回退一个字符，但不删除字符。|
    | `\f`   | 换页符，光标移到下一页。在现代系统上，这已经反映不出来了，行为改成类似于 `\v` |
    | `\n`   | 换行符。                                                                          |
    | `\r`   | 回车符，光标移到同一行的开头。|
    | `\t`   | 制表符，光标移到下一个水平制表位，通常是下一个 8 的倍数。|
    | `\v`   | 垂直分隔符，光标移到下一个垂直制表位，通常是下一行的同一列。|
    | `\0`   | NUL 字符，代表没有内容，当作字符串的“终点线”。注意，它的值等于 0，和 '0'(ascii:48) 不一样。|
    |        | <br>                                                                          |
    |        | **转义写法还能使用 8 和 16 进制表示一个字符** |
    | `\nn`  | 字符的 8进制写法，`nn`为八进制值。|
    | `\xnn` | 字符的16进制写法，`nn`为十六进制值。|


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

* ## ABI(Application Binary Interface)
    * https://github.com/lenary/abis