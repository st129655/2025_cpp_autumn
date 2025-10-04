Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = myapp
SOURCE = main.cpp

# Сборка по умолчанию
all: $(TARGET)

# Сборка целевой программы
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Очистка
clean:
	rm -f $(TARGET)

# Пересборка
rebuild: clean all

# Запуск
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run