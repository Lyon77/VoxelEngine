#pragma once
#include "Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Voxel
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

//Core Log Macros
#define VL_CORE_CRITICAL(...)  ::Voxel::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define VL_CORE_ERROR(...)  ::Voxel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VL_CORE_WARN(...)   ::Voxel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VL_CORE_INFO(...)   ::Voxel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VL_CORE_TRACE(...)  ::Voxel::Log::GetCoreLogger()->trace(__VA_ARGS__)

//Client Log Macros
#define VL_CRITICAL(...)		::Voxel::Log::GetClientLogger()->critical(__VA_ARGS__)
#define VL_ERROR(...)		::Voxel::Log::GetClientLogger()->error(__VA_ARGS__)
#define VL_WARN(...)		::Voxel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VL_INFO(...)		::Voxel::Log::GetClientLogger()->info(__VA_ARGS__)
#define VL_TRACE(...)		::Voxel::Log::GetClientLogger()->trace(__VA_ARGS__)