#include "Mess.h"
#include <iostream>


void Bytes::free() {
    //TODO why not release memory in destructor?
    //for (std::size_t i = 0; i < len_; ++i) {
    //    delete (this->content_ + i);
    //}
    delete []content_;
}
