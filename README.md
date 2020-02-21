# C51_Linux

Linux下C51单片机开发

windows下单片机开发有keil工具链，而且代码实例很多。

但是Linux下使用sdcc编译器搭配codeblocks开发而且代码与Windows下不同。

C51部分代码与知乎专栏、微信公众号文章同步

知乎专栏：<a href="https://zhuanlan.zhihu.com/c_1183488323446931456">专栏</a>

## 准备

Linux使用的是SDCC编译器

![avater](./img/sdcc.png)

使用Codeblocks开发工具

![avater](./img/codeblocks.png)

***在开发熟练之后，会考虑移植到Qt下开发***

烧录工具使用stcflash.py(https://github.com/laborer/stcflash) + python-serial

硬件是普中单片机开发版V3.0和V2.0以及其他的一些扩展。

本仓库代码有部分来自普中单片机开发版配套光盘，我将其转换为Linux下。

系统环境：linux mint 18.3 xfce 64bit（基于ubuntu16.04.01）

## linux配置stm32开发环境概述

在linux系统下基于codeblocks和SDCC，使用codeblocks可以自动生成hex文件，而不用再安装其他软件来转换格式，烧写程序到51单片机使用stcflash，使用python，需要安装serial串口模块。

关于USB转串口驱动问题 ，在linux下已经集成好了CH340和PL2302的驱动（linux mint（ubuntu16.04）是这样，其他发行版不清楚），一连接电脑在/dev/下面就会自动有/dev/ttyUSB0，表示有一个串口设备连接了电脑。

### codeblocks

　　Manjaro Linux源里面包含codeblocks最新版的软件包，直接安装就可以了。其他linux发行版也是能在官网找到安装包的，具体安装就不赘述了，相信在linux玩51的已经有这些基础的了。

## SDCC

Manjaro Linux源里面包含SDCC最新版的软件包，直接安装。

运行

```bash
sdcc -v
```

查看sdcc是否正确安装，正确安装执行上述代码会返回版本号

![avater](./img/sdcc_version.png)

### 编译

```C
sdcc main.c
```

这样的话预编译，汇编，链接全部都做了，直接生成ihx文件。

### 转换ihx文件为hex

```bash
#转换成hex文件
packihx main.ihx > main.hex
#也可以转成bin文件
objcopy -I ihex -O binary main.hex mian.bin
#or （makebin是sdcc的一个工具，应该默认装的了）
makebin main.hex main.bin
```

将生成的可执行程序烧录到单片机是需要一条下载线的。一般说来使用 USB 转串口的下载线。插上之后，在 /dev 里面有个设备叫 ttyUSB* 说明可以进行后面内容。

否则你可能需要安装 USB 转串口的驱动。

选择烧录工具。网上大部分使用的是 gSTCISP 这个工具烧录。但是在我尝试之后，总是卡在 We are trying to connect your MCU...这个地方。

起初我还以为下载线出现问题了。后来发现不是。你可以尝试。注意 gSTCISP 需要的是二进制文件，因此需要把 main.ihx 转换为二进制文件。

```bash
makebin <main.ihx> main.bin

然后检查USB连接：
　　a.  $  lsmod | grep usbserial
　　　　如果输出有 usbserial，说明
系统支持USB转串口。
　　b. 用USB数据线将开发板与电脑
连接起来，运行


　$ ls /dev/ttyUSB*
　　　　如果输出有/dev/ttyUSB0或1
等等，说明系统已正确识别该USB转串
口设备。
　　　　也可以用“#lsusb”命令查看是
否有“USB-Serial adapter”类似的设
备。
　　c. 设置串口为ttyUSB0（可以不
做，在下载时手动指定--port）:
　　　　$ dmesg | grep ttyUSB0
　　d. 关闭开发板电源，运行
stcflash.py烧写程序，当出现如下字样
时，打开开发板电源，即开始下载：

## stcflash

使用的时候要把stcflash.py这个文件复制到hex文件同目录下，假设需要烧写的文件是test.hex ，那么在终端进入到test.hex 目录下，执行下面语句

```bash
　　python stcflash.py test.hex
```

以我自己的一个工程为例，需要烧写的文件为sonar.hex ，此时会有如下图所示

![avater](./img/connecting.png)

此时要关闭51单片机电源然后重启，就像在win系统下一样，然后会看到以下情况：

![avater](./img/connected.png)

有晶振频率，芯片型号，ROM大小等信息。

关于codeblocks建立MCS51工程的教程建议参考篇首提供的链接，这里就不再叙述了。

## 参考资料
