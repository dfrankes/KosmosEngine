#ifdef Engine_EXPORTS
#define Engine_API __declspec(dllexport)
#else
#define Engine_API __declspec(dllimport)
#endif

// This class is exported from the dll
class Engine_API Engine
{
public:
    Engine(void);
    bool drawWindow();
};

extern Engine_API int nEngine;

Engine_API int fnEngine(void);
