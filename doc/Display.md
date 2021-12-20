# Display

The aim of this document is displaying all items real size on the monitor, scale 1:1 We define the vertical resolution in pixels per mm and the horizontal resolution in pixels per mm. 

| Display Diagonal (inch) | Display width (pixel) | Display height (pixel) | Display width (mm) | Display height (mm) | Horizontal resolution (pixel/mm) | Vertical resolution (pixel/mm) | Ratio |
|-------------------------|-----------------------|------------------------|--------------------|---------------------|----------------------------------|----------------------------------|-------|
| 12   | 2304 | 1440 |      |      |      |      | Wide |
| 13.3 | 2560 | 1600 |      |      |  8.9 |  8.9 | Wide |
| 15.4 | 2880 | 1800 |      |      |  8.7 |  8.7 | Wide |
| 16   | 3072 | 1920 |      |      |  8.9 |  8.9 | Wide |
| 14.2 | 3024 | 1964 |      |      |   10 |   10 |      |
| 16.2 | 3456 | 2234 |      |      |   10 |   10 |      |
| 21.5 | 4096 | 2304 |      |      |  8.6 |  8.6 | Wide |
| 23.5 | 4480 | 2520 |      |      |  8.6 |  8.6 | Wide |
| 27   | 5120 | 2880 |      |      |  8.6 |  8.6 | Wide |
| 32   | 6016 | 3384 |      |      |  8.6 |  8.6 | Wide |
| 31.5 | 7680 | 4320 |      |      |      |      |      |
| 49   | 5120 | 1440 |      |      |      |      | Ultra |
| 27   | 5120 | 2880 |      |      |      |      |      |
| 24   | 1920 | 1200 |      |      |      |      | Wide |
| 22   | 1680 | 1050 |  474 |  295 | 3.55 | 3.55 | Wide |
| 20   | 1680 | 1050 |      |      |      |      | Wide |
| 20   | 1600 | 1200 |      |      |      |      |      |
| 19   | 1280 | 1024 |      |      |      |      |      |
| 17   | 1680 | 1050 |  367 |  229 |      |      | Wide |
| 15   | 1400 | 1050 |      |      |      |      |      |
| 15   | 1280 |  800 |      |      |      |      | Wide |
| 13   | 1400 | 1050 |      |      |      |      |      |
| 13   | 1280 |  800 |      |      |      |      | Wide |

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
