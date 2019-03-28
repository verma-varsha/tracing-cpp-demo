#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <yaml-cpp/yaml.h>

#include <jaegertracing/Tracer.h>

using namespace opentracing;

namespace {

void setUpTracer(const char* configFilePath)
{
    auto configYAML = YAML::LoadFile(configFilePath);
    auto config = jaegertracing::Config::parse(configYAML);
    auto tracer = jaegertracing::Tracer::make(
        "example-service", config, jaegertracing::logging::consoleLogger());
    opentracing::Tracer::InitGlobal(
        std::static_pointer_cast<opentracing::Tracer>(tracer));
}

char* format_string(char* hello_to, const std::unique_ptr<opentracing::Span>& parentSpan)
{
    auto span_format_string = Tracer::Global()->StartSpan("format", {ChildOf(&parentSpan->context())});
    char buffer[50];
    int n;
    n= sprintf(buffer, "Hello, %s!", hello_to);
    span_format_string->Log({{"event", "string-format"}, {"value", buffer}});
    span_format_string->Finish();
    return buffer;
}

void print_hello(char* hello_str, const std::unique_ptr<opentracing::Span>& parentSpan)
{   
    auto span_print_hello = Tracer::Global()->StartSpan("println", {ChildOf(&parentSpan->context())});
    printf(hello_str);
    span_print_hello->Log({{"event", "println"}});
    span_print_hello->Finish();
}

void say_hello(char* hello_to)
{
    auto span_say_hello = Tracer::Global()->StartSpan("say-hello", {SetTag("hello-to", hello_to)});
    char* hello_str = format_string(hello_to, span_say_hello);
    print_hello(hello_str, span_say_hello);
    span_say_hello->Finish();
}

} 

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "usage: " << argv[0] << " <config-yaml-path>\n";
        return 1;
    }
    setUpTracer(argv[1]);

    char* hello_to = argv[2];
    
    say_hello(hello_to);

    usleep(2000000);
    opentracing::Tracer::Global()->Close();
    return 0;
}
