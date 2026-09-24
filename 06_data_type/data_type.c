
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <inttypes.h>
//#include <stdint.h> inttypes.h 头文件包含了 stdint.h

/**
 * @see https://wangdoc.com/clang/types
 *
 * C 语言的每一种数据，都是有类型（type）的，编译器必须知道数据的类型，才能操作数据。
 * 所谓“类型”，就是相似的数据所拥有的共同特征，那么一旦知道某个值的数据类型，就能知道该值的特征和操作方式。
 * 基本数据类型有三种：字符（char）、整数（int）和浮点数（float）。复杂的类型都是基于它们构建的。
 */
int main(){
    
    /**
        1. 字符类型

            字符类型指的是单个字符，类型声明使用 char 关键字。C 语言规定，字符常量必须放在单引号里面。
            在计算机内部，字符类型使用一个字节（8位）存储。C 语言将其当作整数处理。
            字符类型在不同计算机的默认范围是不一样的。一些系统默认为 -128~127，另一些系统默认为 0~255。这两种范围正好都能覆盖 0~127 的 ASCII 字符范围。
            只要在字符类型的范围之内，整数与字符是可以互换的，都可以赋值给字符类型的变量。

            两个字符类型的变量可以进行数学运算。

            单引号本身也是一个字符，如果要表示这个字符常量，必须使用反斜杠转义。

            控制字符，参考 README.md。
     */
        printf("========================Character Type========================\n");
        char c = 66;
        char d = 'B';
        printf("c = %c, d = %c,  e = %d,    single = %c\n", 
                            c,      d,  'B' + 'B',  '\'');
        // 控制字符
        printf("hello world\b!!!\n");
        // 8,16 进制。也就是一个字符有四种表示方式：数字、ASCII 码、8进制、16进制。
        printf("c_8: %c, c_16: %c\n", '\102', '\x42');


    /**
        2. 整数类型

            1、简介: 整数类型用来表示较大的整数，类型声明使用int关键字。
            
                不同计算机的int类型的大小是不一样的。
                比较常见的是使用 4 个字节（32位）存储一个 int 类型的值，但是 2 个字节（16位）或 8 个字节（64位）也有可能使用。
                编译器可以根据计算机的实际情况来决定整数类型的范围。

            2、signed，unsigned:
                C 语言使用 signed 关键字，表示一个类型带有正负号，包含负值；使用 unsigned 关键字，表示该类型不带有正负号，只能表示零和正整数。
                对于int类型，默认是带有正负号的，也就是说 int 等同于 signed int。由于这是默认情况，关键字signed一般都省略不写，但是写了也不算错。

                字符类型 char 也可以设置 signed 和 unsigned。
                注意，C 语言规定 char 类型默认是否带有正负号，由当前系统决定。这一点与 int 不同。
            
            3、整数的子类型:
                如果int类型使用4个或8个字节表示一个整数，对于小整数，这样做很浪费空间。
                另一方面，某些场合需要更大的整数，8个字节还不够。为了解决这些问题，C 语言在 int 类型之外，又提供了三个整数的子类型。默认它们都是带符号的（signed）
                    short int       （简写为short）：       占用空间不多于 int， 一般占用 2 个字节（整数范围为 -32768～32767)。
                    long  int       （简写为long） ：       占用空间不少于 int， 至少为 4 个字节。
                    long long int   （简写为long long）：   占用空间多于   long，至少为 8 个字节。
                这样有利于更精细地限定整数变量的范围，也有利于更好地表达代码的意图。

            4、整数类型的极限值:

            5、整数的进制:
                C 语言的整数默认都是十进制数，如果要表示八进制数和十六进制数，必须使用专门的表示法。
                    八进制使用 0 作为前缀，比如 017、0377。
                    十六进制使用 0x 或 0X 作为前缀，比如 0xf、0X10。
                    有些编译器使用 0b 前缀，表示二进制数，但不是标准。
                不同进制可以混合使用，比如 10 + 015 + 0x20 是一个合法的表达式。
                显示前缀，参考 README.md。

                在stdint.h出现之前，C语言的整数类型设计是带着历史包袱的。
                C语言标准只规定了每种整数类型的最小取值范围，比如int至少能表示-32767到32767，但并没有强制规定它必须是2字节还是4字节。
                这带给编译器实现者很大的自由度，却给应用开发者带来了灾难。

     */
        printf("\n========================Interger Type========================\n");
        signed int i = 100; int j = 200;
        signed char c1;     // 范围为 -128 到 127
        unsigned char c2;   // 范围为 0 到 255

        int32_t a = 100;
        if (a < INT_MAX)
            printf("a = %d, a = %d, o = %o, x = %x\n", a, INT32_MAX, INT_MAX, INT_MAX);
        
        (void)sizeof(int); // 通过强制转换为 void，消除编译器对未使用变量的警告
        size_t size = sizeof(int);
        printf("\n");
        printf("sizeof(short)     = %zu bytes\n", sizeof(short));       // 2
        printf("sizeof(int)       = %zu bytes\n", size);                // 4
        printf("sizeof(long)      = %zu bytes\n", sizeof(long));        // 8
        printf("sizeof(long long) = %zu bytes\n", sizeof(long long));   // 8
        printf("sizeof(void*)     = %zu bytes\n", sizeof(void*));       // 8    void* 是"指向任意类型的指针"
        
        // 位宽限制 intN_t 输出，使用宏定义，避免类型不匹配。
        uint32_t count = 42;
        int64_t offset = -1000000L;
        uint64_t big = UINT64_C(123456789012345);
        printf("\n");
        printf("count   = %" PRIu32 "\n", count);
        printf("offset  = %" PRId64 "\n", offset);
        printf("big     = %" PRIu64 "\n", big);
        //printf("big     = %" PRIu32 "\n", big);     // 类型不匹配 : 2249056121

        // 整数类型的极限值:
        printf("\n");
        printf("signed char:        [%d, %d]\n",           SCHAR_MIN,  SCHAR_MAX);     // [-128, 127]
        printf("short:              [%d, %d]\n",           SHRT_MIN,   SHRT_MAX);      // [-32768, 32767]
        printf("int:                [%d, %d]\n",           INT_MIN,    INT_MAX);       // [-2147483648, 2147483647]
        printf("long:               [%ld, %ld]\n",         LONG_MIN,   LONG_MAX);      // [-9223372036854775808, 9223372036854775807]
        printf("long long:          [%lld, %lld]\n",       LLONG_MIN,  LLONG_MAX);     // [-9223372036854775808, 9223372036854775807]
        printf("unsigned char:      [0, %u]\n",            UCHAR_MAX);                 // [0, 255]
        printf("unsigned short:     [0, %u]\n",            USHRT_MAX);                 // [0, 65535]
        printf("unsigned int:       [0, %u]\n",            UINT_MAX);                  // [0, 4294967295]
        printf("unsigned int64:     [0, %" PRIu64 "]\n",   UINT64_MAX);                // [0, 18446744073709551615]
        printf("unsigned long:      [0, %lu]\n",           ULONG_MAX);                 // [0, 18446744073709551615]
        printf("unsigned long long: [0, %llu]\n",          ULLONG_MAX);                // [0, 18446744073709551615]

        // 整数的进制:
        int x = 100;
        printf("\n");
        printf("dec     = %d\n",  x);   // 100
        printf("octal   = %o\n",  x);   // 144
        printf("hex     = %x\n",  x);   // 64
        printf("octal   = %#o\n", x);   // 0144
        printf("hex     = %#x\n", x);   // 0x64
        printf("hex     = %#X\n", x);   // 0X64

    /**
        3. 浮点数类型:

            浮点数的类型声明使用 float 关键字，可以用来声明浮点数变量。

            任何有小数点的数值，都会被编译器解释为浮点数。所谓“浮点数”就是使用 m * be 的形式，存储一个数值，m 是小数部分，b 是基数（通常是2），e 是指数部分。
            这种形式是精度和数值范围的一种结合，可以表示非常大或者非常小的数。
            参考：https://xhsgg12302.github.io/archive/hugo/corner/numeration/#浮点数

            float类型占用4个字节（32位），其中 8 位存放指数的值和符号，剩下 24 位存放小数的值和符号。
            C标准（ISO 9899）规定：float类型至少能够提供（十进制的）6 位有效数字，指数部分的范围为（十进制的）-37~37，即数值范围为 10-37~1037。
            IEEE 754 单精度的实际能力：6~7 位（保守保证6位）[十进制有效位数 ≈ log₁₀(2²⁴) ≈ 7.22]，实际指数 -126 ~ +127。
            对于下面的例子，f1 和 f2 的值在存储时，小数前 6 位得到保证，后面应该舍弃了，导致它们相等。

            有时候，32位浮点数提供的精度或者数值范围还不够，C 语言又提供了另外两种更大的浮点数类型。
                double：        占用8个字节（64位），至少提供13位有效数字。(double d = 3.14;   // 正确，无后缀默认就是 double)
                    C 语言的默认参数提升规则（default argument promotions）规定，float 在表达式运算和函数传参时会自动提升为 double。所以：
                    float a = 1.0f, b = 2.0f;
                    float c = a + b;  // a、b 先提升为 double 运算，结果再截断回 float
                long double：   通常占用 16 个字节。(long double d = 3.14L;   // L,l 后缀就是 long double)

            由于存在精度限制，浮点数只是一个近似值，它的计算是不精确的，比如 C 语言里面 0.1 + 0.2 != 0.3，而是有一个很小的误差。

            C 语言允许使用科学计数法表示浮点数，使用字母e来分隔小数部分和指数部分。
            e 后面如果是加号 + ，加号可以省略。注意，科学计数法里面 e 的前后，不能存在空格。
            另外，科学计数法的小数部分如果是 0.x 或 x.0 的形式，那么 0 可以省略。
                0.3E6 <==> .3E6
                3.0E6 <==> 3.E6

            浮点数的比较
                用容差比较：
                #include <math.h>
                if (fabs(a - b) < 1e-6) { // 认为相等  }

     */
        printf("\n========================Floating Point Type========================\n");
        float f1 = 33.1234563f; 
        float f2 = 33.1234564f;
        if( f1 == f2) 
            printf("f1 == f2, f1: %e, f2: %E\n", f1, f2);                       // ✅ f1 == f2, f1: 3.312346e+01, f2: 3.312346E+01

        printf("float: %e, %a\n",   123000.0f, 123000.0f);                      // 1.230000e+05, 0x1.e078p+16
        printf("float: %e, %a\n",   0.036f, 0.036f);                            // 3.600000e-02, 0x1.26e978p-5
        printf("float: %e, %a\n",   5.0f, 5.0f);                                // 5.000000e+00, 0x1.4p+2
        printf("float: %e, %a\n",  0.0000000000001752f, 0.0000000000001752f);   // 1.752000e-13, 0x1.8a83ecp-43
        printf("float: %e, %a\n",   9.625f, 9.625f);                            // 9.625000e+00, 0x1.34p+3
        
        double x1 = 123.456e+3; // 123.456 x 10^3
        // 等同于
        double x2 = 123.456e3;

    /**
        4. 布尔类型:
            C 语言原来并没有为布尔值单独设置一个类型，而是使用整数0表示伪，所有非零值表示真。

            C99 标准添加了类型 _Bool，表示布尔值。但是，这个类型其实只是整数类型的别名，还是使用 0 表示伪，1 表示真
            参考：https://gcc.gnu.org/onlinedocs/gcc/Boolean-Type.html

            头文件 stdbool.h 定义了另一个类型别名 bool，并且定义了 true 代表 1、false 代表 0。只要加载这个头文件，就可以使用这几个关键字。
     */
        printf("\n========================Bool Type========================\n");
        int flag = 1;
        if (flag) {
            printf("flag is true!\n");
        }
        // c99 _Bool
        _Bool isNormal; bool isOk;
        isNormal = 1; isOk = true;
        if (isNormal && isOk)
            printf("Everything is OK.\n");

    /**
        5. 字面量的类型:
            字面量（literal）指的是代码里面直接出现的值。比如 `int x = 123;`中，x 是变量，123 就是字面量。
            
            编译时，字面量也会写入~内存~ELF 文件，因此编译器必须为字面量指定数据类型，就像必须为变量指定数据类型一样。
            使用命令可以查看：`objdump -d -S -w  build/06_data_type/data_type | grep -A 2 '12302'`

            一般情况下，十进制整数字面量（比如 123）会被编译器指定为 int 类型。
            如果一个数值比较大，超出了 int 能够表示的范围，编译器会将其指定为 long int。
            如果数值超过了 long int，会被指定为 unsigned long。
            如果还不够大，就指定为 long long 或 unsigned long long。
            比如：小数（比如 3.14）会被指定为 double 类型。
     */
        printf("\n========================Literal Type========================\n");
        int l = 12302;
    

    /**
        6. 字面量后缀:
            有时候，程序员希望为字面量指定一个不同的类型。

            比如，编译器将一个整数字面量指定为 int 类型，但是程序员希望将其指定为 long 类型，这时可以为该字面量加上后缀 l/L，编译器就知道要把这个字面量的类型指定为 long。
            八进制和十六进制的值，也可以使用后缀l和L指定为 Long 类型，比如 020L 和 0x20L。

            如果希望指定为无符号整数 unsigned int，可以使用后缀 u/U。
            int x = 123U;
            L 和 U 可以结合使用，表示 unsigned long 类型。L 和 U 的大小写和组合顺序无所谓。
            int x = 123LU;
            u 还可以与其他整数后缀结合，放在前面或后面都可以，比如 10UL、10ULL 和 10LLU 都是合法的。

            对于浮点数，编译器默认指定为 double 类型，如果希望指定为其他类型，需要在小数后面添加后缀 (f/F float) 或(l/L long double)。
            科学计数法也可以使用后缀。
                1.2345e+10F
                1.2345e+10L

            常用的字面量后缀 参考 README.md
     */
        printf("\n========================Literal Subfix========================\n");
        int w = 12302L;     // 定义为 long int，赋值时进行隐式转换。

        // 常用的字面量后缀
        int           v1 = 1234;
        long int      v2 = 1234L;
        long long int v3 = 1234LL;

        unsigned int           v4 = 1234U;
        unsigned long int      v5 = 1234UL;
        unsigned long long int v6 = 1234ULL;

        float       v7 = 3.14f;
        double      v8 = 3.14;
        long double v9 = 3.14L;

    /**
        7. 溢出:
            每一种数据类型都有数值范围，如果存放的数值超出了这个范围（小于最小值或大于最大值），需要更多的二进制位存储，就会发生溢出。
            大于最大值，叫做向上溢出（overflow）；小于最小值，叫做向下溢出（underflow）。
            一般来说，编译器不会对溢出报错，会正常执行代码，但是会忽略多出来的二进制位，只保留剩下的位，这样往往会得到意想不到的结果。所以，应该避免溢出。
     */
        printf("\n======================== Overflow ========================\n");
        unsigned char uc = 255;
        uc = uc + 1;
        printf("uc value: %d\n", uc);       // 0
        // 对于减法也是： 比如 0 - 1 ==> 0 + (-1) ==> 0b0000_0000 + 0b1111_1111 ==> 0b1111_1111 = 255
        // 注意不能直接用 uc - 1，应该会转换成 int，获取到不符合的结果。
        printf("uc value: %d\n", --uc);   // 255

        // 溢出很容易被忽视，编译器又不会报错，所以必须非常小心。如下情况:
        for (unsigned char i = 100; i >= 0; --i)    // 错误，因为无符号的就没有负值，会一直在 0 ~ 255 中循环，导致判断结果成立，条件无线循环。
            { if(i == 0) break;}; // 为了打破循环添加的。
        unsigned int m = 5, n = 7;
        if (m - n < 0           ) { };              // 错误，m - n 向下溢出，总是大于 0 的。应该写成 if ( m < n )
        if (m + n > UCHAR_MAX   ) { };              // 错误，m + n 向上溢出。应该写成 if ( m > UCHAR_MAX - n )        

    /**
        8. sizeof 运算符:
            sizeof是 C 语言提供的一个运算符，返回某种数据类型或某个值占用的字节数量。它的参数可以是数据类型的关键字，也可以是变量名或某个具体的值。
     */
        printf("\n======================== Overflow ========================\n");

    printf("\nCongratulations! you have learned the data types of C language!\n");
    return 0;
}