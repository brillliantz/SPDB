#pragma once

#include <cstddef>

/*****************字节流***************/
class Bytes {
private:
    std::size_t len_;
    char *content_;
public:
    //释放字节空间
    void free();

    //TODO:添加成员函数
    template <typename T>
        Bytes(T& obj) {
            //TODO not sure 'reinterpret_cast' is correct.
            content_ = reinterpret_cast<char*>(&obj);
            len_ = sizeof(content_);
        }

    std::size_t size() const { return len_; }
};
