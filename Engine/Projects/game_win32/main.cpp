//
//  Created by Andrey Sidorov on 12.02.2012.
//  Copyright 2012 Andrey Sidorov. All rights reserved.
//

#include "StdAfx.h"
#include "Application.h"
#include <iostream>

void main ()
{
Application::getInstance()->Run();
printf("\nGAME EXIT\n");
std::cin.get();
}