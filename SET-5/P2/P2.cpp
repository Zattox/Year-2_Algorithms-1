#include "bloom_filter.h"

BloomFilter::BloomFilter(size_t countOfHashes, size_t countOfBits)
    : _hashes(countOfHashes), _bits(countOfBits) {
  _filter.resize(countOfBits, false);
}

void BloomFilter::add(const std::string &value) {
  _raw_set.insert(value);
  for (int i = 0; i < _hashes; ++i) {
    size_t cur_hash = _get_hash(i, value);
    _filter[cur_hash] = true;
  }
}

bool BloomFilter::verify(const std::string &value) {
  ++cnt;
  for (int i = 0; i < _hashes; ++i) {
    size_t cur_hash = _get_hash(i, value);
    if (!_filter[cur_hash]) {
      return false;
    }
  }

  if (_raw_set.count(value) == 0) {
    ++false_positive_cnt;
  }
  return true;
}

double BloomFilter::getFPRate() const {
  if (cnt == 0) {
    return 0;
  }
  return 1.0 * false_positive_cnt / cnt;
}

size_t BloomFilter::numberOfHashFunctions() const {
  return _hashes;
}

size_t BloomFilter::numberOfBits() const {
  return _bits;
}

inline size_t BloomFilter::_get_hash(int hashNumber, const std::string &value) const {
  std::string valueWithSalt = value + std::to_string(hashNumber);
  return hasher(valueWithSalt) % _bits;
}