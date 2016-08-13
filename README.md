##  **模仿bash_shell实现shell应有的各种功能**
###  1.0 version
1. 完成shell输入提示符
2. 完成基本的内存分配与释放
3. 完成每条命令词的划分

------

### 1.1 version

1. 实现了cd pwd exit 命令
2. 通过函数数组实现命令选择

------

### 1.2 version

1. 实现了env echo export三个命令
2. 通过创建新进程  调用execvp函数 执行其他指令(系统中所有指令)


------

------


### 2.0 version

1. 通过文件重定向dup2实现了三个重定向符号 <(输入重定向), >(输出重定向), >>(附加重定向)
2. 实现了进程组的各种功能   实现了后台运行符号& 
