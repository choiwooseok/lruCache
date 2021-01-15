#include <iostream>
#include <stdexcept>
#include <memory>
#include <gtest/gtest.h>
#include "LRUCache.hpp"


TEST(CACHE_TEST, pruneTest) {
    cache::LRUCache<std::string, int> cache(2);
    cache.put("a", 1);
    cache.put("aa", 2);
    cache.put("aaa", 3);
    cache.put("aaaa", 4);

    EXPECT_EQ(cache.size(), 2);
    EXPECT_EQ(cache.contains("a"), false);
    EXPECT_EQ(cache.contains("aa"), false);
    EXPECT_EQ(cache.contains("aaa"), true);
    EXPECT_EQ(cache.contains("aaaa"), true);
    EXPECT_THROW(cache.get("a"), std::invalid_argument);
}

TEST(CACHE_TEST, missingKeyTest) {
    cache::LRUCache<std::string, int> cache(2);
    cache.put("a", 1);

    EXPECT_THROW(cache.get("b"), std::invalid_argument);
}

TEST(CACHE_TEST, getTest) {
    cache::LRUCache<std::string, int> cache(2);
    cache.put("a", 1);
    cache.put("aa", 2);

    EXPECT_EQ(cache.get("a"), 1);
    EXPECT_EQ(cache.get("aa"), 2);

    int testParam = 3;
    cache.put("aaa", testParam);
    EXPECT_EQ(cache.get("aaa"), testParam);
}

TEST(CACHE_TEST, vectorTest) {
    cache::LRUCache<std::string, std::vector<int>&> cache(2);
    std::vector<int> testParam{0,1};
    cache.put("a", testParam);
    EXPECT_EQ(cache.get("a"), testParam);
    EXPECT_EQ(cache.get("a").data(), testParam.data());
}

TEST(CACHE_TEST, vectorTest2) {
    cache::LRUCache<std::string, std::vector<int>> cache(2);
    std::vector<int> testParam{0,1};
    cache.put("a", testParam);
    EXPECT_EQ(cache.get("a"), testParam);
    EXPECT_NE(cache.get("a").data(), testParam.data());
}


class A {
private:
    int a;        
public : 
    A() : a(0) {}
    A(int a) : a(a) {}
    int getA() {return a;}
    void setA(int a) {this->a = a;}
    virtual ~A(){}
};

TEST(CACHE_TEST, putClassTest) {
    cache::LRUCache<std::string, std::shared_ptr<A>> cache(2);

    std::shared_ptr<A> testParam0 = std::make_shared<A>(3);
    std::shared_ptr<A> testParam1 = std::make_shared<A>(4);
    cache.put("a", testParam0);
    cache.put("aa", testParam1);
    EXPECT_EQ(cache.get("a")->getA(), 3);
    EXPECT_EQ(cache.get("aa")->getA(), 4);

    EXPECT_EQ(testParam0.use_count(), 2);
    cache.put("aaa", std::make_shared<A>(5));
    EXPECT_EQ(testParam0.use_count(), 1);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
