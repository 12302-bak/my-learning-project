
#include <stdio.h>

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

            如果一个函数的参数或返回值，也是一个函数，那么函数原型可以写成下面这样。
            int compute(int (*myfunc)(int), int, int);
     */
        printf("========================pointer of function========================\n");
        void (*increment_ptr)(int) = &increment;

        printf("printf's address is: %p\n", &printf);                           // 0x7ffff7e03100
        int (*printf_ptr)(const char *, ...) = (void *)0x7ffff7e03100;          // 固定地址和操作系统 ASLR 有关，所以下面的方式比较稳妥。容器也可参考`"securityOpt": [ "seccomp=unconfined" ]`
        printf_ptr = &printf;                                                   // 重新赋值
        
        // 有了指针，可以通过指针调用 (*printf_ptr)("")
        (*printf_ptr)("called method 01\n");                                    // <==> printf()
        // 比较特殊的是，C 语言中，函数名本身会被编译器衰变为指向函数代码的指针，
        // 也就是说 printf 和 &printf 是一样的。                                   // *printf ==> *&printf ==> printf ==> &printf
        if (printf == &printf) { printf("hello world from pointer!\n");}        // hello world from pointer!

        
    printf("\n\033[1;31;42mCongratulations! you have learned the function of C language!\033[0m\n");
    return 0;
}