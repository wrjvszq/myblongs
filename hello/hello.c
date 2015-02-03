#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");

static int hello_init(void)
{
	printk("<0> hello world\n");
	return 0;
}

static void hello_exit(void)
{
    printk("<0> goodbye\n");

}

	module_init(hello_init);//该宏在模块的目标代码中增加一个特殊的段，用于说明内核初始化函数所在的位置
	module_exit(hello_exit);//跟上面的宏对立
