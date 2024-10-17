#include "muza/buffer.hpp"
#include <stdexcept>
namespace muza {
Buffer::Buffer(int frames) : samples(frames * 2, 0), ready(true) {}
bool Buffer::isReady() { return ready; }
void Buffer::use() { ready = false; }
const void *Buffer::data() { return samples.data(); }
int Buffer::size() { return samples.size(); }
void Buffer::copyTo(Buffer &buffer) {
  if (size() != buffer.size()) {
    throw std::runtime_error("Buffer size not equal\n");
  }
  for (unsigned long i = 0; i < samples.size(); ++i) {
    buffer[i] = (*this)[i];
  }
}
float &Buffer::operator[](int index) {
  if (index < 0 && index >= size()) {
    throw std::runtime_error("Buffer access out of range\n");
  }
  return samples[index];
}

} // namespace muza