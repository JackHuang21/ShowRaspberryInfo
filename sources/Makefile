# this is a makefile

# 定义路径变量
DIR_INC = ../includes
DIR_SRC = ../sources
DIR_OBJ = ../obj
DIR_BIN = ../bin

# wildcard 使变量中的通配符有效,下面这个命令将路径下的C文件全部展开
# notdir   将展开的文件的路径全部去除
# patsubst 将所有的C文件的后缀全部替换成O
SRC = $(wildcard ${DIR_SRC}/*.c)    			 # 指定需要编译的所有C文件
OBJ = $(patsubst %.c, ${DIR_OBJ}/%.o,$(notdir ${SRC}))   # 指定所有的obj文件


TARGET = main						 # 设置TARGET为main
BIN_TARGET = ${DIR_BIN}/${TARGET}			 # 指定输出的可执行文件

CC = gcc						 # 指定编译器为GCC
CFLAGS = -g -Wall -I${DIR_INC}				 # 配置GCC设置

${BIN_TARGET}:${OBJ}					 # 链接obj文件
	$(CC) $(OBJ) -o $@ -lwiringPi

${DIR_OBJ}/%.o:${DIR_SRC}/%.c				 # 编译C文件
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	find ${DIR_OBJ} -name *.o -exec rm -rf {}
