#pragma once

#include <vector>
#include "DataType.h"
#include <string>
#include <vector>
#include <unordered_map>

/*
    DataFrame实现了对带有索引的矩阵的基本操作，是DBTable的矩阵部分功能的抽象
    DataRow则是对DBEntry的Series功能抽象
    DataColumn是DataFrame的基本组成单位，存储了有名的一列数据

    如果有不明白的地方，想想pandas里是怎么做的
    Note:
        建议不要在析构函数里删掉Data，否则每次生成新的DataFrame需要重新复制所有
        的Data，通过从源头上统一控制Data的生成和删除（比如在本实验中可以在整个Table被
        从内存中删除时删除Data）来减小复制的开销和实现很多拷贝构造函数、移动赋值函数等
        的成本
*/

/***********DataFrame索引********/
//包含了列名、列数据类型等信息
class DBIndex {
private:
    std::vector<std::string> indices_;
    //TODO：添加成员
    std::vector<DBData::DBDataType> types_;

public:
    //TODO:添加成员
    DBIndex();

    void add(std::string &name, DBData::DBDataType type);
    void add(std::string &&name, DBData::DBDataType type);

    bool empty() const { return indices_.empty(); }
    std::size_t size() const { return indices_.size(); }

    void show() const;

    std::string operator[](int i) const;    //TODO Though DBIndex is ordered,
                                            //     Columns in DataFrame is not.
};


/**********数据行*************/
class DataRow {
private:
    DBIndex index_;
    //TODO:添加成员变量
    DBData* primary_key_;    //TODO where should I create this instance?

public:
    DBData& operator[](std::string col) const;
    //TODO:添加成员函数
    const DBIndex& getIndex() const { return index_; }
};


/*********数据列************/
class DataColumn {
private:
    std::string name_;
    std::vector<DBData*> data_;
    bool is_primary_;
    std::size_t size_;

public:
    DataColumn(std::string name, std::vector<DBData> data,
               bool is_primary = false);
    std::string getName() const { return name_; }
    std::vector<DBData*>& getData() { return data_; }
    DBData& operator[](int i) { return *(data_[i]); }
    //TODO:添加成员函数
    void rename(std::string new_name) { name_ = new_name; }
    DBData& operator[](const DBData &primary_key);
};


/***************数据矩阵*************/
class DataFrame {
private:
    //索引
    DBIndex index_;

    //数据列
    std::unordered_map<std::string, DataColumn> columns_;

    //TODO:添加成员变量
public:
    //将函数应用到每一行并不返回值
    void apply(void func(DataRow));

    //将函数应用到每一行并返回一个数据列，每行的值为参数函数的返回值
    template<typename T>
    DataColumn applyWithRet(T func(DataRow));
    //TODO:添加成员函数
    DataFrame();

    //设置索引
    void setIndex(DBIndex& index);
    DBIndex& getIndex();

    //获取列(可以用来添加列)
    DataColumn& operator[](std::string col);

    //获取行
    DataRow operator[](int rownum);

    //获取子数据帧
    DataFrame operator[](std::string names[]);
    DataFrame operator[](int rows[]);
    DataFrame operator[](std::pair<int, int> slice_range);

    //获取深拷贝的子数据帧
    DataFrame copy(std::string names[]);
    DataFrame copy(int rows[]);
    DataFrame copy(std::pair<int, int>);
    DataFrame copy(std::pair<int, int>, std::string names[]);

    //删除列
    DataFrame drop(std::string[]);

    /**************OPTIONAL***********/
    /*
        实现对key的迭代: implement begin, end
        eg 对每列第一个值加一：
            for (auto key : df)
                df[key][0]++;

        ref：http://blog.csdn.net/is2120/article/details/30238945
    */
    template <typename T>
    class const_iterator {
      public:
        const_iterator();
        const T &operator*();

        const_iterator &operator++();

        const_iterator &operator++(int);

        const_iterator &operator--();

        const_iterator &operator--(int);

        bool operator==(const const_iterator &rhs);
        bool operator!=(const const_iterator &rhs);

      protected:
        T *current;

        T &retreve();

        const_iterator(T *p);
    };


    //TODO:添加成员函数
};

