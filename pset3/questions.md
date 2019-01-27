# Questions

## What's `stdint.h`?

stdint.h is a header file to allow programmers to write more portable code by providing a set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

To specify **exact-width integer types**, so the programm can define minimum and maximum allowable values for each type. It using form `intN_t` and `uintN_t`, both types must be represented by exactly **N** bits.

Specifier | Signing	Bits | Bytes | Minimum Value | Maximum Value
--------- | ------------ | ----- | ------------- | -------------
`uint8_t`	| Unsigned	| 8	| 1	| 0	| 28 − 1 which equals 255
`uint16_t` | Unsigned	| 16 | 2 | 0 | 216 − 1 which equals 65,535
`int32_t`	| Signed | 32 | 4 | −231 which equals −2,147,483,648 | 231 − 1 which equals 2,147,483,647
`uint32_t` | Unsigned | 32 | 4 | 0 | 232 − 1 which equals 4,294,967,295

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

Those all just aliases for C/C++ primitive data types
* `BYTE` is an alias of `uint8_t` which is 8 bits or 1 Byte.
* `DWORD` is an alias of `uint16_t` which is 16 bits or 2 Bytes.
* `LONG` is an alias of `int32_t` which is 32 bits or 4 Bytes.
* `WORD` is an alias of `uint32_t` which is 32 bits or 4 Bytes.


## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

Byte 1 and Byte 2 should be respectively `B M` or `66 77`  or `0x42 0x4D`.

## What's the difference between `bfSize` and `biSize`?

* `bfSize` is the size, in bytes, of the bitmap file, which is a member of `BITMAPFILEHEADER` struct.
* `biSize` is the number of bytes required by the structure, which is `BITMAPINFOHEADER` struct.

## What does it mean if `biHeight` is negative?

`biHeight` is the height of the bitmap or device-independent bitmap (DIB), in pixels.
There are two varieties of DIBs:
1. A bottom-up DIB, in which the origin lies at the lower-left corner.
2. A top-down DIB, in which the origin lies at the upper-left corner.
If the height of the bitmap or `biHeight` is a negative value, it is a top-down DIB. Top-down DIBs cannot be compressed.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

`biBitCount` determines the number of bits that define each pixel and the maximum number of colors in the bitmap (BMP's color depth). 

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

There are many reasons fopen might return `NULL`:
* Wrong filename, path or directory so file cannot be found.
* Program doesn't have permissions to read or write.
* Insufficient storage space is available.

## Why is the third argument to `fread` always `1` in our code? (For example, see lines 40, 44, and 75.)

The third argument of fread is the number of elements. Since we are looking through each struct one at a time we put the third argument as 1 every time.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

Since RGBTRIPLE struct consist of 3 x BYTE of `rgbtBlue` `rgbtGreen` and `rgbtRed` on bmp header;
`typedef struct
{
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} __attribute__((__packed__))
RGBTRIPLE;`
So sizeof(RGBTRIPLE) equals 3 bytes.
(recall that BYTE is an alias of `uint8_t` which is 8 bits or 1 Byte)

`// determine padding for scanlines
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;`
padding = (4 - (3 * 1) mod 4) mod 4
        = 3

## What does `fseek` do?

`fseek` function sets the file position of the stream to the given offset.

## What is `SEEK_CUR`?

`SEEK_CUR` is a constant which can be used on `fseek` function to sets the position from where offset is added, which is Current position of the file pointer if using `SEEK_CUR` as third argument of `fseek` function.
