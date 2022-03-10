# Report

### GitHub repo

https://github.com/YU-LIN-LIN/ESL_HW1

### General description or introduction of the problem and your solution
	I use a row based data fashion in sending and receiving data.
	Reading original figure and transmitting data row by row in fifo for doing Gaussian fiterring. 
	After filterring, store the filterred data back into the figure row by row through buffer, too.
### Implementation details
	In testbench, it just takes response for data reading and writing.
	In kernel(GaussianFilter.cpp), doing Gaussian filterring(zero padding and convolution).
### Additional features of your design and models
	I used 3 buffers in 3 channels(R, G, B) in kernel. 
	In the beginning, I read 3 rows of the original figure and send it to fifo to the buffer in the kernel. 
	Then, I can do filterring at the first 2 rows, send them to fifo again and store them into the address of the original figure.
	After that, Repeat the step that read 1 row, send to fifo, filterring in the kernel, send to fifo, store in the figure.
	When the last row is read, there are 2 rows needed to be filterring. There is 1 extra row filterring in the end.
### Experimental results
	Total cycles : 718102 cycles
### Discussions and conclusions
	Considering the original method in lab2, every pixel needs to be readed and sent to fifo 9 times.
	Compared of that, the row fusion data transmission makes each pixel need to be readed and sent to fifo 1 times.
	There are 8 times * 256 pixels data transmission in fifo being saved.



