#ifndef Gaussian_FILTER_H_
#define Gaussian_FILTER_H_
#include <systemc>
using namespace sc_core;

#include "filter_def.h"

class GaussianFilter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<unsigned char> i_r;
  sc_fifo_in<unsigned char> i_g;
  sc_fifo_in<unsigned char> i_b;
  // sc_fifo_out<int> o_result;
  sc_fifo_out<int> o_r_result;
  sc_fifo_out<int> o_g_result;
  sc_fifo_out<int> o_b_result;

  SC_HAS_PROCESS(GaussianFilter);
  GaussianFilter(sc_module_name n);
  ~GaussianFilter() = default;

private:
  void do_filter();
  // int val[MASK_N];
  int r_val;
  int g_val;
  int b_val;
};
#endif
