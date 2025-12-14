#include <iostream>

template <class T, int size>
class Array
{
    T array[size];
    
public:
    Array() {};
    
    Array(T* b)
    {
        for (int i = 0; i < size; ++i)
        {
            array[i] = b[i];
        }
    }
    
    void show()
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }
    
    T minimum(Array<T, size>& m)
    {
        T minValue = array[0];
        for (int i = 1; i < size; ++i)
        {
            if (array[i] < minValue)
            {
                minValue = array[i];
            }
        }
        
 
        T otherMin = m.array[0];
        for (int i = 1; i < size; ++i)
        {
            if (m.array[i] < otherMin)
            {
                otherMin = m.array[i];
            }
        }
        
        return (minValue < otherMin) ? minValue : otherMin;
    }
};
int main(int argc,char** argv)
{
    int data1[] = {5, 3, 8, 1, 9};
    int data2[] = {10, 2, 7, 4, 6};
    
    Array<int, 5> arr1(data1);
    Array<int, 5> arr2(data2);
    
    std::cout << "Array 1: ";
    arr1.show();
    
    std::cout << "Array 2: ";
    arr2.show();
    
    // Находим минимальный элемент из минимумов двух массивов
    int result = arr1.minimum(arr2);
    std::cout << "Minimum of minimums: " << result << std::endl;
    
    return 0;
}