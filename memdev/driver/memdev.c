/*************************************************************************
	> File Name: /home/wrj/my_linux/kernel_module/myblong/memdev/memdev.c
	> Author: @wrj
	> Mail: wrjvszq@163.com
	> Created Time: Wed 04 Feb 2015 11:09:15 AM CST
 ************************************************************************/

#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<asm/uaccess.h>
#include"memdev.h"

#define MEM_SIZE 1024

MODULE_LICENSE("GPL");

struct mem_dev{
    struct cdev cdev;
    int mem[MEM_SIZE];//全局内存4k
    dev_t devno;
};

struct mem_dev my_dev;

long mem_ioctl(struct file *fd, unsigned int cmd, unsigned long arg){
    switch(cmd){
    case MEM_RESTART:
        printk("<0> memdev is restart");
        break;
    default:
        return -EINVAL;
    }
    return 0;
}

/*打开设备*/
int mem_open(struct inode *inode, struct file *filp){
    int num = MINOR(inode->i_rdev);/*获取次设备号*/

    if(num == 0){/*判断为那个设备*/
        filp -> private_data = my_dev.mem;/*将设备结构体指针复制给文件私有数据指针*/
    }
    return 0;
}
/*文件关闭函数*/
int mem_release(struct inode *inode, struct file *filp){
      return 0;
}

static ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos){
    int * pbase = filp -> private_data;/*获取数据地址*/
    unsigned long p = *ppos;/*读的偏移*/
    unsigned int count = size;/*读数据的大小*/
    int ret = 0;

    if(p >= MEM_SIZE)/*合法性判断*/
        return 0;
    if(count > MEM_SIZE - p)/*读取大小修正*/
        count = MEM_SIZE - p;

    if(copy_to_user(buf,pbase + p,size)){
       ret = - EFAULT;
    }else{
        *ppos += count;
        ret = count;
    }

    return ret;
}

static ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos){
    unsigned long p = *ppos;
    unsigned int count = size;
    int ret = 0;
    int *pbase = filp -> private_data;

    if(p >= MEM_SIZE)
        return 0;
    if(count > MEM_SIZE - p)
        count = MEM_SIZE - p;

    if(copy_from_user(pbase + p,buf,count)){
       ret = - EFAULT;
    }else{
        *ppos += count;
        ret = count;
    }
    return ret;
}

/*seek文件定位函数*/
static loff_t mem_llseek(struct file *filp, loff_t offset, int whence){ 

    loff_t newpos;

    switch(whence) {
        case SEEK_SET:/*从文件头开始定位*/
            newpos = offset;
            break;
        case SEEK_CUR:/*从当前位置开始定位*/ 
            newpos = filp->f_pos + offset;
            break;
        case SEEK_END: 
            newpos = MEM_SIZE * sizeof(int)-1 + offset;/*从文件尾开始定位*/
            break;
        default:
            return -EINVAL;
    }

     if ((newpos<0) || (newpos>MEM_SIZE * sizeof(int)))/*检查文件指针移动后位置是否正确*/
         return -EINVAL;
     
     filp->f_pos = newpos;
     return newpos;

}

const struct file_operations mem_ops = {
    .llseek = mem_llseek,
    .open = mem_open,
    .read = mem_read,
    .write = mem_write,
    .release = mem_release,
    .unlocked_ioctl = mem_ioctl,
};

static int memdev_init(void){
    int ret = -1;

    /*动态分配设备号*/
    ret = alloc_chrdev_region(&my_dev.devno,0,1,"memdev");
    if (ret >= 0){
        cdev_init(&my_dev.cdev,&mem_ops);/*初始化字符设备*/
        cdev_add(&my_dev.cdev,my_dev.devno,1);/*添加字符设备*/
    }

    return ret;   
}

static void memdev_exit(void){
    cdev_del(&my_dev.cdev);
    unregister_chrdev_region(my_dev.devno,1);

}

module_init(memdev_init);
module_exit(memdev_exit);

