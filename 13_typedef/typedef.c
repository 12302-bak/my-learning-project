
#include <stdio.h>

/**
 * 
 * @see https://wangdoc.com/clang/typedef
 *
 */
int main(void){


    /**
        1. 简介

            typedef 命令用来为某个类型起别名。
            
                // type 代表类型名，alias 代表别名。
                typedef type alias;

            typedef 可以一次指定多个别名。
            typedef int antelope, bagel, mushroom;
                

     */
        printf("========================   Intro   ========================\n");

        // 示例中，typedef 命令为类型 `unsign char` 起别名 BYTE，然后就可以使用 BYTE 声明变量。
        typedef unsigned char BYTE;
        BYTE c = 'z';

        // typedef 可以为指针起别名。
        // 使用的时候要小心，这样不容易看出来，变量 x 是一个指针类型。
        typedef int* intptr;
        int a = 10;
        intptr x10 = &a;

        // typedef 也可以用来为数组类型起别名。
        typedef int five_ints[5];
        five_ints x11 = {11, 22, 33, 44, 55};

        // typedef 为函数起别名的写法如下。
        // 示例中，类型别名 fp 是一个指针，代表函数 signed char (*)(void)。
        typedef signed char (*fp)(void);

                void (*common_ptr01)(char *, int) = (void *)0x7ffff7e03100;
        typedef void (*Func        )(char *, int);
                Func common_ptr02                 = (void *)0x7ffff7e03100;
        common_ptr01("hello variable\n", 100);
        common_ptr02("hello type\n", 100);

    /**
        2. 主要好处

            typedef为类型起别名的好处，主要有下面几点。

                （1）更好的代码可读性。
                    // 示例为字符指针起别名为 STRING，以后使用 STRING 声明变量时，就可以轻易辨别该变量是字符串。
                    typedef char* STRING;
                    STRING name;

                （2）为 struct、union、enum 等命令定义的复杂数据结构创建别名，从而便于引用。
                    // 示例中，Tree 为`struct treenode*`的别名。
                    struct treenode {
                        // ...
                    };
                    typedef struct treenode* Tree;
                
                （3）typedef 方便以后为变量改类型。
                    // 示例中，变量 f1、f2、f3 的类型都是 float。如果以后需要为它们改类型，只需要修改 typedef 语句即可。
                    typedef float app_float;
                    app_float f1, f2, f3;
                    // 下面命令将变量 f1、f2、f3 的类型都改为 long double。
                    typedef long double app_float;

                （4）可移植性
                    // 某一个值在不同计算机上的类型，可能是不一样的。

                    int i = 100000;
                    上面代码在32位整数的计算机没有问题，但是在16位整数的计算机就会出错。

                    C 语言的解决办法，就是提供了类型别名，在不同计算机上会解释成不同类型，比如 int32_t。
                    // 示例将变量 i 声明成 int32_t 类型，保证它在不同计算机上都是 32 位宽度，移植代码时就不会出错。
                    int32_t i = 100000;
                    对于这些整数类型别名都放在头文件stdint.h，不同架构的计算机只需修改这个头文件即可，而无需修改代码。

                （5）简化类型声明
                    // C 语言有些类型声明相当复杂，比如下面这个。
                    char (*(*x(void))[5])(void);
                    typedef 可以简化复杂的类型声明，使其更容易理解。首先，最外面一层起一个类型别名。

                    typedef char (*Func)(void);
                    Func (*x(void))[5];

                    // 这个看起来还是有点复杂，就为里面一层也定义一个别名。
                    typedef char (*Func)(void);
                    typedef Func Arr[5];
                    Arr* x(void);

                    上面代码就比较容易解读了。
                    x是一个函数，返回一个指向 Arr 类型的指针。
                    Arr是一个数组，有5个成员，每个成员是Func类型。
                    Func是一个函数指针，指向一个无参数、返回字符值的函数。

     */
        printf("========================   Main benefits   ========================\n");

                char  (* (*x(void))[5] )(void);         // 语句是：函数原型定义
        typedef char  (* Funcc         )(void);
                Funcc (*x(void))[5];                    // 语句是：函数原型定义
        typedef Funcc Arr       [5];
                Arr *x(void);                           // 语句是：函数原型定义

    
    printf("\n\033[1;31;42mCongratulations! you have learned the typedef of C language!\033[0m\n");
    return 0;
}

// char  (* (*x(void))[5] )(void);

int *p = (int *)0x10000;
// f01(void) 的返回类型是指向： int 的指针; 也就是指向一个整数
int *f01(void) { 
    static int temp = 10;
    return &temp; 
}

// 一个包含 10 个 int* 的数组，名叫 arr_ptr
// int* arr_ptr[10] = (int * [10])0x0001;  // 一个是数组不能强转，另一个是语法不允许 
// 函数不能返回数组，所以写法是错误的，得让它返回如下 f02 数组指针,或者 f03 指针成语数组指针
// int* pc(void)[3] { }
// 
// f02(void) 的返回类型是指向： int [3] 的指针; 也就是指向一个 包含 3 个整形的数组。
int (*f02(void))[3]{
    static int temp[3] = {10, 11, 12};
    return &temp;
}

int * (*brr_ptr)[3] = (int *(*)[3])0x00001;
// f03(void) 的返回类型是指向： int * [3] 的指针; 也就是指向一个 包含 3 个整形指针的数组。
int * (*f03(void))[3] {
    static int x = 10, y = 11, z = 12;
    static int *temp[3] = { &x, &y, &z };
    return &temp;
}

char (* (*f04(void))[3] )(void) { return NULL; }
