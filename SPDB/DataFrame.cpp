/**
 * implementation file of DataFrame.h
 */

#include <vector>
#include "DataType.h"
#include "DataFrame.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <iostream>


/**
 * DBIndex implementation:
 */
DBIndex::DBIndex() {
    std::vector<std::string> indices_;
    std::vector<DBData::DBDataType> types_;
}

void DBIndex::add(std::string &name, DBData::DBDataType type) {
    indices_.push_back(name);
    types_.push_back(type);
}
void DBIndex::add(std::string &&name, DBData::DBDataType type) {
    indices_.push_back(std::move(name));
    types_.push_back(type);
}

void DBIndex::show() const {
    std::cout << "current size = " << this->size() << ", "
        << "is empty = " << this->empty();

    std::cout << "\t( ";
    for(unsigned int i = 0; i < this->size(); ++i) {
        std::cout << indices_[i] << ' ' << types_[i] << ", ";
    }
    std::cout << " )";
    std::cout << std::endl;
}

std::string DBIndex::operator[](int i) const {
    if (i >= 0) {
        return indices_[i];
    }
    else {
        return indices_[indices_.size() + i];
    }
}

//----------------------------------------
//DataRow implementation:
DBData& DataRow::operator[](std::string col) const {
    //TODO how to from the DataColumn col find the index of this row.
    //DataColumn &target_col = this->getColumn(col);
    //return target_col[primary_key_];
}

//----------------------------------------
//DataColumn implementation:
DataColumn::DataColumn(std::string name, std::vector<DBData> data, bool is_primary) :
name_{name}, is_primary_{is_primary}, size_{data.size()} {
    std::vector<DBData*> data_;
    for (auto& d : data) {
        data_.push_back(&d);
    }
}

DBData& DataColumn::operator[](const DBData &primary_key) {
    auto find_res = std::find_if(std::begin(this->data_), std::end(this->data_),
            [&primary_key](DBData *d) { return *d == primary_key; });
    int pos = find_res - std::begin(this->data_);
    if (pos == this->data_.size()) {
        throw std::invalid_argument(
                std::string("primary_key unfound in column ") + this->getName());
    }
    else {
        return *(data_[pos]);
    }
}

/*
//----------------------------------------
//DataFrame implementation:
void DataFrame::apply(void func(DataRow)) {

}

DataColumn& DataFrame::operator[](std::string col) {
    return columns_[col];
}

DataRow DataFrame::operator[](int rownum) {
}

DataFrame DataFrame::operator[](std::string names)
    */
