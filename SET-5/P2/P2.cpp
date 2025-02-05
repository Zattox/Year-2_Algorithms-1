#include "bloom_filter.h"

BloomFilter::BloomFilter(size_t, size_t) {
}

void BloomFilter::add(const std::string &) {
}

bool BloomFilter::verify(const std::string &) {
}

double BloomFilter::getFPRate() const {
}

size_t BloomFilter::numberOfHashFunctions() const {
}

size_t BloomFilter::numberOfBits() const {
}

inline size_t BloomFilter::_get_hash(int, const std::string &) const {
}