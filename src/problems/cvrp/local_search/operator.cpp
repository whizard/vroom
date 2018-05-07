/*

This file is part of VROOM.

Copyright (c) 2015-2018, Julien Coupey.
All rights reserved (see LICENSE).

*/

#include <iostream>

#include "operator.h"

ls_operator::ls_operator(const input& input,
                         raw_solution& sol,
                         std::vector<amount_t>& amounts,
                         index_t source_vehicle,
                         index_t source_rank,
                         index_t target_vehicle,
                         index_t target_rank)
  : _input(input),
    _sol(sol),
    _amounts(amounts),
    source_vehicle(source_vehicle),
    source_rank(source_rank),
    target_vehicle(target_vehicle),
    target_rank(target_rank),
    gain_computed(false) {
}

gain_t ls_operator::gain() const {
  assert(gain_computed);
  return stored_gain;
}

bool operator<(const ls_operator& lhs, const ls_operator& rhs) {
  return lhs.gain() > rhs.gain();
}