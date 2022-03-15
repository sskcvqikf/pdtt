#ifndef PDTT_TRAINER_H_
#define PDTT_TRAINER_H_
#pragma once

#include <optional>

#include "TrainParameters.h"
#include "WordEngine.h"

class Trainer final {
 public:
  explicit Trainer(WordEngine word_engine_);

  void Run(TrainParameters train_parameters) const;

 private:
  WordEngine word_engine_;
};

#endif  // PDTT_TRAINER_H_
