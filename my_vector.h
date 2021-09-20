//
// Created by Daniil Kolesnik on 31/08/2021.
//

#ifndef LR5_ISSUERESOLUTION_MY_VECTOR_H
#define LR5_ISSUERESOLUTION_MY_VECTOR_H


#include <stddef.h>
#include <iostream>
#include "my_iterator.h"

/*Exceptions
1) at +
2) [] n
3) front ?
4) backv ?
5) data ne
6) begin ne
7) end ne
8) empty ne
9) size ne
10) reserve +

11) capacity ne
12) clear ne
13) insert (вставка элемента) +
14) erase (удаление по итератору, удаление ?
диапазона по итераторам)
15) push_back ?
16) pop_back ne
17) resize ?
18)swap ?

 */

template<typename T>
class my_vector {


private:


    size_t capacity_ = 0;
    size_t number_of_elements = 0;
    T *data_ = nullptr;

    double factor = 1.5;


public:

    my_vector() : capacity_(0), number_of_elements(0), data_(nullptr) {}

//    my_vector()


    my_vector(size_t n, const T &value) {
        try {
            if (n >= 16000) throw (5,5);
            reserve(n);
            number_of_elements = n;
            for (size_t i = 0; i < number_of_elements; ++i) {
                data_[i] = value;
            }


        }
        catch (double){
            std::cout << "try with less capacity\n";
        }


    }

    my_vector(const my_vector &other) {
        reserve(other.capacity_);
        number_of_elements = other.number_of_elements;
        for (size_t i = 0; i < number_of_elements; ++i) {
            data_[i] = other.data_[i];
        }
    }  // copy constructor




    ~my_vector() {
        if (data_) {
            delete[] data_;
        }
    }


    T &at(size_t pos) {

        try {
            if (pos >= number_of_elements) throw 5.5;
            return data_[pos];
        }
        catch (double) {
            std::cout << " Out of range " << std::endl;
        }


    }

    const T &at(size_t pos) const {
        try {
            if (pos >= number_of_elements) throw 5.5;
            return data_[pos];
        }
        catch (double) {
            std::cout << " Out of range " << std::endl;
        }
    }


    void clear() {
        delete[] this->data_;
        capacity_ = 0;
        number_of_elements = 0;
        data_ = nullptr;
    }

    T &operator[](size_t pos) {

        return data_[pos];


    }

    const T &operator[](size_t pos) const {

        return data_[pos];

    }

    T &front() { // нужно ли обрабатывать пустой вектор?
        return data_[0];
    }

    const T &front() const {
        return data_[0];
    }

    T &back() {
        try{
            if (number_of_elements == 0) throw 5.5;
            return data_[number_of_elements - 1];
        }
        catch (double){
            std::cout << " Container is empty " << std::endl;
        }

    }

    const T &back() const {
        try{
            if (number_of_elements == 0) throw 5.5;
            return data_[number_of_elements - 1];
        }
        catch (double){
            std::cout << " Container is empty " << std::endl;
        }
    }

    my_iterator<T> end() const {
        return my_iterator(data_ + number_of_elements);
    }

    my_iterator<T> begin() const {
        return my_iterator(data_);
    }

    size_t size() const {
        return number_of_elements;
    } // return number of elements //PASS

    size_t capacity() const {
        return capacity_;
    } // return capacity //PASS

    my_vector &operator=(const my_vector &other) {  // overloading "equalize" operation for 2 vectors
        if (this == &other) std::cout << "youre trying to equalize same objects" << std::endl;
        else { // self initialization check


            reserve(other.capacity_);

            number_of_elements = other.number_of_elements;
            for (size_t i = 0; i < number_of_elements; ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }

    T *data() {
        return data_;
    } // return data

    const T *data() const {
        return data_;
    } //return data




    bool empty() const {
        return number_of_elements == 0;
    } // if the container is empty returns 1 //PASS

    void swap(my_vector &other) {
        std::swap(capacity_, other.capacity_);
        std::swap(number_of_elements, other.number_of_elements);
        std::swap(data_, other.data_);
    }

    void pop_back() {
        if (number_of_elements == 0) return;
        else if (number_of_elements == 1) {
            delete[] data_;
            capacity_ = 0;
            number_of_elements = 0;
            data_ = nullptr;
        } else {
            --number_of_elements;
        }
    }

    void push_back(const T &value) {
        if (!data_) { reserve(1); }
        else if (number_of_elements + 1 > capacity_) {
            if (capacity_ == 1) reserve(2);
            else reserve(capacity_ * factor);
        }
        data_[number_of_elements] = value;
        ++number_of_elements;
    }

    void reserve(size_t new_cap) {
        if (new_cap <= capacity_) {
            return;
        }
        T *tmp = new T[new_cap];

        for (size_t i = 0; i < number_of_elements; ++i) {
            tmp[i] = data_[i];
        }
        if (data_) delete[] data_;
        data_ = tmp;
        capacity_ = new_cap;
    } //PASS

    void resize_(size_t count, const T &value) {

        T *tmp = new T[count];

        for (size_t i = 0; i < std::min(number_of_elements, count); ++i) {
            tmp[i] = data_[i];
        }
        if (data_) delete[] data_;
        data_ = tmp;
        capacity_ = count;

        for (size_t i = std::min(number_of_elements, count); i < count; ++i) {
            data_[i] = value;
        }
    } //PASS

    my_iterator<T> insert(my_iterator<T> iter,const T& value) {
        try {
            if (this->begin() == this->end()) throw 5,5;
            auto temp = back();
            auto temp2 = iter - begin();
            auto it = end() - 1;
            for (; it > iter; --it) {
                *it = *(it - 1);
            }
            *it = value;
            push_back(temp);
            return my_iterator(data_ + temp2);
        }
        catch (double){
            std::cout << "First and last iterators point at the same element\n";
        }

    }


    my_iterator<T> erase(const my_iterator<T> pos) {
        try {
            if (pos == end()) throw 5,5;
            for (auto it = pos; it < end() - 1; ++it) {
                *it = *(it + 1);
            }
            --number_of_elements;
            return pos;
        }
        catch (double) {
            std::cout << "cant use end() as an arg\n";
        }
        
    } //PASS




    my_iterator<T> erase(const my_iterator<T> first, const my_iterator<T> last) {
        auto it = first;
        auto it2 = last;
        for (;  it2!= end(); ++it, ++it2) {
            *it = *it2;
        }

        number_of_elements = number_of_elements - (last - first);
        return first;
    } //PASS





    size_t get_capacity() {
        return capacity_;
    }

    size_t get_n() {
        return number_of_elements;
    }


};


#endif //LR5_ISSUERESOLUTION_MY_VECTOR_H
