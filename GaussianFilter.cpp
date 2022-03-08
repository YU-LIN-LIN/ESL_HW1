#include <cmath>
#include <cstdlib>
using namespace std;

#include "GaussianFilter.h"

GaussianFilter::GaussianFilter(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_filter);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// gaussian mask
const int mask[MASK_X][MASK_Y] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};


void GaussianFilter::do_filter() {
  wait(256);          // wait for enough pixel to do convolution

  while (true) {
    r_val = 0;
    g_val = 0;
    b_val = 0;
    for (unsigned int v = 0; v < MASK_Y; ++v) {
      for (unsigned int u = 0; u < MASK_X; ++u) {
        r_val += i_r.read() * mask[u][v];
        g_val += i_g.read() * mask[u][v];
        b_val += i_b.read() * mask[u][v];
        // cout << "Read at " << sc_time_stamp() << ", v = " << v << ", r_val = " << r_val << ", g_val = " << g_val << ", b_val = " << b_val << endl;
      }
    }
    int r_result = (int)(r_val / 16);
    int g_result = (int)(g_val / 16);
    int b_result = (int)(b_val / 16);
    o_r_result.write(r_result);
    o_g_result.write(g_result);
    o_b_result.write(b_result);
    // cout << "Read at " << sc_time_stamp() << ", r_result = " << r_result << ", g_result = " << g_result << ", b_result = " << b_result << endl;
    wait(10); //emulate module delay
  }
}
