# LBYARCH S18B MP2
## Ambata, Simon Luis & Aragon, Enrique Miguel 
MP Specs:
![MP Specs](https://github.com/ena0553/LBYARCH-MP2/blob/main/Images/MP-specs.png?raw=true)
When performing the stress tests on both kernels, we executed each kernel 30 times in order to get the average execution time.

## Sample runs using vector sizes of 2e20, 2e24, and 2e28 are shown below:
![Sample Screenshot](https://github.com/ena0553/LBYARCH-MP2/blob/main/Images/2e20result.png?raw=true)

![Sample Screenshot](https://github.com/ena0553/LBYARCH-MP2/blob/main/Images/2e24result.png?raw=true)

![Sample Screenshot](https://github.com/ena0553/LBYARCH-MP2/blob/main/Images/sample-result.png?raw=true)

It is immediately evident that the Assembly kernel is significantly faster than the C kernel. Across all three stress tests, the average time for Assembly was consistently about 2.5x faster than the average time for C. This highlights the advantage of using a low-level language such as Assembly for handling multiple computations on a large scale, as compared to a language like C which is higher level in compariosn.

Video Demo Link:<link>
