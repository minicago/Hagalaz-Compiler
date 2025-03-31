# Hagalaz-Compiler

## 安装调试交叉编译器以及QEMU环境

### 交叉编译器 

```bash
#安装
sudo apt-get install gcc-arm-linux-gnueabihf
#运行
arm-linux-gnueabihf-gcc -xc test/functional/00_main.sy -I test -o 00_main
```

我们编译器最终将实现这一部分的功能

### QEMU
```bash
# 这里我们选择使用用户态QEMU
sudo apt install qemu-user-static
# 尝试运行 00_main
qemu-arm-static 00_main
# 发生报错 qemu-arm-static: Could not open '/lib/ld-linux-armhf.so.3': No such file or directory

# 修复方案
ln -s /usr/arm-linux-gnueabihf/lib/ld-linux-armhf.so.3 /lib/ld-linux-armhf.so.3
# 重新运行
qemu-arm-static 00_main 
echo $?
# 3
```

### 数据集获取
```bash
git clone https://gitlab.eduxiji.net/csc1/nscscc/compiler2023.git
# 将其中公开样例与运行时库复制到test目录下
```