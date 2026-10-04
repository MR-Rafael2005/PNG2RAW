# PNG2RAW

A simple C program that converts PNG images to RAW format (tested and used with PS2SDK).

## Requirements

- [stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)
- C compiler (GCC recommended)

## Compilation

On Linux or MinGW:
```bash
gcc png2raw.c -o png2raw -lm
```

On Windows (MinGW):
```bash
gcc png2raw.c -o png2raw.exe -lm
```

## Usage

```bash
./png2raw file.png output.raw rgb
./png2raw file.png output.raw rgba
```

- The last argument sets the output format: `rgb` (24 bits) or `rgba` (32 bits).

## Example

```bash
./png2raw texture.png texture.raw rgba
```

This will generate a `texture.raw` file containing the raw pixel data.

## Notes

- The generated RAW format is useful for homebrew projects, such as with PS2SDK.
- Make sure the input PNG file exists and is accessible.

## License

MIT or public domain (like [stb](https://github.com/nothings/stb)).
