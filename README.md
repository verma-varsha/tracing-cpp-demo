# tracing-cpp-demo
A primitive illustration for distributed tracing in C++

The illustration draws inspiration from Yuri Shkuro's opentracing-tutorial
[here](https://github.com/yurishkuro/opentracing-tutorial/tree/master/python/lesson02).

This repository is derived from [Jaeger](https://www.jaegertracing.io/) 
where the example app in the examples folder has been modified for a
hello-world illustraion.

## Building

jaeger-client-cpp is built using CMake. It will automatically download
needed dependencies using [Hunter](https://docs.hunter.sh/en/latest/).

To build:

```bash
    mkdir build
    cd build
    cmake ..
    make
```

After building, the [example](./examples/App.cpp) program (along with the
hello-to string which is `Varsha` here) can be run with:

```bash
    ./app ../examples/config.yml Varsha
```
