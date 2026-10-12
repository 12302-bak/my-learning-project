
#include <stdio.h>

/**
 * 
 * @see https://wangdoc.com/clang/union
 *
 */
int main(void){


    /**
        Union 结构

            有时需要一种数据结构，不同的场合表示不同的数据类型。比如，如果只用一种数据结构表示水果的“量”，这种结构就需要有时是整数（6 个苹果），有时是浮点数（1.5 公斤草莓）。
            
            C 语言提供了 Union 结构，用来自定义可以灵活变更的数据结构。
            它内部包含各种属性，但是所有属性共用一块内存，导致这些属性都是对同一个二进制数据的解读，其中往往只有一个属性的解读是有意义的。
            并且，后面写入的属性会覆盖前面的属性，这意味着同一块内存，可以先供某一个属性使用，然后再供另一个属性使用。这样做的最大好处是节省内存空间。

     */
        printf("========================   Union structure   ========================\n");

        // 示例中，union 命令定义了一个包含三个属性的数据类型 quantity。
        // 虽然包含三个属性，但是只能写入一个值，三个属性都是对这个值的不同解读。
        // 最后赋值的属性，往往就是可以取到有意义的值的那个属性。当然其他属性也可以拿到值，只不过属于 UB，结果未可知。
        union quantity {
            short count;
            float weight;
            float volume;
        };

        // 使用时，声明一个该类型的变量。
        // 写法一
        union quantity q10;
        q10.count = 4;

        // 写法二
        union quantity q20 = {.count=4};

        // 写法三，不指定属性名，就会赋值给第一个属性 count。
        union quantity q30 = {4};

        // 执行完上面的代码以后，q.count可以正常取到值，另外两个属性没有意义。
        printf("count is %i\n",  q30.count);        // count is 4
        printf("weight is %f\n", q30.weight);       // weight is 0.000000   [未定义行为 UB]

        // 如果要让 q30.weight 属性可以取到值，就要先为它赋值。
        // 一旦为其他属性赋值，原先可以取到值的 q30.count 属性就跟着改变，使用它可能就没有意义了。除了这一点，Union 结构的其他用法与 Struct 结构，基本上是一致的。
        q30.weight = 0.5;
        printf("weight is %.2f\n", q30.weight);     // weight is 0.50


        // 占用空间，union 的对齐 = 所有成员对齐要求的最大值。
        printf("union quantity use space size is: %lu\n", sizeof(union quantity));      // union quantity use space size is: 4
        union V {
            char buf[7];
            char i;
        };
        printf("union V use space size is: %lu\n", sizeof(union V));                    // union V use space size is: 7
        union E {
            char buf[10];
            int  i;
        };
        printf("union E use space size is: %lu\n", sizeof(union E));                    // union E use space size is: 12


        // Union 结构也支持指针运算符`->`。
        union quantity* ptr;
        ptr = &q30;
        printf("weight is %.3f\n", ptr->weight);     // weight is 0.500

        // typedef 命令可以为 Union 数据类型起别名。
        typedef union {
            short count;
            float weight;
            float volume;
        } UNION;
        UNION u = {.count=4};
        
    
    printf("\n\033[1;31;42mCongratulations! you have learned the union of C language!\033[0m\n");
    return 0;
}