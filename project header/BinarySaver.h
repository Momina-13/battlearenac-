#pragma once
#ifndef BINARY_SAVER_H
#define BINARY_SAVER_H

#include <string>

template<typename T>
class BinarySaver {
public:
    void saveToFile(const T& obj, const std::string& filename);
    T loadFromFile(const std::string& filename);
};

// Template implementation (must be in header file)
template<typename T>
void BinarySaver<T>::saveToFile(const T& obj, const std::string& filename) {
    obj.save(filename);
}

template<typename T>
T BinarySaver<T>::loadFromFile(const std::string& filename) {
    T obj;
    obj.load(filename);
    return obj;
}

#endif // BINARY_SAVER_H