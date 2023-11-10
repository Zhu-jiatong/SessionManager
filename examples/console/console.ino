#include "src/SessionManager.h"
#include <SD.h>

void createSession();
void deleteSession();
void checkSession();

SessionManager sessions;

void setup()
{
	try
	{
		Serial.begin(115200);

		if (!SD.begin())
			throw std::runtime_error("cannot initialise SD");

		if (SD.exists("/sessions.db"))
			SD.remove("/sessions.db");

		sessions.open("/sd/sessions.db");
	}
	catch (const std::exception &e)
	{
		Serial.println(e.what());
		while (true)
			;
	}
}

void loop()
{
	try
	{
		createSession();
		createSession();
		deleteSession();
		checkSession();
	}
	catch (const std::exception &e)
	{
		Serial.println(e.what());
	}
}

void createSession()
{
	Serial.println(__func__);

	Serial.println("username:");
	while (!Serial.available())
		;
	String username = Serial.readString();

	Serial.println("ip:");
	while (!Serial.available())
		;
	uint32_t ip = Serial.parseInt();

	Serial.println(sessions.newSession(username, ip));
}

void deleteSession()
{
	Serial.println(__func__);

	Serial.println("session id:");
	while (!Serial.available())
		;
	String sessionId = Serial.readString();

	sessions.terminateSession(sessionId);
}

void checkSession()
{
	Serial.println(__func__);

	Serial.println("session id:");
	while (!Serial.available())
		;
	String sessionId = Serial.readString();

	Serial.println(sessions.getSessionData(sessionId));
}