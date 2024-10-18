#include "muza/buffer.hpp"
#include <stdexcept>
namespace muza {
Buffer::Buffer() : ready(true) {}
Buffer::Buffer(int frames)
    : frames(frames), samples(frames * 2, 0), ready(true) {}
void Buffer::resize(int frames) { samples.resize(frames, 0); }
bool Buffer::isReady() { return ready.get(); }
int Buffer::getFrames() { return frames; }
void Buffer::use() {
  ready.set(false);
  for (auto &sample : samples) {
    sample = 0;
  }
}
void Buffer::setReady() { ready.set(true); }
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