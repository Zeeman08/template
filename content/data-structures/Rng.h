/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: random num generator. rnd is in integer range. rnd\_range is in long long range.
 * Time: O(1)
 * Status: stress-tested
 */
#pragma once

mt19937 rng(random_device{}());
//alternatively: mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
ll rnd(ll r) {
    return rng() % r;
}
ll rng_range(ll l, ll r) {
    return uniform_int_distribution<ll>(l, r)(rng);
}
