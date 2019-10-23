This is a template for a simple fault tolerance and isolation project based
on LLVM. The project involves instrumenting an LLVM module in order to
produce a new program with varying policies and strategies for fault
tolerance.

After completing this project, a student should have a better understanding
of the workflow involved with dynamic analysis as well as common techniques
including instrumentation, runtime support libraries, and shadow memory.

Building with CMake
==============================================
1. Clone the demo repository.

        git clone http://github.com/nsumner/se-fault-tolerant-template.git

2. Create a new directory for building.

        mkdir tolerantbuild

3. Change into the new directory.

        cd tolerantbuild

4. Run CMake with the path to the LLVM source.

        cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=True \
            -DLLVM_DIR=</path/to/LLVM/build>/lib/cmake/llvm/ ../se-fault-tolerant-template

5. Run make inside the build directory:

        make

This produces a tolerator tool called `bin/tolerator` and supporting
libraries in `lib/`.

Note, building with a tool like ninja can be done by adding `-G Ninja` to
the cmake invocation and running ninja instead of make.

Running
==============================================

First suppose that you have a program compiled to bitcode:

    clang -g -c -emit-llvm simpletest.c -o simple.bc

Running `tolerator` with the "log and quit" policy:

    bin/tolerator -log simple.bc -o simple

Running the resulting instrumented program:

    ./simple

