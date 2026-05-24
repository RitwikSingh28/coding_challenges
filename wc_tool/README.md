# wc_tool

A clone of the Unix `wc` utility, built as part of the [John Crickett Coding Challenges](https://codingchallenges.fyi/challenges/challenge-wc).

## Features
- Count lines (`-l`)
- Count words (`-w`)
- Count bytes (`-c`)
- Count characters (`-m`) with UTF-8 support
- Support for multiple files and standard input

## Building
To build the utility, run:
```bash
make
```
The binary will be located in the `build/` directory.

## Usage
```bash
./build/ccwc [flags] [file...]
```
Example:
```bash
./build/ccwc -lw main.c
```
