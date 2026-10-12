
#include <stdio.h>

/**
 * 
 * @see https://wangdoc.com/clang/enum
 *
 */
int main(void){


    /**
        Enum 类型

            如果一种数据类型的取值只有少数几种可能，并且每种取值都有自己的含义，为了提高代码的可读性，可以将它们定义为 Enum 类型，中文名为枚举。

            注意，Enum 内部的常量名，遵守标识符的命名规范，但是通常都使用大写。

     */
        printf("========================   Enum type   ========================\n");

        // 示例中，假定程序里面需要三种颜色，就可以使用 enum 关键字，把这三种颜色定义成一种枚举类型 colors，
        // 它只有三种取值可能 RED、GREEN、BLUE。这时，这三个名字自动成为整数常量，编译器默认将它们的值设为数字 0、1、2。
        // 相比之下，RED 要比 0 的可读性好了许多。
        enum colors {RED, GREEN, BLUE};
        printf("%d\n", RED);        // 0
        printf("%d\n", GREEN);      // 1
        printf("%d\n", BLUE);       // 2

        // 使用时，可以将变量声明为 Enum 类型。
        // 将变量 color 声明为`enum colors`类型。这个变量的值就是常量 RED、GREEN、BLUE 之中的一个。
        enum colors color = BLUE;

        // typedef 命令可以为 Enum 类型起别名。
        typedef enum {
            SHEEP,
            WHEAT,
            WOOD,
            BRICK,
            ORE
        } RESOURCE;
        RESOURCE r = BRICK;

        // 还有一种不常见的写法，就是声明 Enum 类型时，在同一行里面为变量赋值。
        enum {
            SHEEP_,
            WHEAT_,
            WOOD_,
            BRICK_,
            ORE_
        } t = BRICK, s = 0;

        // 由于 Enum 的属性会自动声明为常量，所以有时候使用 Enum 的目的，不是为了自定义一种数据类型，而是为了声明一组常量。这时就可以使用下面这种写法，比较简单。
        // 常量之间使用逗号分隔。最后一个常量后面的尾逗号，可以省略，也可以保留。
        enum { ONE, TWO, };
        printf("%d %d", ONE, TWO);      // 0 1

        // 由于Enum 会自动编号，因此可以不必为常量赋值。C 语言会自动从 0 开始递增，为常量赋值。
        // 同样，C 语言也允许为 ENUM 常量指定值（可以不连续，甚至可以是同一个值），不过只能指定为整数，不能是其他类型。因此，任何可以使用整数的场合，都可以使用 Enum 常量。
        enum { X = 2, Y = 18, Z = -2 };

        // 如果一组常量之中，有些指定了值，有些没有指定。那么，没有指定值的常量会从上一个指定了值的常量，开始自动递增赋值。
        enum {
            A,      // 0
            B,      // 1
            C = 4,  // 4
            D,      // 5
            E,      // 6
            F = 3,  // 3
            G,      // 4
            H       // 5
        };
        
    
    printf("\n\033[1;31;42mCongratulations! you have learned the enum of C language!\033[0m\n");
    return 0;
}