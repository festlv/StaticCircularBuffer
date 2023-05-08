//
// Created by reinis on 23.8.5.
//

#include <CppUTest/TestHarness.h>
#include "StaticCircularBuffer.hpp"
#include <vector>
#include <iostream>

TEST_GROUP(TestSCB)
{
};

TEST(TestSCB, TestSize)
{
    StaticCircularBuffer<char, 64> b;
    CHECK_EQUAL(b.size(), 0);
    b.add('a');
    CHECK_EQUAL(b.size(), 1);
    for (int i=0; i < 65; i++)
        b.add((char)i);

    CHECK_EQUAL(b.size(), 64);
}

TEST(TestSCB, TestOrder) {
    StaticCircularBuffer<char, 5> b;
    b.add('A');
    b.add('B');
    b.add('C');
    b.add('D');
    b.add('E');
    b.add('F');


    CHECK_EQUAL(b.at(0), 'F');
    CHECK_EQUAL(b.at(1), 'E');
    CHECK_EQUAL(b.at(2), 'D');
    CHECK_EQUAL(b.at(3), 'C');
    CHECK_EQUAL(b.at(4), 'B');
}

TEST(TestSCB, TestFill) {
    StaticCircularBuffer<char, 5> b;
    b.fill('A');
    CHECK_EQUAL(b.at(0), 'A');
    CHECK_EQUAL(b.at(2), 'A');
    CHECK_EQUAL(b.size(), 0);
}

TEST(TestSCB, TestCapacity) {
    StaticCircularBuffer<char, 5> b;
    CHECK_EQUAL(b.capacity(), 5);
}
TEST(TestSCB, TestIterator) {
    StaticCircularBuffer<char, 3> b;
    b.add('A');
    b.add('B');
    b.add('C');

    std::vector<char> res;
    for (auto v: b) {
        res.push_back(v);
    }
    CHECK_EQUAL(res[0], 'C');
    CHECK_EQUAL(res[1], 'B');
    CHECK_EQUAL(res[2], 'A');
}

TEST(TestSCB, TestReadmeOutput) {
    std::cout << "Allocating static circular buffer for 3 elements" << std::endl;
    StaticCircularBuffer<uint32_t, 3> buf;
    buf.fill(0); // zero-initialize buffer
    std::cout << "buf.size() == " << buf.size() << std::endl;

    std::cout << "Adding 3 elements" << std::endl;
    buf.add(1);
    buf.add(2);
    buf.add(3);

    std::cout << "buf.size() == " << buf.size() << std::endl;
    // at returns last-added elements first
    std::cout << "buf.at(0) == " << buf.at(0) << std::endl;

    std:: cout << "Adding next element- the oldest element is overwritten" << std::endl;
    buf.add(4);
    // size has reached maximum
    std::cout << "buf.size() == " << buf.size() << std::endl;

    std::cout << "Buffer contents: ";
    for (auto val: buf) {
        std::cout << val << ", ";
    }
    std::cout << std::endl;
}
