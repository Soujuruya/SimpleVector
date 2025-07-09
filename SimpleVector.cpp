#include "SimpleVector.hpp"

// Копирующее присваивание
SimpleVector& SimpleVector::operator=(const SimpleVector& other){
    if (this == &other){ // самоприсваивание
        return *this;
    } 

    SimpleVector temp(other); // создание копии

    swap(*this,temp); // свапаем значения

    return *this; // возращаем
}

//   Перемещающее присваивание 
SimpleVector& SimpleVector::operator=(SimpleVector &&other) noexcept
{
    if(this != &other){
        // Освобождаем текущие ресурсы
        delete[] data_; 
        // Перехватываем ресурсы other
        data_ = other.data_; 
        size_ = other.size_;
        capacity_ = other.capacity_;
        // Обнуляем other
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    return *this;
}
