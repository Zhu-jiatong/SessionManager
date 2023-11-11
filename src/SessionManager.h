#if !defined(_SessionManager_h)
#define _SessionManager_h

#include <Arduino.h>
#include <Arduino_JSON.h>
#include <DatabaseConnection.h>

class SessionManager
{
public:
	SessionManager() = default;
	~SessionManager() = default;

	void open(const String &dbPath);
	String newSession(const String &username, uint32_t ip);
	void terminateSession(const String &sessionId);
	String getUsername(const String &sessionId);

private:
	DatabaseConnection _db;

	String generateSessionId(const String &username, uint32_t ip);
};

#endif // _SessionManager_h
