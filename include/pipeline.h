#include <cinttypes>

using module_t = uint8_t;

namespace Modules
{
const module_t JsonConverter     = 0b00000001;
const module_t PickleConverter   = 0b00000010;
const module_t FileChecker       = 0b00000100;
const module_t AddrChecker       = 0b00001000;
const module_t CompileRunner     = 0b00010000;
const module_t ProgramComparator = 0b00100000;
const module_t ProgramRunner     = 0b01000000;
}

namespace PipelineConstants
{
    const module_t InitPipeline = 0b00000000;
}

class Pipeline
{
public:
    explicit Pipeline();
    ~Pipeline();
    void setModule(module_t);
    bool isModuleExists(module_t) const;
    void operator=(const Pipeline&);
private:
    module_t pipeline;
    void setModuleBit(const module_t&);
    module_t getModuleBit(const module_t&) const;
};