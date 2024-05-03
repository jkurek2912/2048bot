Created by Jacob Kurek on Thursday, May 2, 2024

Optimization list:
   Instead of storing each state as a 2d vector, I can represent each value as the exponent 2 is raised to in order to
   create that value. For example, 2048 would be 11 because 2^(11) is 2048. Then, I could store the state in a 64-bit
   integer where each group of 4 bits is one index in the state. This would allow me to store values up to
   2^(15) = 32768 in a 64-bit integer. I could then parse out the values using bit-shifts.