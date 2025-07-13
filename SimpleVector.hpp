#ifndef SIMPLEVECTOR_HPP
#define SIMPLEVECTOR_HPP

#include <cstddef>    // Для size_t
#include <algorithm> // std::copy
#include <stdexcept> // std::out_of_range

class SimpleVector{

public:
    
    //Конструктор по умолчанию
    SimpleVector() 
        : data_(nullptr),
        size_(0),
        capacity_(0) 
    {}

    //Конструктор по параметру count
    explicit SimpleVector(size_t count) 
        : data_(count ? new int[count] : nullptr),
          size_(count),
          capacity_(count) 

    {
      for (size_t i = 0;i < size_;i++){
        data_[i] = 0;
      }
    }

    //Конструктор копирования

    SimpleVector(const SimpleVector& other)
        : data_(nullptr),
        size_(0),
        capacity_(0)
    {
        if(other.size_ > 0 && other.data_){
            data_ = new (std::nothrow) int[other.capacity_]; // std::nothrow флаг,который позволяет изменить поведение new при ошибке
            //Обычный new бросает исключение std::bad_alloc при нехватке памяти
            //new с std::nothrow возвращает nullptr вместо исключения
            if (!data_){
                throw std::bad_alloc();
            }

            std::copy(other.data_,other.data_ + other.size_, data_); // откуда копируем,что копируем,куда.
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
    }

    //Move-конструктор
    SimpleVector(SimpleVector&& other) noexcept 
        : data_(other.data_),
          size_(other.size_),
          capacity_(other.capacity_)

    {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    //Оператор присваивания
    SimpleVector& operator=(const SimpleVector& other);

    //Move-оператор присваивания
    SimpleVector& operator=(SimpleVector&& other) noexcept;

    // Для неконстантных объектов
    int& operator[](size_t index); 

    // Для константных объектов (чтобы можно было использовать с const SimpleVector)
    const int& operator[](size_t index) const;

    //Деструктор
    ~SimpleVector() 
    {
        delete[] data_; // Важно отметить, что delete без [] привёл бы к утечке памяти!!!
        // И обнулить размер и вместимость,но это необязательно,так как они не динамические.
        size_ = capacity_ = 0;
    }

    //Swap-фукнция
    friend void swap(SimpleVector& a, SimpleVector& b) noexcept {
        using std::swap;
        swap(a.data_, b.data_);
        swap(a.size_, b.size_);
        swap(a.capacity_, b.capacity_);
    }
    //Добавление в конец
    void push_back(int value);

    //Удаление из конца
    void pop_back();

    //Размер
    size_t size() const noexcept;

private:

    //Характеристика
    int* data_;
    size_t size_;
    size_t capacity_;
};

#endif // SIMPLEVECTOR_HPP
