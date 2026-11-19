

* ## 运算符优先级

    参考:[operator_precedence](https://cppreference.com/c/language/operator_precedence)

    | Precedence | Operator | Description | Associativity |
    | :---: | :--- | :--- | :--- |
    | **1** | `++` `--` <br> `( )` <br> `[ ]` <br> `.` <br> `->` <br> `(type){list}` | Suffix/postfix increment and decrement <br> Function call <br> Array subscripting <br> Structure and union member access <br> Structure and union member access through pointer <br> Compound literal (C99) | Left-to-right |
    | **2** | `++` `--` <br> `+` `-` <br> `!` `~` <br> `(type)` <br> `*` <br> `&` <br> `sizeof` <br> `_Alignof` | Prefix increment and decrement<sup>[1]</sup> <br> Unary plus and minus <br> Logical NOT and bitwise NOT <br> Cast <br> Indirection (dereference) <br> Address-of <br> Size-of<sup>[2]</sup> <br> Alignment requirement (C11) | Right-to-left |
    | **3** | `*` `/` `%` | Multiplication, division, and remainder | Left-to-right |
    | **4** | `+` `-` | Addition and subtraction | Left-to-right |
    | **5** | `<<` `>>` | Bitwise left shift and right shift | Left-to-right |
    | **6** | `<` `<=` <br> `>` `>=` | For relational operators < and ≤ respectively <br> For relational operators > and ≥ respectively | Left-to-right |
    | **7** | `==` `!=` | For relational = and ≠ respectively | Left-to-right |
    | **8** | `&` | Bitwise AND | Left-to-right |
    | **9** | `^` | Bitwise XOR (exclusive or) | Left-to-right |
    | **10** | `\|` | Bitwise OR (inclusive or) | Left-to-right |
    | **11** | `&&` | Logical AND | Left-to-right |
    | **12** | `\|\|` | Logical OR | Left-to-right |
    | **13** | `?:` | Ternary conditional<sup>[3]</sup> | Right-to-left |
    | **14**<sup>[4]</sup> | `=` <br> `+=` `-=` <br> `*=` `/=` `%=` <br> `<<=` `>>=` <br> `&=` `^=` `\|=` | Simple assignment <br> Assignment by sum and difference <br> Assignment by product, quotient, and remainder <br> Assignment by bitwise left shift and right shift <br> Assignment by bitwise AND, XOR, and OR | Right-to-left |
    | **15** | `,` | Comma | Left-to-right |

* ## 数据类型

    格式化符号 [格式符](#格式符)

    | 类型                   | 简写               | 大小       | 有效数字/范围               | 格式化符号 | 说明                                                    |
    | :--------------------- | :----------------- | :--------- | :-------------------------- | :--------- | :------------------------------------------------------ |
    | _Bool                  |                    | 1          | 0 或 1                      | %d         | C99 引入的布尔类型，是语言关键字                        |
    | char                   |                    | 1          | (-128 ~ 127)/(0 ~ 255)      | %c         | 本质是整数，存储 ASCII 码值，符号性由编译器实现决定     |
    | signed char            |                    | 1          | -128 ~ 127                  | %hhd       | 明确有符号                                              |
    | unsigned char          |                    | 1          | 0 ~ 255                     | %hhu       | 明确无符号                                              |
    | short int              | short              | 2          | -32768 ~ 32767              | %hd        |                                                      |
    | unsigned short int     | unsigned short     | 2          | 0 ~ 65535                   | %hu        | 无符号短整型                                            |
    | int                    |                    | 4          | -2147483648 ~ 2147483647    | %d         | 机器最自然的整数长度                                    |
    | unsigned int           |                    | 4          | 0 ~ 4294967295              | %u         | 无符号整型                                              |
    | long int               | long               | 4或8       | 取决于ABI                    | %ld        | Linux 64 位下为 8 字节，Windows 64 位下为 4 字节        |
    | unsigned long int      | unsigned long      | 4或8       | 取决于ABI                    | %lu        | 无符号长整型                                            |
    | long long int          | long long          | 8          | -9.2×10¹⁸ ~ 9.2×10¹⁸        | %lld       | C99 引入                                                |
    | unsigned long long int | unsigned long long | 8          | 0 ~ 1.8×10¹⁹                | %llu       | 无符号长长整型                                          |
    | float                  |                    | 4          | 6~7位有效数字，±3.4×10³⁸      | %f         | IEEE 754 单精度                                         |
    | double                 |                    | 8          | 15~16位有效数字，±1.7×10³⁰⁸   | %lf、%f    | C99 引入(%lf)，在 printf 与 %f 等价，scanf 需要使用 %lf |
    | long double            |                    | 8/10/12/16 | 高于 double                  | %Lf        | 平台相关，x86 上 GCC 通常为 80 位扩展精度               |

* ## 常用的字面量后缀

    | 字面量后缀  | 说明                                               |
    | ---------- | ------------------------------------------------- |
    | `f`、`F`   | float 类型                                         |
    | `l`、`L`   | 对于整数是 long int 类型，对于小数是 long double 类型     |
    | `ll`、`LL` | Long Long 类型，比如 3LL                            |
    | `u`、`U`   | 表示 unsigned int，比如 15U、0377U                   |

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

* ## 格式符

    | [格式符](https://cppreference.com/c/io/fprintf) | 说明                                                                                  |
    | ------ | ------------------------------------------------------------------------------------- |
    | `%c`   | 字符。                                                                                |
    | `%hhd` | h(short),hh(short short) 即 char，有符号十进制整数                                      |
    | `%hhu` | 当 char 或 short 作为可变参数传递给 printf 时，编译器会自动将它们提升为 int（4 字节）。hh 告诉 printf：“虽然参数在栈上是 4 字节的 int，但请只取最低 1 字节，按 char 的语义来解释它。” |
    | ------ |  |
    | `%d`   | 十进制整数。                                                                          |
    | `%o`   | 八进制整数。                                                                          |
    | `%x`   | 十六进制整数。                                                                        |
    | `%u`   | 无符号十进制整数（unsigned int）。                                                          |
    | `%i`   | 整数，基本等同于 `%d`。                                                                  |
    | ------ |  |
    | `%hd`  | 十进制 short int 类型。                                                               |
    | `%ho`  | 八进制 short int 类型。                                                               |
    | `%hx`  | 十六进制 short int 类型。                                                             |
    | `%hu`  | unsigned short int 类型。                                                             |
    | ------ |  |
    | `%ld`  | 十进制 long int 类型。                                                                |
    | `%lo`  | 八进制 long int 类型。                                                                |
    | `%lx`  | 十六进制 long int 类型。                                                              |
    | `%lu`  | unsigned long int 类型。                                                              |
    | ------ |  |
    | `%lld` | 十进制 long long int 类型。                                                           |
    | `%llo` | 八进制 long long int 类型。                                                           |
    | `%llx` | 十六进制 long long int 类型。                                                         |
    | `%llu` | unsigned long long int 类型。                                                         |
    | ------ |  |
    | `%f`   | 小数（包含 `float` 类型和 `double` 类型）。                                                   |
    | `%lf`  | c99 引入，行为与 %f 完全等价，语义上更明确地表示 double                                   |
    | `%e`   | 使用科学计数法的浮点数，指数部分的 `e` 为小写。                                           |
    | `%E`   | 使用科学计数法的浮点数，指数部分的 `E` 为大写。                                           |
    | `%g`   | 6个有效数字的浮点数。整数部分一旦超过6位，就会自动转为科学计数法，指数部分的 `e` 为小写。 |
    | `%G`   | 等同于 `%g`，唯一的区别是指数部分的 `E` 为大写。                                             |
    | `%a`   | 十六进制浮点数，字母输出为小写。                                                      |
    | `%A`   | 十六进制浮点数，字母输出为大写。                                                      |
    | `%Lf`  | long double 类型浮点数。                                                              |
    | `%Le`  | 科学计数法表示的 long double 类型浮点数。                                             |
    | ------ |  |
    | `%n`   | 已输出的字符串数量。该占位符本身不输出，只将值存储在指定变量之中。                    |
    | `%p`   | 指针。                                                                                |
    | `%s`   | 字符串。                                                                              |
    | `%zd`  | `size_t` 类型。                                                                          |
    | `%zu`  | `size_t` 类型，无符号。                                                                |
    | `%td`  | 以有符号十进制整数的形式输出 `ptrdiff_t` 类型的值。                                          |
    | `%#o`、`%#x`、`%#X`  | 显示前缀                                                                |
    | `%%`   | 输出一个百分号。                                                                      | 

* ## 输出格式

    | 格式    | 说明                                                                                  |
    | ------ | ------------------------------------------------------------------------------------- |
    | `（1）限定宽度`       | printf("%5d%s\n", 123, "\|"); // 输出为 "  123\|" <br> printf("%-5d%s\n", 123,"\|"); // 输出为 "123  \|" <br> printf("%12f\n", 123.45); |
    | `（2）总是显示正负号`  | printf("%+d\n", 123); // 输出为 "+123" <br> printf("%+d\n", -123); // 输出为 "-123" |
    | `（3）限定小数位数`    | printf("Number is %.2f\n", 0.5); // 输出为 "0.50" <br> printf("%6.2f\n", 0.5); // 输出为 "  0.50" <br> printf("%*.*f\n", 6, 2, 0.5); |
    | `（4）输出部分字符串`  | printf("%.5s\n", "hello world"); // 输出 "hello" |