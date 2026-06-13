#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
class StatTracker{

    
    private:
        std::vector<T> valueClass;

    public:
        void add(T value);
        T getMin();
        T getMax();
        void printAll();


};

template <typename T>
void StatTracker<T>::add(T value)
{
    valueClass.push_back(value);
}

template <typename T>
T StatTracker<T>::getMin()
{
    return *std::min_element(valueClass.begin(), valueClass.end());
}

template <typename T>
T StatTracker<T>::getMax()
{
    return *std::max_element(valueClass.begin(), valueClass.end());
}

template <typename T>
void StatTracker<T>::printAll()
{
    for(const T& c : valueClass)
    {
        std::cout << c << std::endl;
    }
}