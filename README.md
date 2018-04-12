
# fib1

### 说明：
* 在主函数调用 ZF_LOG::log_init("E:\\log.txt"); 启动log模块
* setfmt， ZF_LOGWI 用在需要打印日志的函数内部；其中 setfmt用于设定格式 ZF_LOGWI用于打印
* write_to_file 用于将内存中的数据以16进制的方式写入文件

### 接口：
* void log_init(char* file_name); 参数为打印log的文件名

* void setfmt(int count, ...); 首参数为参数个数（不包括自己）， 其余参数为调用它的方法的参数类型名，以字符串形式传递；eg: ZF_LOG::setfmt(4, "bool", "uint32", "char", "char");

* void write_to_file(char* src, size_t buflen, const char* filename); src为打印内存的首地址， buflen为需要打印的长度， filename为文件名;

* ZF_LOGWI 宏定义， 首参数为 ZF_LOG::state 不变， 其他参数依次为调用它的方法的参数(user_defined_type需要按定义顺序展开);
#### example:
```
#include "iostream"
#include "logapi.h"
#include "datatype.h"
float foo(float a, char b, const S_Temp& pp)
{
	ZF_LOG::setfmt(3, "float", "char", "S_Temp");
	const char data[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
	return (a + b);
}
const int fafa(bool flag, uint32_t integer, char p, char d)
{
	ZF_LOG::setfmt(4, "bool", "uint32", "char", "char");
	ZF_LOGWI(ZF_LOG::state, flag, integer, p, d);
	char* ps = "hello world";
	ZF_LOG::write_to_file(ps, 12, __FUNCTION__);
	ZF_LOG::setfmt(1, "int");
	ZF_LOGWI(ZF_LOG::state, 10);
	return 10;
}
int main()
{
    ZF_LOG::log_init("E:\\log.txt");
    fafa(false, 1000, 'c', 'm');
    return 0;
}
```
