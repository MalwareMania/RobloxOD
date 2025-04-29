#include <Windows.h>
#include <cstdint>
#include <vector>

class CScheduler {
private:
    uintptr_t Address = 0;
    std::vector<uintptr_t> Jobs;

public:
    uintptr_t gettaskscheduler()
    {
        uintptr_t pid = process->get_process_id();
        uintptr_t base = process->get_module_base(pid);
        return memory->read<uintptr_t>(base + Offsets::RawScheduler);
    }

    uintptr_t getjobname(const std::string jobName)
    {
        uintptr_t task = this->gettaskscheduler();
        uintptr_t jobStart = memory->read<uintptr_t>(task + Offsets::TaskScheduler::JobStart);
        uintptr_t jobEnd = memory->read<uintptr_t>(task + Offsets::TaskScheduler::JobEnd);
        for (uintptr_t i = jobStart; i < jobEnd; i += 0x10) {
            uintptr_t job = memory->read<uintptr_t>(i);
            if (!job) continue;

            uintptr_t ptr = memory->read<uintptr_t>(job + Offsets::TaskScheduler::JobName);
            std::string name = memory->read_string_unknown(ptr);

            if (name == jobName) {
                return job;
            }
        }
    }
    uintptr_t getdatamodel()
    {
        uintptr_t pid = process->get_process_id();
        uintptr_t base = process->get_module_base(pid);
        uintptr_t fakedm = memory->read<uintptr_t>(base + Offsets::DataModel::FakeDataModelPointer);
        return memory->read<uintptr_t>(fakedm + Offsets::DataModel::FakeDataModelToDataModel);
    }

    auto gethumanoid() -> uintptr_t
    {
        uintptr_t datamodel = this->getdatamodel();
        uintptr_t players = rbx->findfirstchild(datamodel, "Players");
        uintptr_t localplayer = memory->read<uintptr_t>(players + Offsets::LocalPlayer);
        uintptr_t character = memory->read<uintptr_t>(localplayer + Offsets::ModelInstance);
        return rbx->findfirstchild(character, "Humanoid");
    }

    uintptr_t set_walkspeed(float speed)
    {
        uintptr_t humanoid = gethumanoid();
        memory->write<float>(humanoid + Offsets::WalkSpeed, speed);
        memory->write<float>(humanoid + Offsets::WalkSpeedCheck, speed);

        return humanoid;
    }

    std::vector<uintptr_t> getplayerlist()
    {
        uintptr_t datamodel = this->getdatamodel();
        uintptr_t players = rbx->findfirstchild(datamodel, "Players");
        return rbx->getchildren(players);
    }

    uintptr_t getscriptcontext()
    {
        uintptr_t dm = getdatamodel();
        uintptr_t child = memory->read<uintptr_t>(memory->read<uintptr_t>(dm + Offsets::Children));
        uintptr_t context = memory->read<uintptr_t>(child + Offsets::ScriptContext);
        return context;
    }
    
    uintptr_t getrenderview()
    {
        uintptr_t dm = this->getdatamodel();
        uintptr_t rv = memory->read<uintptr_t>(dm + Offsets::DataModel::DataModelToRenderView1);
        uintptr_t rv1 = memory->read<uintptr_t>(rv + Offsets::DataModel::DataModelToRenderView2);
        return memory->read<uintptr_t>(rv1 + Offsets::DataModel::DataModelToRenderView3);
    }

    uintptr_t gethumanoidrootpart()
    {
        uintptr_t datamodel = this->getdatamodel();
        uintptr_t players = rbx->findfirstchild(datamodel, "Players");
        uintptr_t localplayer = memory->read<uintptr_t>(players + Offsets::LocalPlayer);
        uintptr_t character = memory->read<uintptr_t>(localplayer + Offsets::ModelInstance);
        return rbx->findfirstchild(character, "HumanoidRootPart");
    }
};

auto scheduler = std::make_unique<CScheduler>();
