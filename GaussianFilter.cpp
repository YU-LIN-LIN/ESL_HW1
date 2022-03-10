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

  int row, col;   // loop index, read addr
  int i, v, u;       // loop index

  // buffer declaration
  unsigned char matrix_R[3][256];
  unsigned char matrix_G[3][256];
  unsigned char matrix_B[3][256];

  while (true) {
    // store first 3 rows
    for (row = 0; row < 3; ++row) {
      for (col = 0; col < 256; ++col) {
        if(i_r.num_available()==0) wait(i_r.data_written_event());
        if(i_g.num_available()==0) wait(i_g.data_written_event());
        if(i_b.num_available()==0) wait(i_b.data_written_event());
        matrix_R[row][col] = i_r.read();
        matrix_G[row][col] = i_g.read();
        matrix_B[row][col] = i_b.read();
      }
    }

    // do filterring at first 2 rows
    for (row = 0; row < 2; ++row) {
      for (col = 0; col < 256; ++col) {
        r_val = 0;
        g_val = 0;
        b_val = 0;
        for (v = -1; v <= 1; ++v) {
          for (u = -1; u <= 1; ++u) {
            // cout << " row + v = " << row + v << ", col + u = " << col + u << endl;
            if (row + v >= 0 && row + v < 256 && 
                col + u >= 0 && col + u < 256) {
              r_val += mask[v+1][u+1] * matrix_R[v + 1][col + u];
              g_val += mask[v+1][u+1] * matrix_G[v + 1][col + u];
              b_val += mask[v+1][u+1] * matrix_B[v + 1][col + u];
            } else {
              r_val += 0;
              g_val += 0;
              b_val += 0;
            }
          }
        }
        int r_result = (int)(r_val / 16);
        int g_result = (int)(g_val / 16);
        int b_result = (int)(b_val / 16);

        o_r_result.write(r_result);
        o_g_result.write(g_result);
        o_b_result.write(b_result);
        wait(10);
      }
    }

    // read data by row-based & do filterring 
    for (row = 2; row < 255; ++row) {     // read the last row but still has 2 rows that need to be filterred
      for (i = 0; i < 256; ++i) {
        matrix_R[0][i] = matrix_R[1][i];
        matrix_G[0][i] = matrix_G[1][i];
        matrix_B[0][i] = matrix_B[1][i];
        matrix_R[1][i] = matrix_R[2][i];
        matrix_G[1][i] = matrix_G[2][i];
        matrix_B[1][i] = matrix_B[2][i];
      }
      
      // read
      for (col = 0; col < 256; ++col) {
        if(i_r.num_available()==0) wait(i_r.data_written_event());
        if(i_g.num_available()==0) wait(i_g.data_written_event());
        if(i_b.num_available()==0) wait(i_b.data_written_event());
        matrix_R[2][col] = i_r.read();
        matrix_G[2][col] = i_g.read();
        matrix_B[2][col] = i_b.read();
      }
      // convolution
      for (col = 0; col < 256; ++col) {
        r_val = 0;
        g_val = 0;
        b_val = 0;
        for (v = -1; v <= 1; ++v) {
          for (u = -1; u <= 1; ++u) {
            if (row + v >= 0 && row + v < 256 && 
                col + u >= 0 && col + u < 256) {
              r_val += mask[v+1][u+1] * matrix_R[v + 1][col + u];
              g_val += mask[v+1][u+1] * matrix_G[v + 1][col + u];
              b_val += mask[v+1][u+1] * matrix_B[v + 1][col + u];
            } else {
              r_val += 0;
              g_val += 0;
              b_val += 0;
            }
          }
        }
        int r_result = (int)(r_val / 16);
        int g_result = (int)(g_val / 16);
        int b_result = (int)(b_val / 16);
        o_r_result.write(r_result);
        o_g_result.write(g_result);
        o_b_result.write(b_result);
        wait(10);
      }
    }
    // conv of the last row
    for (col = 0; col < 256; ++col) {
        r_val = 0;
        g_val = 0;
        b_val = 0;
        for (v = -1; v <= 1; ++v) {
          for (u = -1; u <= 1; ++u) {
            if (row + v >= 0 && row + v < 256 && 
                col + u >= 0 && col + u < 256) {
              r_val += mask[v+1][u+1] * matrix_R[v + 2][col + u];
              g_val += mask[v+1][u+1] * matrix_G[v + 2][col + u];
              b_val += mask[v+1][u+1] * matrix_B[v + 2][col + u];
            } else {
              r_val += 0;
              g_val += 0;
              b_val += 0;
            }
          }
        }
        int r_result = (int)(r_val / 16);
        int g_result = (int)(g_val / 16);
        int b_result = (int)(b_val / 16);
        // cout << "col" << col << " = " << r_val << endl;
        o_r_result.write(r_result);
        o_g_result.write(g_result);
        o_b_result.write(b_result);
        wait(10);
      }
  }
}
