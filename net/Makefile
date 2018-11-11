CROSS_COMPILE = /usr/bin/

AS			= $(CROSS_COMPILE)as
LD			= $(CROSS_COMPILE)ld
CC			= $(CROSS_COMPILE)gcc
CPP			= $(CC) -E
AR			= $(CROSS_COMPILE)ar
NM			= $(CROSS_COMPILE)nm
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump

TOPDIR := $(shell pwd)
export TOPDIR

# export导出的变量是给子目录下的Makefile使用的
export AS LD CC CPP AR NM STRIP OBJCOPY OBJDUMP

# 编译器在编译时的参数设置
CFLAGS := -Wall -O0 -g -lpthread
# 添加头文件路径，不添加的话include目录下的头文件编译时找不到
CFLAGS += -I $(shell pwd)/../include -I /usr/include/

# 链接器的链接参数设置
LDFLAGS := -L /usr/lib/

export CFLAGS LDFLAGS

# 定义将来编译生成的可执行程序的目录
BINDIR= $(shell pwd)

# 添加项目中所有用到的源文件，有顶层目录下的.c文件，和子文件夹
# 添加顶层目录下的.c文件
# 添加顶层目录下的子文件夹（注意目录名后面加一个/）

all: 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/webshell ../common/apue_log.c ../common/net.c server.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BINDIR)/client ../common/apue_err.c ../common/apue_log.c ../common/net.c  client.c

clean:
	rm -f $(shell find -name "*.o")

distclean:
	rm -f $(shell find -name "*.o")
	rm -f $(shell find -name "*.d")
	
