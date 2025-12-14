#include <gtest/gtest.h>
#include <stack>
#include <string>
#include <iostream>

class TextEditor {
private:
    std::stack<char> left;   
    std::stack<char> right; 
    
    std::string getAllLeftText() 
    {
        std::string result;
        std::stack<char> temp;
        while (!left.empty()) 
        {
            temp.push(left.top());
            left.pop();
        }
        while (!temp.empty()) 
        {
            result += temp.top();   
            left.push(temp.top());    
            temp.pop();
        }
        return result;
    }
    
public:
    TextEditor() {}
    
    void addText(std::string text) 
    {
        for (char c : text) 
        {
            left.push(c);
        }
    }
    
    int deleteText(int k) 
    {
        int deleted = 0;
        while (deleted < k && !left.empty()) 
        {
            left.pop();
            ++deleted;
        }
        return deleted;
    }
    
    std::string cursorLeft(int k) 
    {
        while (k > 0 && !left.empty()) 
        {
            right.push(left.top());
            left.pop();
            k--;
        }
        return getAllLeftText();
    }
    
    std::string cursorRight(int k) 
    {
        while (k > 0 && !right.empty())
        {
            left.push(right.top());
            right.pop();
            k--;
        }
        return getAllLeftText();
    }
};

// =========== ТЕСТЫ ===========

// 1. Тест конструктора по умолчанию
TEST(TextEditorTest, DefaultConstructor)
{
    TextEditor editor;
    EXPECT_EQ(editor.deleteText(10), 0);
    EXPECT_EQ(editor.cursorLeft(5), "");
    EXPECT_EQ(editor.cursorRight(5), "");
}

// 2. Тест добавления текста
TEST(TextEditorTest, AddText)
{
    TextEditor editor;
    editor.addText("Hello");
    EXPECT_EQ(editor.cursorLeft(0), "Hello");
}

// 3. Тест удаления текста
TEST(TextEditorTest, DeleteText)
{
    TextEditor editor;
    editor.addText("Hello World");
    EXPECT_EQ(editor.deleteText(3), 3);
    EXPECT_EQ(editor.cursorLeft(0), "Hello Wo");
}

// 4. Тест перемещения курсора влево
TEST(TextEditorTest, CursorLeft)
{
    TextEditor editor;
    editor.addText("Hello World");
    EXPECT_EQ(editor.cursorLeft(5), "Hello ");
    EXPECT_EQ(editor.cursorLeft(2), "Hello");
}

// 5. Тест перемещения курсора вправо
TEST(TextEditorTest, CursorRight)
{
    TextEditor editor;
    editor.addText("Hello World");
    editor.cursorLeft(5);
    EXPECT_EQ(editor.cursorRight(2), "Hello Wo");
    EXPECT_EQ(editor.cursorRight(3), "Hello World");
}

// 6. Тест комбинированных операций
TEST(TextEditorTest, CombinedOperations)
{
    TextEditor editor;
    editor.addText("Hello");
    editor.addText(" World");
    EXPECT_EQ(editor.cursorLeft(0), "Hello World");
    
    editor.cursorLeft(5);
    EXPECT_EQ(editor.deleteText(3), 3);
    EXPECT_EQ(editor.cursorRight(0), "Hello W");
    
    editor.addText("!!!");
    EXPECT_EQ(editor.cursorLeft(0), "Hello W!!!");
}

// 7. Тест удаления большего количества символов, чем есть
TEST(TextEditorTest, DeleteMoreThanExists)
{
    TextEditor editor;
    editor.addText("Hello");
    EXPECT_EQ(editor.deleteText(10), 5);
    EXPECT_EQ(editor.cursorLeft(0), "");
}

// 8. Тест граничных случаев курсора
TEST(TextEditorTest, CursorBoundaryCases)
{
    TextEditor editor;
    editor.addText("Test");
    
    // Движение дальше, чем есть символов
    EXPECT_EQ(editor.cursorLeft(10), "");
    
    // Возврат обратно
    EXPECT_EQ(editor.cursorRight(10), "Test");
}

// 9. Тест добавления после удаления
TEST(TextEditorTest, AddAfterDelete)
{
    TextEditor editor;
    editor.addText("Hello");
    editor.deleteText(2);
    editor.addText("p");
    EXPECT_EQ(editor.cursorLeft(0), "Help");
}

// 10. Тест пустых операций
TEST(TextEditorTest, EmptyOperations)
{
    TextEditor editor;
    EXPECT_EQ(editor.cursorLeft(0), "");
    EXPECT_EQ(editor.cursorRight(0), "");
    
    editor.addText("");
    EXPECT_EQ(editor.cursorLeft(0), "");
    
    EXPECT_EQ(editor.deleteText(0), 0);
}

// =========== ОСНОВНАЯ ФУНКЦИЯ ===========
int main(int argc, char** argv) {
    std::cout << "🚀 Запуск тестов TextEditor..." << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    
    // Простая проверка результата
    if (result == 0) {
        std::cout << " Все тесты пройдены успешно!" << std::endl;
    } else {
        std::cout << " Есть непройденные тесты!" << std::endl;
    }
    
    return result;
}