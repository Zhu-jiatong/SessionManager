#if !defined(_SessionManager_h)
#define _SessionManager_h

#include <Arduino.h>
#include <Arduino_JSON.h>

class SessionManager
{
public:
	SessionManager();
	~SessionManager();

	void open(const String &dbPath);
	void newSession();
	void terminateSession();
	void updateSession();
	JSONVar getSessionData();

private:
	String generateSessionId();
};

#endif // _SessionManager_h
