/**
 * implementation file of DataFrame.h
 */

#include <vector>
#include "DataType.h"
#include <string>
#include <vector>
#include <unordered_map>


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
