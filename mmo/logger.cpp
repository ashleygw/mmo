#include "logger.h"
#include <chrono>
#include <iomanip>

std::fstream Logger::Notification()
{
  std::fstream file("generated/logger_notifications.log", std::ios_base::app);
  file << std::endl;
  file << "********************************************************" << std::endl;
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  file << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << std::endl;
  //add the time
  return file;
}
std::fstream Logger::Warning()
{
  std::fstream file("generated/logger_warnings.log", std::ios_base::app);
  file << std::endl;
  file << "********************************************************" << std::endl;
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  file << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << std::endl;
  //add the time
  return file;
}