#include "Debug.h"
#include <iostream>

#include "Cache.h"
#include "ConcurrentQueue.h"
#include "DataFrame.h"
#include "Exception.h"
#include "Mess.h"

#include "DataType.h"
#include "DBFileSystem.h"
#include "DBModel.h"
#include "FileStructs.h"

#if defined(_TEST_DEMO_)
void Index_test() {
    DBIndex idx;
    idx.show();
    idx.add("ask_prc0", DBData::DBDataType::DB_DOUBLE);
    idx.add("ask_qty0", DBData::DBDataType::DB_INTEGER);
    idx.show();
}

int main() {
    std::cout << "This is my fisrt test main function!" << std::endl;

    Index_test();
}
#endif
