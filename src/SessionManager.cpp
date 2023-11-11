#include "SessionManager.h"
#include <mbedtls/sha256.h>
#include <sstream>
#include <iomanip>

void SessionManager::open(const String &path)
{
	_db.open(path);
	_db.execute("CREATE TABLE IF NOT EXISTS sessions (session_id TEXT NOT NULL PRIMARY KEY, username TEXT NOT NULL) WITHOUT ROWID");
}

String SessionManager::newSession(const String &username, uint32_t ip)
{
	String sessionId = generateSessionId(username, ip);
	_db.execute("INSERT INTO sessions VALUES (?, ?)", sessionId, username);
	return sessionId;
}

void SessionManager::terminateSession(const String &sessionId)
{
	_db.execute("DELETE FROM sessions WHERE session_id=?", sessionId);
}

String SessionManager::getUsername(const String &sessionId)
{
	return _db.execute("SELECT username FROM sessions WHERE session_id=?", sessionId)[0]["username"];
}

String SessionManager::generateSessionId(const String &username, uint32_t ip)
{
	uint8_t hashResult[32];
	uint32_t randomNumber = esp_random();
	String inputString = username + ip + randomNumber;

	int error = mbedtls_sha256_ret(
		reinterpret_cast<const uint8_t *>(inputString.c_str()),
		inputString.length(),
		hashResult,
		0);

	if (error)
		throw std::runtime_error("cannot generate session ID");

	std::ostringstream resultBuilder;
	for (auto &&i : hashResult)
		resultBuilder << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(i);

	return resultBuilder.str().c_str();
}