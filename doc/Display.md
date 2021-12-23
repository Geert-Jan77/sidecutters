# Display

The aim of this document is displaying all items real size on the monitor, scale 1:1. We define the resolution in pixels per mm. Possible choices for the display depend on the pixel width and height. GTK3 Also has a method to determine the display width in mm and the display height in mm, and these methods will be used first.

| Display Diagonal (inch) | Display width (pixel) | Display height (pixel) | Display width (mm) | Display height (mm) | Resolution (pixel/mm) | Ratio |
|-------------------------|-----------------------|------------------------|--------------------|---------------------|-----------------------|-------|
| 49   | 5120 | 1440 | 1198 |  337 |  4.27 | 3.5556 |
| 32   | 6016 | 3384 |  708 |  398 |  8.49 | 1.7778 |
| 31.5 | 7680 | 4320 |  697 |  392 | 11.01 | 1.7778 |
| 27   | 5120 | 2880 |  598 |  336 |  8.57 | 1.7778 |
| 24   | 1920 | 1200 |  517 |  323 |  3.71 | 1.6000 |
| 23.5 | 4480 | 2520 |  520 |  293 |  8.61 | 1.7778 |
| 22   | 1680 | 1050 |  474 |  296 |  3.55 | 1.6000 |
| 21.5 | 4096 | 2304 |  476 |  268 |  8.61 | 1.7778 |
| 20   | 1680 | 1050 |  431 |  269 |  3.90 | 1.6000 |
| 20   | 1600 | 1200 |  406 |  305 |  3.94 | 1.3333 |
| 19   | 1280 | 1024 |  377 |  301 |  3.40 | 1.2500 |
| 17   | 1680 | 1050 |  366 |  229 |  4.59 | 1.6000 |
| 16.2 | 3456 | 2234 |  346 |  223 | 10.00 | 1.5470 |
| 16   | 3072 | 1920 |  345 |  215 |  8.91 | 1.6000 |
| 15.4 | 2880 | 1800 |  332 |  207 |  8.68 | 1.6000 |
| 15   | 1400 | 1050 |  305 |  229 |  4.59 | 1.3333 |
| 15   | 1280 |  800 |  323 |  202 |  3.96 | 1.6000 |
| 14.2 | 3024 | 1964 |  302 |  196 | 10.00 | 1.5397 |
| 13.3 | 2560 | 1600 |  286 |  179 |  8.94 | 1.6000 |
| 13   | 1400 | 1050 |  264 |  198 |  5.30 | 1.3333 |
| 13   | 1280 |  800 |  280 |  175 |  4.57 | 1.6000 |
| 12   | 2304 | 1440 |  258 |  162 |  8.91 | 1.6000 |

# Pdf

A Portable data file is printed with horizontal and vertical resolution of `600 pixel per inch` = `600 / 25.4 pixel/mm` = *23.622047 pixel / mm*

### A4 paper format

The A0 size is defined as follows:
The paper has an area of one square meter. The aspect ratio is the square root of two.
The exact `A0_width = 2^(1/4)` m and the exact `A0_height = 2^(1/2) * 2^(1/4) / 2 m`
The A1 size is obtained by halving the longest side of an A0, and after halving the paper four times, the A4 size is obtained.

The exact `A4_width = 2^(1/4) / 4 m` and the exact `A4_height = 2^(1/2) * 2^(1/4) / 8 m`
This evaluates to *297.3 mm x 210.2 mm*

### Letter

The letter size is 11 x 8.5 inches. It is exactly *279.4 mm x  215.9 mm*

# Precision

The *10^(-6)* precision of a float is used for every variable. All floats should be absolute minimum 1.0, so that the precision is at least `0.000001 / 1.000000 = 10^(-6)`
The worst-case scenario is a variable `(float)fWorst = 1.000000 +- 0.000001`
