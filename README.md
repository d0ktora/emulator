# Simple Emulator

Simple emulator in C. Reads a custom binary format and runs it like a barebones virtual CPU.

## What's inside

- `src/`: all the C source files — CPU, memory, debugger, instruction set, etc.
- `make run`: builds and runs the emulator (`release/emulator`)

## Compiler

A Python script that takes a text-based program and compiles it into a binary file the emulator can run.

## TODO

- Finish parsing support for all instructions in the compiler
- Add support for passing compiled binaries directly to the emulator
