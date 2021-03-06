#ifndef CVRP_LOCAL_SEARCH_H
#define CVRP_LOCAL_SEARCH_H

/*

This file is part of VROOM.

Copyright (c) 2015-2018, Julien Coupey.
All rights reserved (see LICENSE).

*/

#include <unordered_set>

#include "problems/cvrp/local_search/solution_state.h"
#include "structures/typedefs.h"
#include "utils/output_json.h" // Todo remove

struct solution_indicators {
  unsigned unassigned;
  cost_t cost;
  unsigned used_vehicles;
};

class cvrp_local_search {
private:
  const input& _input;
  const matrix<cost_t>& _m;
  const std::size_t V;
  const amount_t _amount_lower_bound;
  const amount_t _double_amount_lower_bound;

  std::vector<index_t> _all_routes;
  raw_solution& _target_sol;
  raw_solution _sol;
  solution_state _sol_state;
  std::unordered_set<index_t> _unassigned;
  raw_solution _best_sol;
  unsigned _best_unassigned;
  cost_t _best_cost;

  void setup();

  void set_node_gains(index_t v);
  void set_edge_gains(index_t v);

  // Todo remove
  bool _log;
  unsigned _ls_step;
  void log_solution();

  void update_costs(index_t v);
  void update_amounts(index_t v);
  void update_skills(index_t v);
  amount_t total_amount(index_t v);
  void update_nearest_job_rank_in_routes(index_t v1, index_t v2);

  void try_job_additions(const std::vector<index_t>& routes,
                         double regret_coeff);

  cost_t route_cost_for_vehicle(index_t vehicle_rank,
                                const std::vector<index_t>& route);
  void run_tsp(index_t route_rank);

  void run_ls_step();

  void remove_from_routes();

public:
  cvrp_local_search(const input& input, raw_solution& sol);

  solution_indicators indicators() const;

  void run();
};

#endif
