// Written by tools/surface.py from tools/surface.json; tools/check_exports.py audits it. Do not edit by hand.

// mcpplibs.mwrap.abseil.algorithm — the names of <absl/algorithm/…> (Abseil LTS 20250512.1), unchanged:
// each is a using-declaration of the upstream entity in the namespace upstream declares it in.
module;
#include <absl/algorithm/algorithm.h>
#include <absl/algorithm/container.h>

export module mcpplibs.mwrap.abseil.algorithm;

export namespace absl {
// functions and operators (87)
using ::absl::c_accumulate;
using ::absl::c_adjacent_difference;
using ::absl::c_adjacent_find;
using ::absl::c_all_of;
using ::absl::c_any_of;
using ::absl::c_binary_search;
using ::absl::c_contains;
using ::absl::c_contains_subrange;
using ::absl::c_copy;
using ::absl::c_copy_backward;
using ::absl::c_copy_if;
using ::absl::c_copy_n;
using ::absl::c_count;
using ::absl::c_count_if;
using ::absl::c_distance;
using ::absl::c_equal;
using ::absl::c_equal_range;
using ::absl::c_fill;
using ::absl::c_fill_n;
using ::absl::c_find;
using ::absl::c_find_end;
using ::absl::c_find_first_of;
using ::absl::c_find_if;
using ::absl::c_find_if_not;
using ::absl::c_for_each;
using ::absl::c_generate;
using ::absl::c_generate_n;
using ::absl::c_includes;
using ::absl::c_inner_product;
using ::absl::c_inplace_merge;
using ::absl::c_iota;
using ::absl::c_is_heap;
using ::absl::c_is_heap_until;
using ::absl::c_is_partitioned;
using ::absl::c_is_permutation;
using ::absl::c_is_sorted;
using ::absl::c_is_sorted_until;
using ::absl::c_lexicographical_compare;
using ::absl::c_linear_search;
using ::absl::c_lower_bound;
using ::absl::c_make_heap;
using ::absl::c_max_element;
using ::absl::c_merge;
using ::absl::c_min_element;
using ::absl::c_minmax_element;
using ::absl::c_mismatch;
using ::absl::c_move;
using ::absl::c_move_backward;
using ::absl::c_next_permutation;
using ::absl::c_none_of;
using ::absl::c_nth_element;
using ::absl::c_partial_sort;
using ::absl::c_partial_sort_copy;
using ::absl::c_partial_sum;
using ::absl::c_partition;
using ::absl::c_partition_copy;
using ::absl::c_partition_point;
using ::absl::c_pop_heap;
using ::absl::c_prev_permutation;
using ::absl::c_push_heap;
using ::absl::c_remove_copy;
using ::absl::c_remove_copy_if;
using ::absl::c_replace;
using ::absl::c_replace_copy;
using ::absl::c_replace_copy_if;
using ::absl::c_replace_if;
using ::absl::c_reverse;
using ::absl::c_reverse_copy;
using ::absl::c_rotate;
using ::absl::c_rotate_copy;
using ::absl::c_sample;
using ::absl::c_search;
using ::absl::c_search_n;
using ::absl::c_set_difference;
using ::absl::c_set_intersection;
using ::absl::c_set_symmetric_difference;
using ::absl::c_set_union;
using ::absl::c_shuffle;
using ::absl::c_sort;
using ::absl::c_sort_heap;
using ::absl::c_stable_partition;
using ::absl::c_stable_sort;
using ::absl::c_swap_ranges;
using ::absl::c_transform;
using ::absl::c_unique_copy;
using ::absl::c_upper_bound;
using ::absl::linear_search;
// standard library names Abseil re-declares as its own (2)
using ::absl::equal;
using ::absl::rotate;
}  // namespace absl
