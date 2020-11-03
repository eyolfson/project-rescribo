# Project Rescribo

A Java instrumentation framework written in C++

## Building

Ensure you have `JAVA_HOME` set and run the following commands:

    mkdir build && cd build
    cmake ..

If you need to manually set `JAVA_HOME`, here's an example (you may have to change your path):

    JAVA_HOME=/usr/lib/jvm/java-11-openjdk cmake ..

## Related Software

- ASM https://asm.ow2.io/
- JNIF http://sape.inf.usi.ch/jnif/
