
#include <stdio.h>
#include <string.h>

int my_strlen(char *s) {
    int count = 0;
    while (s[count] != '\0')
        count++;
    return count;
}

char* my_strcpy(char* dest, const char* source) {
    char* ptr = dest;
    while ( (*dest++ = *source++) );
    return ptr;
}

/**
 * 
 * @see https://wangdoc.com/clang/string
 *
 */
int main(void){

    /**
        1. 简介

            C 语言没有单独的字符串类型，字符串被当作字符数组，即 char 类型的数组。比如，字符串“Hello”是当作数组 {'H', 'e', 'l', 'l', 'o'} 处理的。

            编译器会给数组分配一段连续内存，所有字符储存在相邻的内存单元之中。在字符串结尾，C 语言会自动添加一个全是二进制 0 的字节，写作 `\0` 字符，表示字符串结束。
            字符 `\0` 不同于字符 0，前者的 ASCII 码是 0（二进制形式00000000），后者的 ASCII 码是 48（二进制形式00110000）。所以，字符串“Hello”实际储存的数组是{'H', 'e', 'l', 'l', 'o', '\0'}。
            
            所有字符串的最后一个字符，都是 `\0`。这样做的好处是，C 语言不需要知道字符串的长度，就可以读取内存里面的字符串，只要发现有一个字符是\0，那么就知道字符串结束了。
            char localString[10];
            示例声明了一个 10 个成员的字符数组，可以当作字符串。由于必须留一个位置给 \0，所以最多只能容纳 9 个字符的字符串。

            字符串写成数组的形式，是非常麻烦的。C 语言提供了一种简写法，双引号之中的字符，会被自动视为字符数组。
            {'H', 'e', 'l', 'l', 'o', '\0'}  <==> "Hello"
            上面两种字符串的写法是等价的，内部存储方式都是一样的。双引号里面的字符串，不用自己添加结尾字符 `\0`，C 语言会自动添加。
            注意，双引号里面是字符串，单引号里面是字符，两者不能互换。如果把Hello放在单引号里面，编译器会报错。
            'Hello' // 报错 ❌

            另一方面，即使双引号里面只有一个字符（比如"a"），也依然被处理成字符串（存储为 2 个字节 {'a','\0'} ），而不是字符'a'（存储为 1 个字节）。

            如果字符串内部包含双引号，则该双引号需要使用反斜杠转义。
            "She replied, \"It does.\""
            反斜杠还可以表示其他特殊字符，比如换行符（\n）、制表符（\t）等。

            如果字符串过长，可以在需要折行的地方，使用反斜杠（\）结尾，将一行拆成多行。
            "hello \
            world"          // 示例中，第一行尾部的反斜杠，将字符串拆成两行。
            上面这种写法有一个缺点，就是第二行必须顶格书写，如果想包含缩进，那么缩进也会被计入字符串。为了解决这个问题，C 语言允许合并多个字符串字面量，只要这些字符串之间没有间隔，或者只有空格，C 语言会将它们自动合并。
            char greeting[50] = "Hello, ""how are you ""today!";    ✅
            char greeting[50] = "Hello, "
                                "how are you "
                                "today!";                           ✅


     */
        printf("========================   Intro   ========================\n");
        char localString[10] = {'h','e','l','l','o'};   // last char is '\0'
        char* p = localString; int i = 0;
        while( *p++ != '\0' ) { i++; }
        printf("localString has a total of %d characters, except '\\0'\n", i);
        
        char* s10 = "Hello";

        // char* s11 = 'hello';                         // ❌ incompatible integer to pointer conversion initializing 'char *' with an expression of type 'int'

        char* s12 = "She replied, \"It does.\"";

        char* s13 = "Hello, ""how are you ""today!";

        char* s14 = "Hello, "
                    "how are you "
                    "today!";

        printf("string s10 is : %s\n", s10);
        printf("string s12 is : %s\n", s12);
        printf("string s13 is : %s\n", s13);
        printf("string s14 is : %s\n", s14);

    /**
        2. 字符串变量的声明

            字符串变量可以声明成一个字符数组，也可以声明成一个指针，指向字符数组。
            // 写法一
            char s[14] = "Hello, world!";
            // 写法二
            char* s = "Hello, world!";
            上面两种写法都声明了一个字符串变量 s。如果采用第一种写法，由于字符数组的长度可以让编译器自动计算，所以声明时可以省略字符数组的长度。
            char s[] = "Hello, world!";

            字符数组的长度，可以大于字符串的实际长度。
            char s[50] = "hello";
            上面示例中，字符数组 s 的长度是 50，但是字符串“hello”的实际长度只有 6（包含结尾符号\0），所以后面空出来的 44 个位置，都会被初始化为 \0。

            字符数组的长度，不能小于字符串的实际长度。
            char s[5] = "hello";
            上面示例中，字符串数组 s 的长度是 5，小于字符串“hello”的实际长度 6，这时编译器会警告。因为如果只将前 5 个字符写入，而省略最后的结尾符号 \0，这很可能导致后面的字符串相关代码出错。
            实际如下测试，这个没问题，数组再小的话，会有警告，`initializer-string for char array is too long`，可以正常执行，但是输出不确定。

            字符指针和字符数组，这两种声明字符串变量的写法基本是等价的，但是有两个差异。

                第一个差异是，指针指向的字符串，在 C 语言内部被当作常量，不能修改字符串本身。
                char* s = "Hello, world!";
                s[0] = 'z';
                上面代码使用指针，声明了一个字符串变量，然后修改了字符串的第一个字符。这种写法是错的，会导致难以预测的后果，执行时很可能会报错。
                如果使用数组声明字符串变量，就没有这个问题，可以修改数组的任意成员。
                为了提醒用户，字符串声明为指针后不得修改，可以在声明时使用 const 说明符，保证该字符串是只读的。一旦修改，编译器肯定会报错。

                    为什么字符串声明为指针时不能修改，声明为数组时就可以修改？
                    原因是系统会将字符串的字面量保存在内存的常量区，这个区是不允许用户修改的。
                    声明为指针时，指针变量存储的值是一个指向常量区的内存地址，因此用户不能通过这个地址去修改常量区。
                    但是，声明为数组时，编译器会给数组单独分配一段内存，字符串字面量会被编译器解释成字符数组，逐个字符写入这段新分配的内存之中，而这段新内存是允许修改的。

                第二个差异是，指针变量可以指向其它字符串。
                char* s = "hello";
                s = "world";
                示例中，字符指针可以指向另一个字符串。
                但是，字符数组变量不能指向另一个字符串。字符数组的数组名，总是指向初始化时的字符串地址，不能修改。

                想要重新赋值，必须使用 C 语言原生提供的 strcpy() 函数，通过字符串拷贝完成赋值。
                这样做以后，数组变量的地址还是不变的，即 strcpy() 只是在原地址写入新的字符串，而不是让数组变量指向新的地址。

                    为什么数组变量不能赋值为另一个数组？
                    原因是数组变量所在的地址无法改变，或者说，编译器一旦为数组变量分配地址后，这个地址就绑定这个数组变量了，这种绑定关系是不变的。
                    C 语言也因此规定，数组变量是一个不可修改的左值，即不能用赋值运算符为它重新赋值。


     */
        printf("\n========================   The declaration of string variables   ========================\n");

        // char s20[3] = "world";          
        // printf("string s20 is : %s\n", s20);         // string s20 is : worhello

        // 指针可以重新赋值，不可修改内容
        char* s21 = "Hello, world!";
        // s21[0] = 'z';                                // ❌ Segment Fault
        s21 = "world";                                  // ✅

        // 数组可以修改内容，不可重新赋值。
        char s23[] = "hello";
        // s23 = "world";                               // ❌ error: assignment to expression with array type
        s23[1] = '_';                                   // ✅

        // 但是数组声明的字符串，通过指针是可以修改内容的。其实换种思路想，数组下标的方式也是指针访问另一种方式，E1[E2] <==> *((E1)+(E2))
        char* s231 = s23;
        *(s231 + 2) = '^';
        puts(s23);                                      // h_^lo

        char s24[10];
        strcpy(s24, "abc");
        printf("string s24 is : %s\n", s24);            // string s24 is : abc
    
    /**
        3. strlen()

            strlen()函数返回字符串的字节长度，不包括末尾的空字符 `\0`。该函数的原型如下。
            // string.h
            size_t strlen(const char* s);
            它的参数是字符串变量，返回的是 size_t[current:long unsigned int] 类型的无符号整数，除非是极长的字符串，一般情况下当作 int 类型处理即可。
            下面有一个用法实例。

            注意，字符串长度（strlen()）与字符串变量长度（sizeof()），是两个不同的概念。

            如果不使用这个函数，可以通过判断字符串末尾的\0，自己计算字符串长度。

     */
        printf("\n========================   strlen()   ========================\n");
        char* s = "contact#wtfu.site";
        int len = strlen(s);

        // strlen() vs sizeof()
        char s30[50] = "hello";
        printf("%td\n", strlen(s30));                    // 5
        printf("%td\n", sizeof(s30));                    // 50

        printf("%d\n",  my_strlen(s30));                 // 5

    /**
        4. strcpy()

            字符串的复制，不能使用赋值运算符，直接将一个字符串赋值给字符数组变量。
            
            下面示例中两种字符串的复制写法，都是错的。因为数组的变量名是一个固定的地址，不能修改，使其指向另一个地址。

            如果是字符指针，赋值运算符（=）只是将一个指针的地址复制给另一个指针，而不是复制字符串。

            C 语言提供了 strcpy() 函数，用于将一个字符串的内容复制到另一个字符串，相当于字符串赋值。该函数的原型定义在 string.h 头文件里面。
            strcpy(char dest[], const char source[])
            strcpy() 接受两个参数，第一个参数是目的字符串数组，第二个参数是源字符串数组。
            strcpy() 的返回值是一个字符串指针（即char*），指向第一个参数。
            复制字符串之前，必须要保证第一个参数的长度不小于第二个参数，否则虽然不会报错，但会溢出第一个字符串变量的边界，发生难以预料的结果。
            第二个参数的 const 说明符，表示这个函数不会修改第二个字符串。

            strcpy() 返回值的另一个用途，是连续为多个字符数组赋值。
            strcpy(str1, strcpy(str2, "abcd"));

            另外，strcpy() 的第一个参数最好是一个已经声明的数组，而不是声明后没有进行初始化的字符指针。
            char* str;
            strcpy(str, "hello world");     // 错误
            上面的代码是有问题的。strcpy() 将字符串分配给指针变量 str，但是 str 并没有进行初始化，指向的是一个随机的位置，因此字符串可能被复制到任意地方。

            如果不用strcpy()，自己实现字符串的拷贝 my_strcpy。

            strcpy() 函数有安全风险，因为它并不检查目标字符串的长度，是否足够容纳源字符串的副本，可能导致写入溢出。
            如果不能保证不会发生溢出，建议使用 strncpy() 函数代替。

     */
        printf("\n========================   strcpy()   ========================\n");

        char str1[10];
        char str2[10];
        // str1 = "abc";            // 报错
        // str2 = str1;             // 报错
    
        // 代码可以运行，结果是两个指针变量 s1 和 s2 指向同一字符串，而不是将字符串 s1 的内容复制给 s2。
        char* s1;
        char* s2;
        s1 = "abc";
        s2 = s1;

        char s40[] = "Hello, world!";
        char t40[100];
        strcpy(t40, s40);
        t40[0] = 'z';
        printf("%s\n",   s40);      // "Hello, world!"
        printf("%s\n\n", t40);      // "zello, world!"

        char str41[10];
        strcpy(str41, "abcd");

        // 示例中，从 s42 的第 7 个位置开始拷贝字符串 beast，前面的位置不变。
        // 这导致 s42 后面的内容都被截去了，因为会连 beast 结尾的空字符一起拷贝。strcpy() 返回的是一个指针，指向拷贝开始的位置。
        char* s41 = "beast";
        char s42[40] = "Be the best that you can be.";
        char* ps;
        ps = strcpy(s42 + 7, s41);
        puts(s42);                  // Be the beast
        puts(ps);                   // beast

        printf("\ncalled my_strcpy result is: %s\n", my_strcpy(s42,"abalone"));

    /**
        5. strncpy()

            strncpy() 跟 strcpy() 的用法完全一样，只是多了第 3 个参数，用来指定复制的最大字符数，防止溢出目标字符串变量的边界。
            char* strncpy( char* dest, char* src, size_t n);
            原型中，第三个参数 n 定义了复制的最大字符数。如果达到最大字符数以后，源字符串仍然没有复制完，就会停止复制，这时目的字符串结尾将 没有终止符 `\0`，这一点务必注意。
            如果源字符串的字符数小于 n ，则 strncpy() 的行为与 strcpy() 完全一致。
                strncpy(str1, str2, sizeof(str1) - 1);
                str1[sizeof(str1) - 1] = '\0';

            strncpy()也可以用来拷贝部分字符串。
     */
        printf("\n========================   strncpy()   ========================\n");
        char s51[40];
        char s52[12] = "hello world";
        strncpy(s51, s52, 5);
        s51[5] = '\0';
        printf("%s\n", s51);        // hello

    /**
        6. strcat()

            strcat() 函数用于连接字符串。
            它接受两个字符串作为参数，把第二个字符串的副本添加到第一个字符串的末尾。这个函数会改变第一个字符串，但是第二个字符串不变。
            它的返回值是一个字符串指针，指向第一个参数。
            该函数的原型定义在 string.h 头文件里面。
            char* strcat(char* s1, const char* s2);

            注意，strcat() 的第一个参数的长度，必须足以容纳添加第二个参数字符串。
            否则，拼接后的字符串会溢出第一个字符串的边界，写入相邻的内存单元，这是很危险的，建议使用下面的 strncat() 代替。

     */
        printf("\n========================   strcat()   ========================\n");

        char s61[12] = "hello";
        char s62[6] = "world";
        strcat(s61, s62);
        puts(s61);                  // "helloworld"

    /**
        7. strncat()

            strncat() 用于连接两个字符串，用法与 strcat() 完全一致，只是增加了第三个参数，指定最大添加的字符数。
            在添加过程中，一旦达到指定的字符数，或者在源字符串中遇到空字符 `\0`，就不再添加了。
            它的原型定义在 string.h 头文件里面。
            char* strncat( const char* dest, const char* src, size_t n);
            strncat() 返回第一个参数，即目标字符串指针。

            为了保证连接后的字符串，不超过目标字符串的长度，strncat() 通常会写成下面这样。
            strncat(str1, str2, sizeof(str1) - strlen(str1) - 1);

     */
        printf("\n========================   strncat()   ========================\n");
        
        // 示例中，s71 的变量长度是 10，字符长度是 6，两者相减后再减去 1，得到 3，表明 s71 最多可以再添加三个字符，所以得到的结果是 MondayTue。
        char s71[10] = "Monday";
        char s72[8]  = "Tuesday";
        strncat(s71, s72, 3);
        puts(s71);                  // "MondayTue"

    /**
        8. strcmp()

            如果要比较两个字符串，无法直接比较，只能一个个字符进行比较，C 语言提供了 strcmp() 函数。

            strcmp() 函数用于比较两个字符串的内容。该函数的原型如下，定义在 string.h 头文件里面。
            int strcmp(const char* s1, const char* s2);
            
            按照字典顺序，如果两个字符串相同，返回值为 0；如果 s1 小于 s2 ，strcmp()返回值小于 0；如果 s1 大于 s2，返回值大于 0。

            注意，strcmp() 只用来比较字符串，不用来比较字符。
            因为字符就是小整数，直接用相等运算符（==）就能比较。所以，不要把字符类型（char）的值，放入 strcmp() 当作参数。

     */
        printf("\n========================   strcmp()   ========================\n");
    
        char* s81 = "Happy New Year";
        char* s82 = "Happy New Year";
        char* s83 = "Happy Holidays";
        printf("the compare value is: %d\n", strcmp(s81, s82));     //  0
        printf("the compare value is: %d\n", strcmp(s81, s83));     //  6
        printf("the compare value is: %d\n", strcmp(s83, s81));     // -6

    /**
        9. strncmp()

            由于 strcmp() 比较的是整个字符串，C 语言又提供了 strncmp() 函数，只比较到指定的位置。
            
            该函数增加了第三个参数，指定了比较的字符数。它的原型定义在 string.h 头文件里面。
            int strncmp(const char* s1, const char* s2, size_t n);
            它的返回值与 strcmp() 一样。如果两个字符串相同，返回值为 0；如果 s1 小于 s2，strcmp() 返回值小于 0；如果 s1 大于 s2，返回值大于 0。

     */
        printf("\n========================   strncmp()   ========================\n");
    
        // 示例只比较两个字符串的前 5 个字符
        char s91[12] = "hello world";
        char s92[12] = "hello C";
        if (strncmp(s91, s92, 5) == 0) {
            printf("They all have hello.\n");
        }

    /**
        10. sprintf()，snprintf()

            sprintf() 函数跟 printf() 类似，但是用于将数据写入字符串，而不是输出到显示器。该函数的原型定义在 stdio.h 头文件里面。
            int sprintf(char* s, const char* format, ...);
            sprintf() 的第一个参数是字符串指针变量，其余参数和 printf() 相同，即第二个参数是格式字符串，后面的参数是待写入的变量列表。
            sprintf() 的返回值是写入变量的字符数量（不计入尾部的空字符\0）。如果遇到错误，返回负值。

            sprintf() 有严重的安全风险，如果写入的字符串过长，超过了目标字符串的长度，sprintf() 依然会将其写入，导致发生溢出。
            为了控制写入的字符串的长度，C 语言又提供了另一个函数 snprintf()。

            snprintf() 只比 sprintf()多了一个参数 n，用来控制写入变量的字符串不超过 n - 1 个字符，剩下一个位置写入空字符 `\0`。
            下面是它的原型。
            int snprintf(char*s, size_t n, const char* format, ...);

            snprintf() 总是会【自动写入】字符串结尾的空字符。如果你尝试写入的字符数超过指定的最大字符数，snprintf() 会写入 n - 1 个字符，留出最后一个位置写入空字符。

            snprintf() 的返回值是写入格式字符串的字符数量（不计入尾部的空字符\0）。
            如果 n 足够大，返回值应该小于 n，但是有时候格式字符串的长度可能大于 n，那么这时返回值会大于 n，但实际上真正写入变量的还是 n-1 个字符。
            如果遇到错误，返回一个负值。因此，返回值只有在非负并且小于 n 时，才能确认完整的格式字符串写入了变量。

     */
        printf("\n========================   sprintf()，snprintf()   ========================\n");
    
        // 示例中，sprintf() 将输出内容组合成 “hello world”，然后放入了变量 s。
        char first[6] = "hello";
        char last[6] = "world";
        char s100[40];
        int count = sprintf(s100, "%s %s", first, last);
        printf("%s, and write char count is: %d\n", s100, count);       // hello world, and write char count is: 11

        // 例子中，snprintf() 的第二个参数是 8，表示写入字符串的最大长度不超过 8（包括尾部的空字符）。
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wformat-truncation"
        int numbe = snprintf(s100, 8, "%s %s", "hello", "world");
        #pragma GCC diagnostic pop
        printf("%s, and write char count is: %d\n", s100, numbe);       // hello w, and write char count is: 11

    /**
        11. 字符串数组

            如果一个数组的每个成员都是一个字符串，需要通过二维的字符数组实现。每个字符串本身是一个字符数组，多个字符串再组成一个数组。

            需要注意：通过 char *weekdays[]，指针申明的字符数组，也是不可以通过指针去修改内容的。和第二部分`字符串变量的声明`时候的注意事项一致。

     */
        printf("\n========================   String array   ========================\n");

        // 示例就是一个字符串数组，一共包含 7 个字符串，所以第一维的长度是 7。其中，最长的字符串的长度是 10（含结尾的终止符 `\0`），所以第二维的长度统一设为 10。
        // 
        // 因为第一维的长度，编译器可以自动计算，所以可以省略。
        // char weekdays[7][10] = {
        // 数组可以修改内容
        char weekdays110[][10] = {
            "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
        };
        // weekdays110[3] = "hello";       // ❌ expression must be a modifiable lvalueC/C++(137), [array type 'char[10]' is not assignable]
        char *ptr110 = weekdays110[2];
        *ptr110 = ']';
        for (int i = 0; i < 7; i++) { printf("%s\n", weekdays110[i]); } puts("");


        // 指针可以重新赋值。
        // 数组的第二维，长度统一定为 10，有点浪费空间，因为大多数成员的长度都小于 10。解决方法就是把数组的第二维，从字符数组改成字符指针。
        char *weekdays111[] = {
            "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
        };
        weekdays111[3] = "exception";
        char *ptr111 = weekdays111[2];
        // *ptr111 = ']';                  // ❌ Segmentation fault
        for (int i = 0; i < 7; i++) { printf("%s\n", weekdays111[i]); }

    
    printf("\n\033[1;31;42mCongratulations! you have learned the string of C language!\033[0m\n");
    return 0;
}