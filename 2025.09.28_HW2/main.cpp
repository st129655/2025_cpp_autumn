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
int main(int argc,char** argv) {
    TextEditor editor;
    editor.addText("Hello World, this is a test");
    std::cout << "After adding text: " << editor.cursorLeft(0) << std::endl;// cursor v konce stroki
    std::cout << "cursorLeft(5): " << editor.cursorLeft(5) << std::endl;
    std::cout << "cursorRight(3): " << editor.cursorRight(3) << std::endl;
    editor.deleteText(7);
    std::cout << "After delete(7): " << editor.cursorLeft(0) << std::endl;
    editor.addText("!!!");
    std::cout << "After adding '!!!': " << editor.cursorLeft(0) << std::endl;
    return 0;
}
