# huffman-compressor

A lossless compressor and decompressor using Huffman encoding algorithm

## Installing

Clone this repository, change directory to the project and run

```sh
make huffman
```

## Docs
#### Compress a file

```sh
./huffman -c <input_file_name> [compressed_file_name]
./huffman --compress <input_file_name> [compressed_file_name]
```

Input file name is required. Compressed file name if not specified is `default_compressed`.

#### Decompress a file

```sh
./huffman -d <compressed_file_name> [decompressed_file_name]
./huffman --decompress <compressed_file_name> [decompressed_file_name]
```

Compressed file name is required. Decompressed file name if not specified is `default_decompressed`.

### Tests
```sh
make test-all
```
## Authors

* [Trung Truong](https://github.com/ttrung149)

## License

This project is licensed under the MIT License - see the [LICENSE.txt](LICENSE.txt) file for details
