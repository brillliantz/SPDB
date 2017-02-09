/**
 * implementation file of DataFrame.h
 */

#include <vector>
#include "DataType.h"
#include <string>
#include <vector>
#include <unordered_map>


/**
 * Index implementation:
 */
void Index::add(std::string &name, DBData::DBDataType type) {
    indices.push_back(name);
    types.push_back(type);
    ++length;
}

std::string Index::operator[](int i) const {
    if (i >= 0) {
        return indices[i];
    }
    else {
        return indices[indices.size() + i];
    }
}

/**
 * DataColumn implementation:
 */
DataColumn::DataColumn(std::string name, std::vector<DBData> data) :
name_{name} {
    std::vector<DBData*> data_ {};
    for (const auto& d : data) {
        data_.push_back(&d);
    }
}

std::string DataColumn::getName() const { return name_; }

std::vector<DBData*>& DataColumn::getData() const { return data_; }

DBData& DataColumn::operator[](int i) { return *(data_[i]); }

