#include "Kosmos.hpp"
#include "Engine/Engine.hpp"
#include "Engine/helpers/Logger.hpp"

Logger Kosmos::logger;
Engine *Kosmos::engine;
int main(int argc, char **argv)
{
    Kosmos::engine = new Engine();
    Kosmos::engine->init();
    return 0;
}