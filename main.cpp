#include <iostream>

template<typename TLoggerImpl>
concept LoggerLike = requires(TLoggerImpl log)
{
    log.LogDebug(std::string_view{});
    log.LogInfo(std::string_view{});
    log.LogError(std::string_view{});
};

template<LoggerLike TLoggerImpl>
struct Logger : TLoggerImpl
{
};

struct CustomLoggerImpl
{
    static void LogDebug(std::string_view message)
    {
        std::cout << "[Debug] " << message << '\n';
    }
    static void LogInfo(std::string_view message)
    {
        std::cout << "[Info] " << message << '\n';
    }
    static void LogError(std::string_view message)
    {
        std::cout << "[Error] " << message << '\n';
    }
};

struct TestLoggerImpl
{
    static void LogDebug(std::string_view message) {}
    static void LogInfo(std::string_view message) {}
    static void LogError(std::string_view message) {}
};

using CustomLogger = Logger<CustomLoggerImpl>;
using TestLogger = Logger<TestLoggerImpl>;

template<LoggerLike TLogger>
void LogToAll(TLogger &logger, std::string_view message)
{
    logger.LogDebug(message);
    logger.LogInfo(message);
    logger.LogError(message);
}

int main()
{
    CustomLogger custom_logger;
    LogToAll(custom_logger, "Hello World");

    TestLogger test_logger;
    LogToAll(test_logger, "Hello World");

    return 0;
}
