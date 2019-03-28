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

Run the all-in-one jaeger environment in another terminal with:

```bash
    docker run \
    --rm \
    -p 6831:6831/udp \
    -p 6832:6832/udp \
    -p 16686:16686 \
    jaegertracing/all-in-one:1.7 \
    --log-level=debug
```

Then, the [example](./examples/App.cpp) program (along with the
hello-to string which is `Varsha` here) can be run with:

```bash
    ./app ../examples/config.yml Varsha
```

## Browsing the traces

The traces sent to the Jaeger backend can be accessed and browsed at 
http://localhost:16686/search