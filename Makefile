CC = cl
CFLAGS = /W4 /WX /EHsc
TARGET = main.exe
SRC = main.cpp

build:
	$(CC) $(CFLAGS) $(SRC) /Fe:$(TARGET)

run:
	$(TARGET)

clean:
	del $(TARGET) *.obj