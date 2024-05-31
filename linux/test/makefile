TARGET = myprogram
OS = Windows_NT
ifeq ($(OS),Windows_NT)
    # Windows 上的特定设置
	RM = del /Q
    EXE = .exe
    MESSAGE = "Building for Windows..."
else
    # 非 Windows 系统的设置
    RM = rm -f
    EXE =
    MESSAGE = "Building for Unix-like system..."
endif

all:
	@echo $(MESSAGE)