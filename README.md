# Pawn Timestamp Milliseconds

**Pawn Timestamp Milliseconds** is a plugin for [Open.MP](https://open.mp) that provides three native functions to work with timestamps in milliseconds (13-digit int64 timestamps).

## Native Functions

```pawn
native GetTsString(myString[], size = sizeof(myString));
native GetTsStringFormatted(myString[], size = sizeof(myString));
native ParseMyTs(const myTs[], myString[], size = sizeof(myString));
```

## Usage Examples

```pawn
new get_ts[16];
GetTsString(get_ts); // Get current timestamp in milliseconds

new formatted_data[32];
GetTsStringFormatted(formatted_data); // Get human-readable formatted timestamp, e.g. 25.09.2025 17:06:59.024

new parsed_ts[32];
ParseMyTs("1753513619024", parsed_ts); // Parse a given timestamp string to human-readable format, e.g. 26.07.2025 07:06:59.024
```

**All functions work with strings only**, as Pawn does not support 64-bit integers.

---

## Compilation

### Requirements

- `g++-multilib >= 8` (Linux)
- `clang >= 10` (Linux)
- Visual Studio (any edition with C++17 support)
- `cmake >= 3.19`

### Linux

```bash
git clone --recursive https://github.com/borz7zy/PawnTsMs.git
cd PawnTsMs && mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-m32 -w -fPIC -static-libgcc -static-libstdc++"
cmake --build .
```

### Windows

```bash
git clone --recursive https://github.com/borz7zy/PawnTsMs.git
cd PawnTsMs && mkdir build && cd build
cmake .. -A Win32 -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

---

### Docker (ubuntu 18.04)

```bash
git clone --recursive https://github.com/borz7zy/PawnTsMs.git
cd PawnTsMs
docker build -t pawn_ts_ms .
docker create --name temp_extract_ptm pawn_ts_ms
docker cp temp_extract_ptm:/project/build/pawn_ts_ms.so .
docker rm temp_extract_ptm
```

## License

MIT License
