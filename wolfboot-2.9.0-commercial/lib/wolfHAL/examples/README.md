# wolfHAL Examples

## Building

From an example directory:

```
cd blinky
make BOARD=<board>
```

The output binary is placed in `build/<board>/`.

## Example Structure

Each example contains its application source and a Makefile that references a
board from the top-level `boards/` directory:

```
<example>/
  main.c
  Makefile
```

Board support (device instances, linker scripts, etc.) lives in the top-level
`boards/<board>/` directory. See [boards/README.md](../boards/README.md) for
details.
