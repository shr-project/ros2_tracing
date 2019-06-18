// Copyright 2019 Robert Bosch GmbH
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef TRACETOOLS__UTILS_HPP_
#define TRACETOOLS__UTILS_HPP_

#include <stddef.h>
#include <functional>

template<typename T, typename ... U>
void * get_address(std::function<T(U...)> f)
{
  typedef T (fnType)(U...);
  fnType ** fnPointer = f.template target<fnType *>();
  // Might be a lambda
  if (fnPointer == nullptr) {
    return 0;
  }
  return reinterpret_cast<void *>(*fnPointer);
}

const char * get_symbol(void * funptr);

#endif  // TRACETOOLS__UTILS_HPP_
