#include "Test.h"
#include "../src/Utils/ZLogger.h"
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
        Z_CORE_CRITICAL("hi");
        Z_CLIENT_TRACE("hi");
    }




}