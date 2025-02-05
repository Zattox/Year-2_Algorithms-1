#include "P2.cpp"

using namespace std;

int main() {
  BloomFilter bf(3, 100);

  bf.add("test1");
  bf.add("test2");
  bf.verify("test3"); // This should be a false positive

  std::cout << "False positive rate is " << bf.getFPRate() << std::endl;
  std::cout << bf.numberOfHashFunctions() << std::endl;

  return 0;
}