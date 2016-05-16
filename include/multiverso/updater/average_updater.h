#ifndef MULTIVERSO_UPDATER_AVERAGE_UPDATER_H_
#define MULTIVERSO_UPDATER_AVERAGE_UPDATER_H_

#include "updater.h"

namespace multiverso {

template <typename T>
class AverageUpdater : public Updater<T> {
public:
  void Update(size_t num_element, T* global_model, T* local_model,
              AddOption*, size_t offset) override {
    float average_rate = 0.5;  // (float)1.0 / t_++; // option->learning_rate();
    for (size_t index = 0; index < num_element; ++index) {
      // data[index + offset] -= delta[index];
      // W_(t+1) = W_(t) + \eta * ( W_(t`) - W_(t) )
      global_model[index + offset] = average_rate * local_model[index] +
        (1 - average_rate) * global_model[index + offset];
    }
  }
private:
  // int t_{1};
};

}

#endif  // MULTIVERSO_UPDATER_AVERAGE_UPDATER_H_