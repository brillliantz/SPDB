/**
 * implementation file of DataFrame.h
 */

#include <vector>
#include "DataType.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <stdexcept>


/**
 * DBIndex implementation:
 */
void DBIndex::add(std::string &name, DBData::DBDataType type) {
    indices_.push_back(name);
    types_.push_back(type);
}

std::string DBIndex::operator[](int i) const {
    if (i >= 0) {
        return indices_[i];
    }
    else {
        return indices_[indices.size() + i];
    }
}

/**
 * DataRow implementation:
 */
DBData& DataRow::operator[](std::string col) const {
    // from the DataColumn col find the index of this row.
    DataColumn &target_col = this.getColumn(col);
    return target_col[primary_key_];
}

/**
 * DataColumn implementation:
 */
DataColumn::DataColumn(std::string name, std::vector<DBData> data) :
name_{name}, is_primary_{false} {
    std::vector<DBData*> data_ {};
    for (const auto& d : data) {
        data_.push_back(&d);
    }
}

DBData& DataColumn::operator[](int i) { return *(data_[i]); }
DBData& DataColumn::operator[](const DBData &primary_key) const {
    auto find_res = std::find_if(std::begin(this.indices), std::end(this.indices)
            [](DBData *d) { return *d; });
    int pos = find_res - std::begin(this.indices);
    if (pos == this.indices.size()) {
        throw std::invalid_argument(
                std::string("primary_key unfound in column ") + this.getName())
    }
    else {
        return this[pos];
    }
}

/**
 * DataColumn implementation:
 */
void DataFrame::apply(void func(DataRow))
