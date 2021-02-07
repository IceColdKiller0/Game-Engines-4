#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <iostream>
#include <string>
#include <fstream>

class Debugger
{
public:
	enum class MessageType : unsigned short
	{
		TYPE_NONE = 0,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};

	Debugger() = delete;
	Debugger(const Debugger&) = delete;
	Debugger(Debugger&&) = delete;
	Debugger& operator=(const Debugger&) = delete;
	Debugger& operator=(Debugger&&) = delete;

	static void OnCreate(const std::string& name_ = "GAME_ENGINE_4_LOG");
	static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_, const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void Error(const std::string& message_, const std::string& fileName_, const int line_);
	static void FatalError(const std::string& message_, const std::string& fileName_, const int line_);

private:
	static void Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_); //writes to external file
	static MessageType currentSev;
	static std::string outputName; // holds output name
};

#endif;

