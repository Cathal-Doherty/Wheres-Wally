# Wheres-Wally in C#

This program searches for Wally in a simple cluttered picture from Where's Wally. was able to do this using two text files containing greyscale values for each individual pixel (the reference image along with the large image). I then created a matrix for both of these images by reading the text files and changing each value into a 2-dimensional array using the ReadWriteFunctions that were given to us. Using these 2-D arrays, I began the NNS algorithm (Nearest-Neighbour Search), comparing the greyscale values of the reference image to a matrix of the same size in the large image, until I found the area that matches best, which would hopefully be the location of Wally. I then made a border around this location, changing the greyscale values of the pixels that fall in the border to 0 (black), highlighting on the image where Wally is. I then converted my 2-D array back into a one-dimensional array which could be used to create a .pgm file, displaying the entire puzzle with Wally’s location highlighted.
