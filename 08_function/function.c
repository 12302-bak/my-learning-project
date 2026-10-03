
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void undefined_f(){ printf("called for `undefined_f()` via undefined_f(1)!\n"); }

unsigned long Fibonacci(unsigned n) {
    if (n > 2)
        return Fibonacci(n - 1) + Fibonacci(n - 2);
    else
        return 1;
}

void increment(int a) {
    a++;
}

void do_stuff(void);

extern int sum(int, int);

void counter(void);

extern int static_method(int);

void update_prt(int* p);

double average(int i, ...);

const int global_var = 10;

/**
 * @see https://wangdoc.com/clang/function
 * 
 * @args: --port 8080 --mode "production" input.txt --verbose
 */
int main(int argc, char *argv[], char *envp[]){ // envp —— 是 Unix / GCC 扩展，不是 C 标准，可移植性差。

    for (int i = 0; i < argc; i++) {            printf("argv[%d] = \"%s\"\n", i, argv[i]); }
    for (char **p = envp; *p != NULL; p++) {    printf("\nenv: %s\n\n", *p); break; }

    /**
        1. 简介

            函数是一段可以重复执行的代码。它可以接受不同的参数，完成对应的操作。比如 main 函数。

            函数的声明： 语法有以下几点，需要注意。
            （1）返回值类型。函数声明时，首先需要给出返回值的类型。
            （2）参数。函数名后面的圆括号里面，需要声明参数的类型和参数名。
            （3）函数体。函数体要写在大括号里面，后面（即大括号外面）不需要加分号。大括号的起始位置，可以跟函数名在同一行，也可以另起一行，此处采用同一行的写法。
            （4）return 语句。return 语句给出函数的返回值，程序运行到这一行，就会跳出函数体，结束函数的调用。如果函数没有返回值，可以省略 return 语句，或者写成 return; 。
            （5）C 语言标准规定，函数只能声明在源码文件的顶层，不能声明在其他函数内部。
            （6）不返回值的函数，使用 void 关键字表示返回值的类型。没有参数的函数，声明时要用 void 关键字表示参数类型。
                func(void) 和 func() 在 C 语言里不是一回事，func()表示：参数列表未指定，编译器不会严格检查调用时传了几个参数，调用 func(1)、func("a", 2) 可能都不会报错。
                当前环境会有 clang 检查警告：passing arguments to 'undefined_f' without a prototype is deprecated in all versions of C and is not supported in C23。
                所以之前写的`int main()`都是不严谨的，无参需要使用 void。
            （7）函数不要返回`内部变量`的指针。因为当函数结束运行时，内部变量就消失了，这时指向内部变量的内存地址就是无效的，再去使用这个地址是非常危险的。
                int* f(void) {
                    int i;
                    return &i;
                }

            函数的调用：只要在函数名后面加上圆括号就可以了，实际的参数放在圆括号里面。
            （1）函数调用时，参数个数必须与定义里面的参数个数一致，参数过多或过少都会报错。
            （2）函数必须声明后使用，否则会编译报错。
            （3）函数可以调用自身，这就叫做递归（recursion）。

     */
        printf("========================   Intro   ========================\n");
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wdeprecated-non-prototype"
        #pragma clang diagnostic ignored "-Weverything"
        undefined_f(1);                                         // called for `undefined_f()` via undefined_f(1)!
        #pragma clang diagnostic pop
        printf("Fibonacci for 10: %lu\n\n", Fibonacci(10));     // Fibonacci for 10: 55
        
    /**
        2. main()

            C 语言规定，main()是程序的入口函数，即所有的程序一定要包含一个 main()函数。程序总是从这个函数开始执行，如果没有该函数，程序就无法启动。其他函数都是通过它引入程序的。
            main()的写法与其他函数一样，要给出返回值的类型和参数的类型。
            C 语言约定，返回值 0 表示函数运行成功，如果返回其他非零整数，就表示运行失败，代码出了问题。系统根据 main() 的返回值，作为整个程序的返回值，确定程序是否运行成功。
            正常情况下，如果 main() 里面省略 return 0 这一行，编译器会自动加上，即 main() 的默认返回值为 0。
            由于 C 语言只会对main()函数默认添加返回值，对其他函数不会这样做，所以建议总是保留return语句，以便形成统一的代码风格。

            相关知识：[不用main函数编程](https://xhsgg12302.github.io/archive/hugo/corner/assmebly/book/example/#研究试验4-不用main-函数编程)
     */
        printf("========================   main()   ========================\n");
        printf("Can program without main function?\n\n");

    /**
        3. 参数的传值引用

            如果函数的参数是一个变量，那么调用时，传入的是这个变量的值的拷贝，而不是变量本身。所以，如果参数变量发生变化，最好把它作为返回值传出来。
            可以参考：[用栈传递参数](https://xhsgg12302.github.io/archive/hugo/corner/assmebly/book/example/#附注4-用栈传递参数)

            如果想要传入变量本身，只有一个办法，就是传入变量的地址。通过地址对变量进行读写。
     */
        printf("========================Pass-by-reference of parameters========================\n");
        int i = 10; increment(i);
        printf("increment for \"%d\" is: %d\n\n", i, i);  // 10

    /**
        4. 函数指针

            函数本身就是一段内存里面的代码，C 语言允许通过指针获取函数。有了函数指针，通过它也可以调用函数。
            申明如是：  `返回类型 (* 指针变量)(参数类型列表) = `；
            重新赋值：  `指针变量 = &var`

            C 标准规定：一个函数指示符（function designator），除了作为 sizeof 或一元 & 的操作数之外，都会被转换为"指向该函数的指针"。
            这个可以通过编译器魔法实现。
            C 语言的函数调用运算符 () 实际上作用于“函数的指针，当除了上述的`sizeof`和`&`操作之外，指示符都会退化成为函数指针。
            也就是说：
                printf 这个名字本身是"函数指示符"（function designator），类型是 int (const char*, ...)（函数类型）
                在大多数表达式里，它会自动变成 int (*)(const char*, ...)（函数指针类型）

            如果一个函数的参数或返回值，也是一个函数，那么函数原型可以写成下面这样。
            int compute(int (*myfunc)(int), int, int);
     */
        printf("========================pointer of function========================\n");
        void (*increment_ptr)(int) = &increment;

        int (*printf_ptr)(const char *, ...) = (void *)0x7ffff7e03100;          // 固定地址和操作系统 ASLR 有关，所以下面的方式比较稳妥。容器也可参考`"securityOpt": [ "seccomp=unconfined" ]`
        printf_ptr = &printf;                                                   // 重新赋值
        printf("printf's     address is: %p\n", &printf);                       // 0x7ffff7e03100
        printf("printf_ptr's address is: %p\n", &printf_ptr);                   // 0x7fffffffdce0
        
        // 有了指针，可以通过指针直接调用函数，() 是作用于函数指针的。
        printf_ptr("called method 01\n");
        // 或者`解引用`  (*printf_ptr)(...)
        // 它虽然理论上返回了函数实体，但由于函数实体无法直接参与运算，
        // 它立刻又被编译器自动转换回了“指向该函数的指针”。
        // 因此，哪怕你写 (*******printf_ptr)("Hello\n")，程序也能正常运行。
        (*****printf_ptr)("called method 02\n");
        // 比较特殊的是，C 语言中，函数名本身会被编译器衰变为指向函数代码的指针，
        // 也就是说 printf 和 &printf 是一样的。                                   // *printf ==> printf ==> &printf
        printf(     "called method 03\n");
        (&printf)(  "called method 04\n");
        (***printf)("called method 05\n");

    /**
        5. 函数原型

            前面说过，函数必须先声明，后使用。由于程序总是先运行 main()函数，导致所有其他函数都必须在 main()函数之前声明。否则编译时会产生警告。
            但是，main()是整个程序的入口，也是主要逻辑，放在最前面比较好。另一方面，对于函数较多的程序，保证每个函数的顺序正确，会变得很麻烦。
            C 语言提供的解决方法是，只要在程序开头处给出函数原型，函数就可以先使用、后声明。
            所谓函数原型，就是提前告诉编译器，每个函数的`返回类型`和`参数类型`。其他信息都不需要，也不用包括函数体，具体的函数实现可以后面再补上。
            函数原型包括`参数名`也可以，虽然这样对于编译器是多余的，但是阅读代码的时候，可能有助于理解函数的意图。
            注意，函数原型必须以分号结尾。
            一般来说，每个源码文件的头部，都会给出当前文件使用的所有函数的原型。
     */
        printf("\n========================prototype of function========================\n");
        printf("function prototype `int twice(int);` equals `int twice(int num);`\n");

    /**
        6. exit()

            exit()函数用来终止整个程序的运行。一旦执行到该函数，程序就会立即结束。该函数的原型定义在头文件 stdlib.h 里面。
            
            exit()可以向程序外部返回一个值，它的参数就是程序的返回值。
            一般来说，使用两个常量作为它的参数：EXIT_SUCCESS（相当于 0）表示程序运行成功，EXIT_FAILURE（相当于 1）表示程序异常中止。这两个常数也是定义在 stdlib.h 里面。

            在 main()函数里面，exit()等价于使用 return 语句。其他函数使用 exit()，就是终止整个程序的运行，没有其他作用。

            C 语言还提供了一个 atexit()函数，用来登记 exit() 执行时额外执行的函数，用来做一些退出程序时的收尾工作。该函数的原型也是定义在头文件 stdlib.h。
            atexit()的参数是一个函数指针。注意，它的参数函数（下例的 do_stuff ）不能接受参数，也不能有返回值。
            只有`return`，也会如期调用，因为其他地方会执行 exit()。
     */
        printf("\n======================== exit() ========================\n");
        atexit(do_stuff);                   // 登记 exit() 需要执行的函数。

    /**
        7. 函数说明符

            C 语言提供了一些函数说明符，让函数用法更加明确。
            
            1. extern 说明符
                对于多文件的项目，源码文件会用到其他文件声明的函数。这时，当前文件里面，需要给出外部函数的原型，并用 extern 说明该函数的定义来自其他文件。
                不过，由于函数原型默认就是 extern，所以这里不加 extern，效果是一样的。

            2. static 说明符
                默认情况下，每次调用函数时，函数的内部变量都会重新初始化，不会保留上一次运行的值。static 说明符可以改变这种行为。
                对于变量的修饰可以从`可见性`、`数据存储位置`两方面去理解。

                用于函数内部声明变量：(`可见性`、`数据存储位置`)
                    表示该变量只需要初始化一次，不需要在每次调用时都进行初始化。也就是说，它的值在两次调用之间保持不变。
                    注意，static 修饰的变量初始化时，只能赋值为常量，不能赋值为变量。
                        int i = 3;
                        static int j = i; // ❌

                块作用域：(`可见性`、`数据存储位置`)
                    static 声明的变量有默认值 0。
                        static int foo;
                        // 等同于
                        static int foo = 0;

                修饰函数：(`可见性`)
                    static 关键字表示该函数只能在当前文件里使用，如果没有这个关键字，其他文件也可以使用这个函数（通过声明函数原型）。
                    没有编译警告，只有编译错误：`undefined reference to `static_method'`

                参数：(`契约`) C99 标准引入的一个特殊语法
                    int sum_array(int a[static 3], int n) { }
                    示例中，static 对程序行为不会有任何影响，只是用来告诉编译器，该数组长度至少为 3，某些情况下可以加快程序运行速度。
                    另外，需要注意的是，对于多维数组的参数，static 仅可用于第一维的说明。

            3. const 说明符
                const 在 C 里不是“常量”，更准确地说是只读限定符：它限制某个对象不能通过当前标识符被修改。

                对于变量：
                    全局 const，通常会触发段错误
                    局部 const，可能绕过编译器检查，但属于未定义行为（UB）

                对于指针：int* p
                    const int* p;       限制修改 `*p`，也就是指针所指地址里面的值。但是不影响修改 p = &other.
                    int* const p;       限制修改 `p `，也就是指针所指地址。但是不影响 *p = 12302.
                    const int* const p; 同时限制 `p`、`*p`.


     */
        printf("\n======================== Designator ========================\n");
        printf("called from extern function `sum`: %d\n", sum(1, 2));

        counter();  // 1
        counter();  // 2
        counter();  // 3

        int temp = 0;
        //temp = static_method(20);             // compile error        ❌
        printf("called from extern static function `static_method`: %d\n", temp);
        
        // const indicator
        const int local_var = 20;
        int* p;
        // p = (int*)&global_var;  *p = 30;     // Segmentation fault   ❌
        p = (int*)&local_var ;  *p = 30;        // local_var = 30       ✅

        temp = 111;
        update_prt(&temp);
        printf("update `*p` of `int* const p` : %d\n", temp);

    /**
        8. 可变参数

            有些函数的参数数量是不确定的，声明函数的时候，可以使用省略号 `...` 表示可变数量的参数。比如 printf 函数。
            注意，`...`符号必须放在参数序列的结尾，否则会报错。
            可参考：[函数如何接收不定数量的参数](https://xhsgg12302.github.io/archive/hugo/corner/assmebly/book/example/#研究试验5-函数如何接收不定数量的参数)

            头文件 stdarg.h 定义了一些宏，可以操作可变参数。
            （1）va_list：  一个数据类型，用来定义一个可变参数对象。它必须在操作可变参数时，首先使用。
            （2）va_start： 一个函数，用来初始化可变参数对象。它接受两个参数，第一个参数是可变参数对象，第二个参数是原始函数里面，可变参数之前的那个参数，用来为可变参数定位。
            （3）va_arg：   一个函数，用来取出当前那个可变参数，每次调用后，内部指针就会指向下一个可变参数。它接受两个参数，第一个是可变参数对象，第二个是当前可变参数的类型。
            （4）va_end：   一个函数，用来清理可变参数对象。

            大概原理就是，在调用函数之前，就会在栈上准备好需要的参数[所有参数由低到高平铺在栈上]，然后根据类型一个一个往后取。
     */
        printf("\n======================== Variable parameters ========================\n");
        printf("average value is: %.3lf\n", average(4, 2, 28, 37, 56));


    printf("\n\033[1;31;42mCongratulations! you have learned the function of C language!\033[0m\n");
    //exit(EXIT_FAILURE);             // 可以通过`echo $?` 获取返回值
    return 0;
}

double average(int i, ...) {
    int total = 0;
    va_list ap;
    va_start(ap, i);
    for (int j = 1; j <= i; ++j) {
        int temp = va_arg(ap, int);
        total += temp;
    }
    va_end(ap);
    return (double)total / i;
}

void counter(void){
    static int count = 1;   // 只初始化一次
    printf("%d\n", count);
    count++;
}

void do_stuff(void){
    printf("called before exit()!\n");
}