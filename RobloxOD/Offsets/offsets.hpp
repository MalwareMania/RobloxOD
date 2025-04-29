#include <Windows.h>

// Some of the offsets are not used

namespace Offsets
{
	constexpr uintptr_t Children = 0x80;
	constexpr uintptr_t ChildrenEnd = 0x8;
	constexpr uintptr_t Name = 0x78;
	constexpr uintptr_t LocalPlayer = 0x128;
	constexpr uintptr_t RawScheduler = 0x63BE258;
	constexpr uintptr_t Workspace = 0x180;
	constexpr uintptr_t ModelInstance = 0x2E8;
	constexpr uintptr_t ClassDescriptor = 0x18;
	constexpr uintptr_t WalkSpeed = 0x1D8;
	constexpr uintptr_t WalkSpeedCheck = 0x3B0;
	constexpr uintptr_t ScriptContext = 0x3C0;

	namespace DataModel
	{
		constexpr uintptr_t DataModelToRenderView1 = 0x1D8;
		constexpr uintptr_t DataModelToRenderView2 = 0x8;
		constexpr uintptr_t DataModelToRenderView3 = 0x28;
		constexpr uintptr_t FakeDataModelPointer = 0x63047A8;
		constexpr uintptr_t FakeDataModelToDataModel = 0x1B8;
	}

	namespace TaskScheduler
	{
		constexpr uintptr_t TaskSchedulerPointer = 0x6375108;
		constexpr uintptr_t JobStart = 0x1D0;
		constexpr uintptr_t JobEnd = 0x1D8;
		constexpr uintptr_t JobName = 0x18;
	}

	namespace Engine
	{
		constexpr uintptr_t VisualEnginePointer = 0x61141E8;
		constexpr uintptr_t VisualEngineToDataModel1 = 0x720;
		constexpr uintptr_t VisualEngineToDataModel2 = 0x1B8;
	}
}
