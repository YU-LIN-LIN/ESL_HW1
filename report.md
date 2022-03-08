# Report

### GitHub repo

https://github.com/YU-LIN-LIN/ESL_HW1

### General description or introduction of the problem and your solution
	I use a row based data fashion in sending and receiving data.
    Reading original figure in a Row buffer, transmit data in fifo and wait for doing Gaussian fiterring. 
    After filterring, store the filterred data back into the figure.
### Implementation details
	Declare three 3*256 unsigned char array(R, G, B repectively).
	Use the remainder of 3 to determine which row should each pixel being stored in the buffer.
	Read original figure pixel by pixel and store them to the buffer.
	The reading rate is 1 pixel/cycle. While reading at the 257th pixel ((1, 1) in the matrix), 
	I can start do filterring from the first pixel((0, 0) in the matrix).
	After reading finished, there are 257 remaining pixels not filterred yet. Using another for loop to finish it.	
### Additional features of your design and models
	In the beginning, I didn't wait for the buffer being full of reading pixels and then start to do filterring. 
	I start to do filterring when the buffer get enough pixels (the 257th pixel). 
	Therefore, compared to the method that read the first 3 rows over and started to do filterring, 
	I saved 511 cycles if each 3*3 convolution needs 10 cycles to be done.
### Experimental results
	Total cycles : 256 + 256 * 256 * 10 = 655616
### Discussions and conclusions
	The number of pixel transfer of the original way:
	9*256*256-255*4(read) + 256*256(store after filterring) = 654336
	The number of pixel transfer of the row based data transmission way:
	256*256*2(read & store after filterring) = 65536
	By row based data fusion, I created a buffer to store data instead of receiving pixels from memory every time. 
	Although this may not benefit while software simulation, 
	it could save much power in hard ware by reducing data access from memory directly.
	I generated golden pattern from modifying lab2's code, changing the sobel filter to gaussian filter. 
	The test pattern is identical with the golden pattern after checking.




