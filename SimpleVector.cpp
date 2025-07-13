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

int& SimpleVector::operator[](size_t index) {
    return data_[index]; // Доступ без проверки границ (как в std::vector)
}

const int& SimpleVector::operator[](size_t index) const {
    return data_[index];
}

void SimpleVector::push_back(int value)
{
    if(size_ >= capacity_){
        // 1. Вычисляем новый размер
        size_t new_capacity_ = capacity_ > 0 ? capacity_ * 2 : 1;
        // 2. Выделяем новый массив
        int* new_data = new int[new_capacity_];
        // 3. Копируем старые данные
        for(size_t i = 0; i<size_ ;++i){
            new_data[i] = data_[i];
        }
        // 4. Освобождаем старую память
        delete[] data_;
        // 5. Обновляем указатель и capacity
        data_ = new_data;
        capacity_ = new_capacity_;
    }
    // 6. Добавляем элемент
    data_[size_] = value;
    ++size_;

}

void SimpleVector::pop_back()
{
    if (size_ == 0) {
        throw std::out_of_range("Cannot pop from empty vector");
    }
    --size_; 
}

size_t SimpleVector::size() const noexcept {
    return size_;
}
