# wolfHAL

wolfHAL is a lightweight, OS-agnostic, compiler-agnostic hardware abstraction
layer for embedded targets written in C. It provides a uniform driver model
with vtable dispatch by default and an opt-in single-instance fast path for
size-constrained builds.

## Repository layout

```
wolfHAL/                    Public headers (API surface)
  platform/                 Platform-specific device macros and definitions
src/                        Driver implementations (generic + platform)
boards/                     Example board configurations used for testing and examples
examples/                   Example applications
tests/                      Test framework and test suites
```

## Further reading

- [Getting Started](docs/getting_started.md) — Integrating wolfHAL into your project
- [Boards](boards/README.md) — Example board configurations
- [Examples](examples/README.md) — Example applications
- [Tests](tests/README.md) — Test framework and test suites
- [Writing a Driver](docs/writing_a_driver.md) — How to implement a driver for a new platform
- [Adding a Board](docs/adding_a_board.md) — How to add a new board configuration
- [Adding a Peripheral](docs/adding_a_peripheral.md) — How to add an external peripheral device
- [Adding an Example](docs/adding_an_example.md) — How to add a new example application
- [Adding a Test](docs/adding_a_test.md) — How to add hardware tests

## License

GPLv3 -- see [LICENSE](LICENSE) for details.
