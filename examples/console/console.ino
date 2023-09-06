#include "src/SessionManager.h"
#include <SD.h>

void setup()
{
	try
	{
		Serial.begin(115200);

		if (!SD.begin())
			throw std::runtime_error("cannot initialise SD");

		if (SD.exists("/sessions.db"))
			SD.remove("/sessions.db");
	}
	catch (const std::exception &e)
	{
		Serial.println(e.what());
	}
}

void loop() {}