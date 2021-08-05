#include "Test.h"
#include "../src/Common.h"
#include <iostream>

namespace Zyliph
{
   TestApp::TestApp()
   {
       
   }

    TestApp::~TestApp()
    {
        
    }

    void TestApp::Run()
    {
        Zyliph::ZLogger::Init();
        Zyliph::ZLogger::GetCoreLogger()->warn("test");
        std::cout << "Testing" << std::endl;
    }




}