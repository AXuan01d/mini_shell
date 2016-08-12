##  **模仿bash_shell实现基本的shell功能**
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
