#define _CRT_SECURE_NO_WARNINGS  
#include <iostream>
#include <cstring>
#include <cstdlib>


class String {
private:
    class Proxy {
    private:
        String* parent;
        int start;
        
    public:
        Proxy(String* parent, int start) : parent(parent), start(start) {}
        
        String operator[](int end) const {
          
            if (start < 0 || end < start || start >= static_cast<int>(parent->size) || end > static_cast<int>(parent->size)) {
                return String(""); 
            }
          
            int length = end - start;
            char* temp = new char[length + 1];
            
            for (int i = 0; i < length; i++) {
                temp[i] = parent->str[start + i];
            }
            temp[length] = '\0';
            
            String result(temp);
            delete[] temp;
            return result;
        }
    };
    
public:
    String(const char* str = "") {
        size = strlen(str);
        this->str = new char[size + 1];
        strcpy(this->str, str);
    }
    
    String(size_t n, char c) : size(n) {
        str = new char[size + 1];
        for (size_t i = 0; i < size; i++) {
            str[i] = c;
        }
        str[size] = '\0';
    }
    

    ~String() {
        delete[] str;
    }
    

    String(const String& other) : size(other.size) {
        str = new char[size + 1];
        strcpy(str, other.str);
    }
    

    String& operator=(const String& other) {
        if (this != &other) {
            delete[] str;
            size = other.size;
            str = new char[size + 1];
            strcpy(str, other.str);
        }
        return *this;
    }
    
    Proxy operator[](int i) {
        return Proxy(this, i);
    }
    

    Proxy operator[](int i) const {
        return Proxy(const_cast<String*>(this), i);
    }
    

    void append(const String& other) {
        size_t new_size = size + other.size;
        char* new_str = new char[new_size + 1];
        
        strcpy(new_str, str);
        strcat(new_str, other.str);
        
        delete[] str;
        str = new_str;
        size = new_size;
    }
    

    friend std::ostream& operator<<(std::ostream& stream, const String& text) {
        stream << text.str;
        return stream;
    }

private:
    size_t size;
    char* str;
};

int main(int argc, char* argv[]) {
    String hello("hello");

    std::cout << hello << std::endl;
    
    String const hell = hello[0][4];
    std::cout << hell << std::endl;
    
    String const ell = hello[1][4];
    std::cout << ell << std::endl;
    
    String const empty = hello[1][1];
    std::cout << empty << std::endl;

    return EXIT_SUCCESS;
}