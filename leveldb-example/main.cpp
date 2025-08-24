//
// Created by gali yu on 2025/8/24.
//
#include <iostream>
#include "leveldb/slice.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

int main() {
    std::cout << "hello world" << std::endl;

    leveldb::DB* db;
    leveldb::Options options;

    // 如果没有就创建
    options.create_if_missing = true;

    // 这个 name 字段是自动识别 相对 / 绝对路径的
    // 打开 / 新建 一个数据库
    leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);

    if (status.ok()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cerr << "Open DB failed: " << status.ToString() << std::endl;
    }

    // 写入一个字段
    status = db->Put(leveldb::WriteOptions(), "name", "Alice");

    if (status.ok()) {
        std::cout << "write ok" << std::endl;
    } else {
        std::cerr << "Put DB failed: " << status.ToString() << std::endl;
    }

    // 读取一个字段
    std::string val;
    status = db->Get(leveldb::ReadOptions(), "name", &val);

    if (status.ok()) {
        std::cout << "read ok" << std::endl;
        std::cout << "val: " << val << std::endl;
    } else {
        std::cerr << "Get DB failed: " << status.ToString() << std::endl;
    }

    // 删除一个字段
    status = db->Delete(leveldb::WriteOptions(), "name");

    if (status.ok()) {
        std::cout << "delete ok" << std::endl;
    } else {
        std::cerr << "Delete DB failed: " << status.ToString() << std::endl;
    }

    // 批量写入多个键值
    // 需要包含 "leveldb/write_batch.h"
    leveldb::WriteBatch batch;
    batch.Put("id", "123");
    batch.Put("lang", "C++");
    batch.Put("os", "Linux");
    db->Write(leveldb::WriteOptions(), &batch);

    // 遍历数据库
    leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        std::cout << it->key().ToString() << " => " << it->value().ToString() << std::endl;
    }
    // 需要删除这个，不然会报错
    delete it;

    // 关闭数据库
    delete db;

    return 0;
}