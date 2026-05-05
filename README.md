# Nes-emu

Nes-emu is a education NES mcu-friendly emulator written in C.
The main function of this project is to be ported to mcu.

## Showcase

<p align="center">
  <img src="/showcase/bf.png" width="48%" />
  <img src="/showcase/ic.png" width="48%" /><br/>
  <img src="/showcase/smb.png" width="48%" />
</p>

## Building

I design nes-emu to be portable. If you want to run it at desctop pc, you need implement graphic output like SDL.
In example a sample SDL3 output is realized in framebuffero.c 

**First** you need to build SDL3 and include to CMakeFiles to make framebuffero.c works propertly.

**Second** create build folder

```sh
mkdir build
```

**Third** generate make

```sh
cmake ..
```

**Fourth** compile emulator

```sh
cmake --build .
```


## Running

If you want to try playing the game just write path to nes rom in main.c
like **boot("../rom/smb.nes");** and envoke compiled app with arg 0

```sh
my_app.exe 0
```
