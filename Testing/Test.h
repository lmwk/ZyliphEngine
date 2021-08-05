#pragma once

#include "../src/Core/Core.h"

namespace Zyliph
{

    class Z_API TestApp
    {
    public:
        TestApp();
        virtual ~TestApp();

        void Run();
    };

    _declspec(dllexport) void Print();
}