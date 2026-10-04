
#include <stdio.h>
#include <string.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))

int sum_array(int a[][4], int n);

/**
 * @see https://wangdoc.com/clang/array
 * 
 */
int main(void){

    /**
        1. 简介

            数组是一组相同类型的值，按照顺序储存在一起。数组通过变量名后加方括号表示，方括号里面是数组的成员数量。
                int scores[100];
                示例声明了一个数组 scores，里面包含 100 个成员，每个成员都是 int 类型。即使没有初始化，里面也会有乱七八糟的值。
                数组名后面使用方括号指定下标，就可以引用该成员。也可以通过该方式，对该位置进行赋值。
            
                注意：
                    声明数组时，必须给出数组的大小。
                    数组的成员从 0 开始编号，所以数组 scores[100] 就是从第 0 号成员一直到第 99 号成员，最后一个成员的编号会比数组长度小 1。
                    如果引用不存在的数组成员（即越界访问数组），并不会编译运行报错，所以必须非常小心。

            初始化：
                数组也可以在声明时，使用大括号，同时对每一个成员赋值。
                注意：
                    使用大括号赋值时，必须在数组声明时赋值，否则编译时会报错。 int a[5]; a = {22, 37, 3490, 18, 95}; // 报错 ❌
                    报错的原因是，C 语言规定，数组变量一旦声明，就不得修改变量指向的地址，具体会在后文解释。由于同样的原因，数组赋值之后，再用大括号修改值，也是不允许的。
                    
                    如果大括号里面的值，少于数组的成员数量，那么未赋值的成员自动初始化为 0。
                    int a[5] = {22, 37, 3490};
                    // 等同于
                    int a[5] = {22, 37, 3490, 0, 0};

                    如果要将整个数组的每一个成员都设置为零，最简单的写法就是下面这样。
                    int a[5] = {};                                      // 一旦使用 {}，就会将里面的值置为 0。

                    数组初始化时，可以指定为哪些位置的成员赋值。
                    int a[15] = {[2] = 29, [9] = 7, [14] = 48};         // 示例中，数组的 2 号、9 号、14 号位置被赋值，其他位置的值都自动设为 0。
                    
                    指定位置的赋值可以不按照顺序，下面的写法与上面的例子是等价的。
                    int a[15] = {[9] = 7, [14] = 48, [2] = 29};

                    指定位置的赋值与顺序赋值，可以结合使用。
                    int a[15] = {1, [5] = 10, 11, [10] = 20, 21}        // 示例中，0 号、5 号、6 号、10 号、11 号被赋值。

                    C 语言允许省略方括号里面的数组成员数量，这时将根据大括号里面的值的数量，自动确定数组的长度。
                    int a[3] = {22, 37, 3490};
                    // 等同于
                    int a[]  = {22, 37, 3490};

                    省略成员数量时，如果同时采用指定位置的赋值，那么数组长度将是最大的指定位置再加 1。
                    int a[] = {[2] = 6, [9] = 12};                      // 示例中，数组 a 的最大指定位置是 9，所以数组的长度是 10。
            
     */
        printf("========================   Intro   ========================\n");
        int scores[10];
        scores[0]  = 13;
        scores[9]  = 42;
        // for (int i = 0; i < 10; i++) { printf("%d ", scores[i]); } printf("\n");     // 2nd function call argument is an uninitialized value

        int a[5] = {22, 37, 3490, 18, 95};
        for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++) { printf("%d ", a[i]); } printf("\n");

        int b[15] = {1, [5] = 10, 11, [10] = 20, 21};
        for (size_t i = 0; i < sizeof(b) / sizeof(b[0]); i++) { printf("%d ", b[i]); } printf("\n");

    /**
        2. 数组长度

            它里面没有 length 之类的东西，可以利用 sizeof 运算符会返回整个数组的字节长度，然后除每个数据占用的字节，就可以得到元素个数了。
            形如：`sizeof(a) / sizeof(a[0])`

            注意，sizeof 返回值的数据类型是 size_t，所以`sizeof(a) / sizeof(a[0])`的数据类型也是 size_t。在 printf() 里面的占位符，要用 %zd 或 %zu。
            
     */
        printf("\n========================   Array Length   ========================\n");
        int c[] = {[2] = 6, [9] = 12};
        for (size_t i = 0; i < sizeof(c) / sizeof(c[0]); i++) { printf("%d ", c[i]); } printf("\n");

    /**
        3. 多维数组

            C 语言允许声明多个维度的数组，有多少个维度，就用多少个方括号，比如二维数组就使用两个方括号。
                int board[10][10];      // 示例声明了一个二维数组，第一个维度有 10 个成员，第二个维度也有 10 个成员。
            
            多维数组可以理解成，上层维度的每个成员本身就是一个数组。比如上例中，第一个维度的每个成员本身就是一个有 10 个成员的数组，因此整个二维数组共有 100 个成员（10 x 10 = 100）。
            三维数组就使用三个方括号声明，以此类推。
                int c[4][5][6];
            跟一维数组一样，多维数组每个维度的第一个成员也是从0开始编号。
               
            引用二维数组的每个成员时，需要使用两个方括号，同时指定两个维度。
                board[0][0] = 13;
                board[9][9] = 13;
                注意，board[0][0] 不能写成 board[0, 0]，因为 0, 0 是一个逗号表达式，返回第二个值，所以 board[0, 0] 等同于 board[0]。

            多维数组也可以使用大括号，一次性对所有成员赋值。

            多维数组也可以指定位置，进行初始化赋值。

            不管数组有多少维度，在内存里面都是线性存储，a[0][0] 的后面是 a[0][1]，a[0][1] 的后面是 a[1][0]，以此类推。
            因此，多维数组也可以使用单层大括号赋值，int a[2][2] = {1, 0, 0, 2};
            
     */
        printf("\n========================   Multidimensional Array   ========================\n");
        int d[2][5] = {
            {0, 1, 2, 3, 4},
            {5, 6, 7, 8, 9}
        };
        for (size_t i = 0; i < 2; i++){ for (size_t j = 0; j < 5; j++){ printf("%d ", d[i][j]); } printf("\n"); }; printf("\n"); 

        int e[2][2] = {[0][0] = 1, [1][1] = 2};
        for (size_t i = 0; i < 2; i++){ for (size_t j = 0; j < 2; j++){ printf("%d ", e[i][j]); } printf("\n"); }; printf("\n"); 
        
        int f[2][2] = {1, 0, 0, 2};
        for (size_t i = 0; i < 2; i++){ for (size_t j = 0; j < 2; j++){ printf("%d ", f[i][j]); } printf("\n"); }; printf("\n"); 

    /**
        4. 变长数组

            数组声明的时候，数组长度除了使用常量，也可以使用变量。这叫做变长数组（variable-length array，简称 VLA）。
                int n = x + y;
                int arr[n];
                示例中，数组 arr 就是变长数组，因为它的长度取决于变量 n 的值，编译器没法事先确定，只有运行时才能知道 n 是多少。

            变长数组的根本特征，就是数组长度只有运行时才能确定。它的好处是程序员不必在开发时，随意为数组指定一个估计的长度，程序可以在运行时为数组分配精确的长度。

            任何长度需要运行时才能确定的数组，都是变长数组。
            
     */
        printf("\n========================   Variable-length Array   ========================\n");
        int i = 10,k = 3;
        // 下面三个数组的长度都需要运行代码才能知道，编译器并不知道它们的长度，所以它们都是变长数组。
        int a1[i];
        int a2[i + 5];
        int a3[i + k];

        // 变长数组也可以用于多维数组。
        int m = 4, n = 5;
        int a4[m][n];

    /**
        5. 数组的地址


            在大多数表达式里，数组名会自动转换成"指向数组首元素的指针"。也就是 a == &a[0]
                int arr[10];
                arr                     // 类型从 int[10] 变成 int*

                所以如果在退化后，就获取不到长度信息了。
                比如通过函数传参，使用 sizeof()，就只能被当指针对待，获取的也就是指针的 size 了，所以函数参数里面还得传入元素个数。
                而在没有退化之前，使用 sizeof(), 是可以获取到整个数组占用的长度的。

            &arr 需要注意：
                int arr[10];
                int *p1 = arr;          // arr 退化为 int*，指向首元素
                int (*p2)[10] = &arr;   // &arr 不退化，类型是 int(*)[10]，指向整个数组

                arr[3]                  // 合法；arr 退化为 int*，
                p1 [3]                  // 合法；p1 本来就是 int*
                3 [p1]                  // 合法；==> *(3 + p1)，参考：https://en.cppreference.com/c/language/operator_member_access


            By definition, the subscript operator E1[E2] is exactly identical to *((E1)+(E2))
            C 语言里数组下标运算符 [] 根本不是为数组设计的，它是为指针设计的。数组能用 []，是因为数组退化成了指针。指针才是 [] 的正主。

           
            int brr[4][2] = {0};
            *(brr[0]) = brr[0][0]
            **brr     = brr[0][0]       ❓

     */
        printf("\n========================   The address of the Array   ========================\n");
        // 对于一维数组来说，它的标识符表示，第一个元素 arr[0]，取址类型是 int (*p12)
        int arr[10];
        int *p1       = arr;
        int (*p2)[10] = &arr;

        int p11       = arr[1];     // arr[1] 的类型是 int.
        int (*p12)    = &arr[1];

        printf("arr size:%zu\t, &arr size:%zu\n", sizeof(*p1), sizeof(*p2));
        printf("arr size:%zu\t, &arr size:%zu\n", sizeof(arr[0]), sizeof(*&arr));

        // 对于二维数组来说，它的标识符表示，第一个元素 brr[0]，取址类型是 int (*ptr)[2]
        int brr[4][2] = {};
        int (*ptr)[2] = brr;
        int (*ptz)[4][2] = &brr;

        int* crr      = brr[1];     // brr[1] 的类型是 int[2]（第二行这个数组），但在表达式里它退化为 int*，指向 brr[1][0]。
        int (*ptc)[2] = &brr[1];

        printf("brr[4][2] first's type is int (*ptr)[2], and size is:%zu\n", sizeof(*ptr));

        printf("other a expression is: integer-expression [ pointer-expression ], %d\n", 2[c]);     // 6

    /**
        6. 数组指针的加减法

            C 语言里面，数组名可以进行加法和减法运算，等同于在数组成员之间前后移动，即从一个成员的内存地址移动到另一个成员的内存地址。
            比如，a + 1 返回下一个成员的地址，a - 1 返回上一个成员的地址。
            a + i 的每轮循环每次都会指向下一个成员的地址，*(a + i) 取出该地址的值，等同于 a[i]。对于数组的第一个成员，*(a + 0)（即 *a ）等同于 a[0]。

            如果指针变量 p 指向数组的一个成员，那么 p++ 就相当于指向下一个成员，这种方法常用来遍历数组。比如 p_a。

            反过来，通过数组的减法，可以知道两个地址之间有多少个数组成员
            
     */
        printf("\n========================   Array pointer addition and subtraction operations   ========================\n");
        int apaaso[]  = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int* p_a = apaaso;         // 注意，数组名指向的地址是不能变的
        for ( ; *p_a != 9; p_a++){ printf("%d ", *p_a); } printf("\n");

        // 遍历数组一般都是通过数组长度的比较来实现，但也可以通过数组起始地址和结束地址的比较来实现。
        p_a = apaaso;
        for ( ; p_a <= apaaso + 8; p_a++){ printf("%d ", *p_a); } printf("\n");

        p_a = apaaso;
        for ( ; *p_a != 9; p_a++){ } printf("array's length == %td\n", ++p_a - apaaso);

    /**
        7. 数组的复制

            由于数组名是指针，所以复制数组不能简单地复制数组名。
            正确的是单个循环，或者使用 memcpy。
     */
        printf("\n========================   Array copy   ========================\n");
        int* a7 = NULL;
        int b7[3] = {1, 2, 3};

        a7 = b7;            // 结果不是将数组 b7 复制给数组 a7，而是让 a7 和 b7 指向同一个数组。
        printf("%d\n", *a7);

        for (size_t i = 0; i < ARRAY_LEN(b7); i++){
            a7[i] = b7[i];  // 由于 a7 和 b7 地址一样，所以相当于把 b7 里面的数值取出来又放进去。新建一个数组，赋值给 a7 即可。
        } printf("\n");

        int c7[ARRAY_LEN(b7)] = {};
        memcpy(c7, b7, sizeof(b7));
        for (size_t i = 0; i < ARRAY_LEN(c7); i++) { printf("%d ", c7[i]); } printf("\n");
        
    /**
        8. 作为函数的参数

            1. 声明参数数组

                数组作为函数的参数，一般会同时传入数组名和数组长度。

                如果函数的参数是多维数组，那么除了第一维的长度可以当作参数传入函数，其他维的长度需要写入函数的定义。
                int sum_array(int a[][4], int n) { }
                int a[2][4] = { };
                int sum = sum_array(a, 2);
                如果不写，则编译器不知道一维有多少个元素，编译不通过。a 是 int(*)[?]，a + 1 要跳过一整行。一整行多大？

            2. 变长数组作为参数

                变长数组作为函数参数时，写法略有不同。
                int sum_array(int n, int a[n]) { }
                int a[] = {3, 5, 7, 3};
                int sum = sum_array(4, a);
                数组 a[n] 是一个变长数组，它的长度取决于变量 n 的值，只有运行时才能知道。
                所以，变量 n 作为参数时，顺序一定要在变长数组前面，这样运行时才能确定数组 a[n] 的长度，否则就会报错。

                因为函数原型可以省略参数名，所以变长数组的原型中，可以使用 * 代替变量名，也可以省略变量名。
                int sum_array(int, int [*]);
                int sum_array(int, int []);

                变长数组作为函数参数有一个好处，就是多维数组的参数声明，可以把后面的维度省掉了。c99
                // 原来的写法
                int sum_array(int a[][4], int n);
                // 变长数组的写法
                int sum_array(int n, int m, int a[n][m]);

            3. 数组字面量作为参数

                C 语言允许将数组字面量作为参数，传入函数。
                // 数组变量作为参数
                int a[] = {2, 3, 4, 5};
                int sum = sum_array(a, 4);

                // 数组字面量作为参数
                int sum = sum_array((int []){2, 3, 4, 5}, 4);
            
     */
        printf("\n========================   As a parameter of a function   ========================\n");
        int a8[2][4] = {
            {1, 2, 3, 4},
            {8, 9, 10, 11}
        };
        printf("sum_array normal  output is: %d\n", sum_array(a8, 2));                          // 48

        printf("sum_array literal output is: %d\n", sum_array((int [][4]){2, 3, 4, 5}, 1));     // 14

    printf("\n\033[1;31;42mCongratulations! you have learned the array of C language!\033[0m\n");
    return 0;
}

// int sum_array(int (*a)[4], int n);
// int sum_array(int a[2][4], int n);
int sum_array(int a[][4], int n) {
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < 4; j++){
            sum += a[i][j];
        }
    }
    return sum;
}