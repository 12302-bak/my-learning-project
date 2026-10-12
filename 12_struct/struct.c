
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

struct turtle {
    char* name;
    char* species;
    int age;
};

void happy(struct turtle t) {
    t.age = t.age + 1;
};

void happy_ptr(struct turtle* t) {

    //  (*t).age = (*t).age + 1;
        t->age = t->age + 1;
}

/**
 * 
 * @see https://wangdoc.com/clang/struct
 *
 */
int main(void){


    /**
        1. 简介

            C 语言内置的数据类型，除了最基本的几种原始类型，只有数组属于复合类型，可以同时包含多个值，但是只能包含相同类型的数据，实际使用中并不够用。

            实际使用中，主要有下面两种情况，需要更灵活强大的复合类型。
                复杂的物体需要使用多个变量描述，这些变量都是相关的，最好有某种机制将它们联系起来。
                某些函数需要传入多个参数，如果一个个按照顺序传入，非常麻烦，最好能组合成一个复合结构传入。

            为了解决这些问题，C 语言提供了 struct 关键字，允许自定义复合数据类型，将不同类型的值组合在一起。
            这样不仅为编程提供方便，也有利于增强代码的可读性。C 语言没有其他语言的对象（object）和类（class）的概念，struct 结构很大程度上提供了对象和类的功能。
            比如如下的 `struct fraction` 结构。

            注意，作为一个自定义的数据类型，它的类型名要包括`struct`关键字，比如上例是`struct fraction`，单独的`fraction`没有任何意义，甚至脚本还可以另外定义名为`fraction`的变量，虽然这样很容易造成混淆。
            另外，struct 语句结尾的分号不能省略，否则很容易产生错误。

     */
        printf("========================   Intro   ========================\n");

        // 示例定义了一个分数的数据类型 struct fraction，包含两个属性 numerator 和 denominator。
        struct fraction {
            int numerator;
            int denominator;
        };
        // 定义了新的数据类型以后，就可以声明该类型的变量，这与声明其他类型变量的写法是一样的。
        // 再次声明，必须使用`struct fraction f1`声明变量，不能写成`fraction f1`。
        // 示例中，先声明了一个`struct fraction`类型的变量 f1，这时编译器就会为 f1 分配内存，接着就可以为 f1 的不同属性赋值。
        // 可以看到，struct 结构的属性通过点（.）来表示，比如 numerator 属性要写成 `f1.numerator`。
        struct fraction f1;
        f1.numerator = 22;
        f1.denominator = 7;

        // 除了逐一对属性赋值，也可以使用大括号，一次性对 struct 结构的所有属性赋值。
        // 示例中，变量 saturn 是`struct car`类型，大括号里面同时对它的三个属性赋值。如果大括号里面的值的数量，少于属性的数量，那么缺失的属性自动初始化为 0。
        struct car {
            char* name;
            float price;
            int speed;
        };
        struct car saturn10 = {"Saturn SL/2", 16000.99, 175};
        // 注意，大括号里面的值的顺序，必须与 struct 类型声明时属性的顺序一致。否则，必须为每个值指定属性名。
        struct car saturn11 = {.speed=172, .name="Saturn SL/2"};
        //  saturn11 =              {.speed=172, .name="Saturn SL/2"};          // ❌ expected expression，右边必须写成 (struct car){...}，不能只写 {...}，否则编译器不知道这是什么类型的结构体。
            saturn11 = (struct car) {.speed=172, .name="Saturn SL/2"};          // ✅ 
        saturn11.speed = 168;

        // struct 的数据类型声明语句与变量的声明语句，可以合并为一个语句。                                          struct anonym { ... } var;
        struct book {
            char title[500];
            char author[100];
            float value;
        } b1;
        // 如果类型标识符 book 只用在这一个地方，后面不再用到，这里可以将类型名省略。                                 struct { ... } var;
        struct {
            char title[500];
            char author[100];
            float value;
        } b2;
        // 与其他变量声明语句一样，可以在声明变量的同时，对变量赋值。                                                struct { ... } var = {.. , ..};
        struct {
            char title[500];
            char author[100];
            float value;
        }   b3 = {"Harry Potter", "J. K. Rowling", 10.0},
            b4 = {"Cancer Ward", "Aleksandr Solzhenitsyn", 7.85};
        // 下一章介绍的 typedef 命令可以为 struct 结构指定一个别名，这样使用起来更简洁.                              typedef struct anonym { ... } type_name;      type_name var = ;
        typedef struct cell_phone {
            int cell_no;
            float minutes_of_charge;
        } phone;
        phone p = {5551234, 5};
        // 指针变量也可以指向 struct 结构。                                                                     struct anonym { ... } * ptr、struct anonym { ... }; struct anonym* ptr;
        struct anon01 { char title[500]; char author[100]; float value; }* a01_ptr;
        struct anon02 { char title[500]; char author[100]; float value; };  struct anon02* a02_ptr;
        // struct 结构也可以作为数组成员。
        struct fraction numbers[10];
        numbers[0].numerator = 22;
        numbers[0].denominator = 7;

        // struct 结构占用的存储空间，不是各个属性存储空间的总和，而是最大内存占用属性的存储空间的倍数，其他属性会添加空位与之对齐。这样可以提高读写效率。
        // 为了加快读写速度，把内存占用划分成等长的区块，就可以快速在 Struct 结构体中定位到每个属性的起始地址。
        // 由于这个特性，在有必要的情况下，定义 Struct 结构体时，可以采用存储空间递增的顺序，定义每个属性，这样就能节省一些空间。当然熟悉规则之后完全可以自定义顺序也不会多占用空间。
        // 
        // --------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------
        // 2 byte  +       +///////a///////+/b/_____3______+///////c///////+_______4_______+///////////////d///////////////+///////e///////+/f/_1__+///h///+               |
        // --------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------
        //                 0       2       4       6       8                               16              20              24              28      30      32
        struct foo {
            int  a;
            char b;
            int  c;
            char* d;
            int   e;
            bool  f;
            short h;
        };
        printf("%zu\n", sizeof(struct foo));    // 32
        // 可以用 offsetof 宏查看每个成员的偏移：
        printf("a offset = %zu\n", offsetof(struct foo, a));        // 0
        printf("b offset = %zu\n", offsetof(struct foo, b));        // 4
        printf("c offset = %zu\n", offsetof(struct foo, c));        // 8
        printf("d offset = %zu\n", offsetof(struct foo, d));        // 16
        printf("e offset = %zu\n", offsetof(struct foo, e));        // 24
        printf("f offset = %zu\n", offsetof(struct foo, f));        // 28
        printf("h offset = %zu\n", offsetof(struct foo, h));        // 30

    /**
        2. struct 的复制

            struct 变量可以使用赋值运算符（=），复制给另一个变量，这时会生成一个全新的副本。
            系统会分配一块新的内存空间，大小与原来的变量相同，把每个属性都复制过去，即原样生成了一份数据。这一点跟数组的复制不一样，务必小心。

            对于包含指针的结构体，两个结构体变量有成员指向同一块地址，也需要注意修改的时候。

            注意，这种赋值要求两个变量是同一个类型，不同类型的 struct 变量无法互相赋值。
            
            另外，C 语言没有提供比较两个自定义数据结构是否相等的方法，无法用比较运算符（比如`==`和`!=`）比较两个数据结构是否相等或不等。
     */
        printf("\n========================   struct copy   ========================\n");

        // 示例中，变量 b 是变量 a 的副本，两个变量的值是各自独立的，修改掉 b.name 不影响 a.name。
        // 示例是有前提的，就是 struct 结构的属性必须定义成字符数组，才能复制数据。如果稍作修改，属性定义成字符指针，结果就不一样。 struct cat { char* name; short age; } a, b;
        struct cat { char name[30]; short age; } a, b;
        strcpy(a.name, "Hula");
        a.age = 3;
        b = a;
        b.name[0] = 'M';
        printf("%s\n", a.name);         // Hula
        printf("%s\n", b.name);         // Mula

    /**
        3. struct 指针

            如果将 struct 变量传入函数，函数内部得到的是一个原始值的副本。
            通常情况下，开发者希望传入函数的是同一份数据，函数内部修改数据以后，会反映在函数外部。
            而且，传入的是同一份数据，也有利于提高程序性能。这时就需要将 struct 变量的指针传入函数，通过指针来修改 struct 属性，就可以影响到函数外部。

            struct 指针传入函数的写法如下。
                void happy(struct turtle* t) { }
                happy(&myTurtle);       // struct 类型跟函数、数组不一样，类型标识符本身并不是指针，也不能退化成指针，所以传入时，指针必须写成 `&myTurtle`。

            函数内部也必须使用 (*t).age 的写法，从指针拿到 struct 结构本身。
            void happy(struct turtle* t) {
                (*t).age = (*t).age + 1;
            }
            示例中，(*t).age 不能写成 *t.age，因为点运算符 . 的优先级高于 * 。*t.age 这种写法会将 t.age 看成一个指针，然后取它对应的值，会出现无法预料的结果。

            "*t.age 这种写法会将 t.age 看成一个指针" 这个在语法上是可以这么解释的，因为 * 就是针对指针的操作符。
            但是在明确 t 是结构体指针的情况下会编译错误，因为指针没有`.` 运算符。

            (*t).age 这样的写法很麻烦。C 语言就引入了一个新的箭头运算符（->），可以从 struct 指针上直接获取属性，大大增强了代码的可读性。

            总结一下，
                对于 struct 变量名，使用点运算符（.）获取属性；
                对于 struct 变量指针，使用箭头运算符（->）获取属性。
                以变量 myStruct 为例，假设 ptr 是它的指针，那么下面三种写法是同一回事。
                // ptr == &myStruct
                myStruct.prop == (*ptr).prop == ptr->prop

     */
        printf("\n========================   struct pointer   ========================\n");
        printf("\nmyStruct.prop == (*ptr).prop == ptr->prop\n");

    /**
        4. struct 的嵌套

            struct 结构的成员可以是另一个 struct 结构。

            struct 结构内部不仅可以引用其他结构，还可以自我引用，即结构内部引用当前结构。比如，链表结构的节点就可以写成下面这样。

     */
        printf("\n========================   Nesting of struct  ========================\n");

        // 示例中，fish 的属性 breed 是另一个 struct 结构 species。
        struct species {
            char* name;
            int kinds;
        };
        struct fish {
            char* name;
            int age;
            struct species breed;
        };

        // 赋值的时候有多种写法。
        // 写法一
        struct fish shark40 = { "shark", 9, { "Selachimorpha", 500 }};
        // 写法二
        struct species myBreed = { "Selachimorpha", 500 };
        struct fish shark41 = { "shark", 9, myBreed };
        // 写法三
        struct fish shark42 = {
            .name="shark",
            .age=9,
            .breed={ "Selachimorpha", 500 }
        };
        // 写法四
        struct fish shark43 = {
            .name="shark",
            .age=9,
            .breed.name="Selachimorpha",
            .breed.kinds=500
        };
        printf("Shark's species is %s\n\n", shark43.breed.name);


        // node, 示例中，node 结构的 next 属性，就是指向另一个 node 实例的指针。
        struct node {
            int data;
            struct node* next;
        };
        struct node* head;
        // 生成一个三个节点的列表 (11)->(22)->(33)
        head = malloc(sizeof(struct node));
        head->data = 11;
        head->next = malloc(sizeof(struct node));
        head->next->data = 22;
        head->next->next = malloc(sizeof(struct node));
        head->next->next->data = 33;
        head->next->next->next = NULL;
        // 遍历这个列表
        for (struct node *cur = head; cur != NULL; cur = cur->next) {
            printf("%d\n", cur->data);
        }


    /**
        5. 位字段

            struct 还可以用来定义`二进制位`组成的数据结构，称为“位字段”（bit field），这对于操作底层的二进制数据非常有用。

                // 示例中，每个属性后面的`:1`，表示指定这些属性只占用一个二进制位，所以这个数据结构一共是 4 个二进制位。
                struct {
                    unsigned int ab:1;
                    unsigned int cd:1;
                    unsigned int ef:1;
                    unsigned int gh:1;
                } synth;
                synth.ab = 0;
                synth.cd = 1;
            
            注意，定义二进制位时，结构内部的各个属性只能是整数类型。
            实际存储的时候，C 语言会按照 int 类型占用的字节数，存储一个位字段结构。
            如果有剩余的二进制位，可以使用未命名属性，填满那些位。也可以使用宽度为 0 的属性，表示占满当前字节剩余的二进制位，迫使下一个属性存储在下一个字节。

                // 示例中，stuff.field1 与 stuff.field2 之间，有一个宽度为两个二进制位的未命名属性。stuff.field3 将存储在下一个字节。
                struct {
                    unsigned int field1 : 1;
                    unsigned int        : 2;
                    unsigned int field2 : 1;
                    unsigned int        : 0;
                    unsigned int field3 : 1;
                } stuff;

            注意：
                类型限制：
                    位字段的类型只能是 int、unsigned int、signed int（C99 后还允许 _Bool）。不能是 float、double、数组或指针。

                强烈建议使用 unsigned int：
                    如果你用 int，最高位可能是符号位。比如 int a : 1;，你赋值 1，但打印出来可能是 -1（因为 1 位有符号数补码表示 -1）。这极易引发 Bug。
                    使用 unsigned int 可以避免符号位带来的歧义。

                位数不能超过类型宽度：
                    比如 unsigned int 通常是 32 位，你就不能写 unsigned int a : 33;。
                
                不能取地址（&）:
                    因为位字段可能不是从字节边界开始的，它没有独立的内存地址。
                    struct Flags f;
                    // int *p = &f.is_ready;
                
                内存布局是“实现定义”的（不可移植）:
                    C 标准没有规定位字段在内存中是从左往右排，还是从右往左排。也没有规定跨字节时怎么处理。
                    这意味着：你在这台电脑上用位字段定义好的网络协议包，发到另一台电脑上解析，可能会完全乱套。

                跨字节边界问题:
                    编译器可能会把位字段紧凑排列，也可能会为了对齐而在中间插入“空洞”。
                    struct A {
                        unsigned int a : 3;
                        unsigned int   : 0;     // 匿名位字段，宽度为 0，强制下一个位字段从下一个存储单元（如字节）开始
                        unsigned int b : 5;
                    };
                    unsigned int : 0; 是一个特殊语法，叫做零宽度位字段，它强制让下一个位字段从新的内存单元开始，常用于手动对齐。
                
                不能使用 sizeof 精确计算:
                    sizeof(struct Flags) 的结果可能比你想象的要大。编译器可能会为了内存对齐而填充字节（Padding）。

     */
        printf("\n========================   Bits field   ========================\n");

        struct PackedData {
            unsigned int a : 3;     // [0 ~ 7 ]
            unsigned int b : 5;     // [0 ~ 31]
        };
        struct PackedData data;
        // 1. 赋值
        data.a = 5;
        data.b = 20;
        // 2. 读取
        printf("a = %u, b = %u\n", data.a, data.b);
        // 3. 溢出测试
        volatile int temp = 9;                  // 加上 volatile 防止编译器优化并推导出常量 9
        data.a = temp;                          // 9 的二进制是 1001，但 a 只有 3 位，只能存低 3 位 001，即 1
        printf("溢出后 a = %u\n", data.a);       // 输出 1


    /**
        6. 弹性数组成员

            很多时候，不能事先确定数组到底有多少个成员。如果声明数组的时候，事先给出一个很大的成员数，就会很浪费空间。
            C 语言提供了一个解决方法，叫做弹性数组成员（flexible array member）。

            如果不能事先确定数组成员的数量时，可以定义一个 struct 结构。

            下面示例中，假定 chars 数组的成员数量是 n，只有在运行时才能知道 n 到底是多少。
            然后，就为 struct vstring 分配它需要的内存：它本身占用的内存长度，再加上 n 个数组成员占用的内存长度。最后，len 属性记录一下 n 是多少。
            这样就可以让数组 chars 有 n 个成员，不用事先确定，可以跟运行时的需要保持一致。
            
            弹性数组成员有一些专门的规则。
                首先，弹性成员的数组，必须是 struct 结构的最后一个属性。
                另外，除了弹性数组成员，struct 结构必须至少还有一个其他属性。

     */
        printf("\n========================   Flexible array member   ========================\n");

        // 示例中，struct vstring 结构有两个属性。len 属性用来记录数组 chars 的长度，chars 属性是一个数组，但是没有给出成员数量。
        struct vstring {
            int len;
            char chars[];
        };
        // chars 数组到底有多少个成员，可以在为 vstring 分配内存时确定。
        int n = 30;
        printf("sizeof(struct vstring) is : %lu\n", sizeof( struct vstring));           // 4 
        struct vstring* str = malloc(sizeof(struct vstring) + n * sizeof(char));
        str->len = n;
        printf("sizeof(*str) is : %lu\n", sizeof( *str ));                              // 4 

    
    printf("\n\033[1;31;42mCongratulations! you have learned the struct of C language!\033[0m\n");
    return 0;
}