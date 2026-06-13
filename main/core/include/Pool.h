#include <vector>

template <typename T>
class Pool{

    public:
        void add(T item);
        std::vector<T> getAll();
        int getCount();


    private:
        std::vector<T> items;
    
};


template <typename T>
void Pool<T>::add(T item)
{
    items.push_back(item);
}


template <typename T>
std::vector<T> Pool<T>::getAll()
{
    return items;
}

template <typename T>
int Pool<T>::getCount()
{
    return items.size();
}