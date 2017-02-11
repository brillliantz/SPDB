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
int main() {
    std::cout << "This is my fisrt test main function!" << std::endl;
}

#elif defined(_BYTES_TEST_)
void Bytes_test() {
    int integer = 655;
    long long int integer_l = 21312314231;
    double x = 1233241.20194871212132123;
    Bytes b1(integer), b2(integer_l), b3(x);
    std::cout << b1.size() <<','<< b2.size() << ',' << b3.size() << std::endl;
    b1.free();
    b2.free();
    b3.free();
}
int main() {
    std::cout << "Bytes test begin: ";
    Bytes_test();
    return 0;
}
#elif defined(_HEADER_TEST_)
int main() {
    std::cout << "HeaderTest complete." << std::endl;
    return 0;
}

#elif defined(_COLUMN_TEST_)

#elif defined(_INDEX_TEST_)
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
