# cpgm
cpgm is a Plain PGM image compressor. Although it compresses an image of resolution NxM to a N+M file, 
it is not a good solution for large images in which colors vary a lot.

### How does it work?
cpgm does not use fancy compression algorithms.  It approximates the elements of a NxM matrix as 
the product of the average of it's line and column.

### How can I use it?
First, compile it by running

```
make compress
make uncompress
```

Then, to compress a image, run `./compress <input_image.pgm> <output_image.cpgm>`. To uncompress it run 
`./uncompress <compressed_image.pgm> <output_file.pgm>`.

### Why did you make this?
I wanted to visualize how good of an approximation was this approach.
