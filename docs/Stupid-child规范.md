# 规范

为了统一代码风格，在此做一些基本的代码规范

## commit mssage（git提交规范）

```
<type>(<scope>):<subject>
```

<type>（必须）

- feat：新功能，添加一个新功能并且测试过。
- fix/to: 修复bug，可以是测试发现的BUG，也可以是自己研发的时候发现的BUG。
  - fix: 已经找到bug并且解决。
  - to：找到bug未解决，解决完成之后需要fix。
- docs：文档，编写一个驱动、一个功能、一个协议需要编写技术文档，方便他人的理解。
- style：格式，修改代码格式（不影响代码的运行）。
- refactor：重构，对之前的代码进行重构，既不是添加新功能也不是修改bug。
- perf：优化，性能的提升、体验的提升。
- test：增加测试模块，如demo
- chore：构建工具改变，如bat文件
- revert：回滚到上一个版本
- merge：代码合并
- sync：同步主线或分支的bug

<scopde>(可选)

用于说明commit的影响范围，暂时不需要。

<subject>(使用中文)

- 结尾不需要添加句号、小数点

```
fix:1.修复xxxx产生的bug 2.添加buffer的边界检测
docs：1. 添加xxxx模块的技术文档
perf：优化xxx的性能，优化flash的均衡写入
```

## code（代码规范）

### 宏、结构体名、枚举名

- 宏定义、结构体名、枚举名必须大写。

```
typdef struct {
	uint8_t num1:1,
			num2:1,
			num3;
}STRUCT_NAME;

#define DEINE_NAME		(3)
```

- 宏定义数字，必须添加（）`#define NUM   (3)`
- 宏定义函数必须使用do while（0）

### 变量命名

- 变量命名不能使用中文谐音，应该通俗易懂，如 duty、log、info
- 变量命名采用下划线如：table_info、start_flag
- 变量名必须使用小写
- 减少全局变量的使用，尽可能通过静态变量提供接口获取变量

### 函数命名

- 函数命名尽量采用动词+名词，名词与名词之间采用下划线隔开 如：download_file、get_duty、read_file_name
- 函数名使用小写、避免使用驼峰命名法



