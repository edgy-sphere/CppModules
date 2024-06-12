//

module;
#include "Misc/AutomationTest.h"

export module tests;

import country;

#if WITH_DEV_AUTOMATION_TESTS

namespace Tests
{
	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CountryBasic, "Basic", EAutomationTestFlags::EditorContext | EAutomationTestFlags::PerfFilter)

	bool CountryBasic::RunTest(const FString& Parameters)
	{
		Country c{};
		c.InitDev();

		return true;
	}
}



#endif
