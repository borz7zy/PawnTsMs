#include <sdk.hpp>
#include <Server/Components/Pawn/pawn.hpp>
#include <Server/Components/Pawn/Impl/pawn_natives.hpp>
#include <Server/Components/Pawn/Impl/pawn_impl.hpp>

#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

class PawnTsMs final : public IComponent, public PawnEventHandler
{
private:
    ICore* core_ = nullptr;
    IPawnComponent* pawn_ = nullptr;
public:
    PROVIDE_UID(0xB304B1488BAE5EA3);
    SemanticVersion componentVersion() const override{return SemanticVersion(1,0,0,0);}
    StringView componentName() const override{return "PawnTsMs";}
    ~PawnTsMs(){
        if(pawn_){
            pawn_->getEventDispatcher().removeEventHandler(this);
        }
        if(core_){}
    }
    void onAmxLoad(IPawnScript& script) override{
        pawn_natives::AmxLoad(script.GetAMX());
    }
    void onAmxUnload(IPawnScript& script) override{}
    void onLoad(ICore* c) override{
        core_ = c;
        core_->printLn("PawnTsMs loaded.");
        setAmxLookups(core_);
    }
    void onInit(IComponentList* components) override{
        pawn_ = components->queryComponent<IPawnComponent>();
        if(pawn_){
            setAmxFunctions(pawn_->getAmxFunctions());
            setAmxLookups(components);
            pawn_->getEventDispatcher().addEventHandler(this);
        }
    }
    void onFree(IComponent* component) override{
        if(component == pawn_){
            pawn_ = nullptr;
            setAmxFunctions();
            setAmxLookups();
        }
    }
    void free() override{delete this;}
    void reset() override{}
};
COMPONENT_ENTRY_POINT(){
    return new PawnTsMs();
}

SCRIPT_API(GetTsString, int(OutputOnlyString& myString)){
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto ms = duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    myString = std::to_string(ms.count());
    return 1;
}

SCRIPT_API(GetTsStringFormatted, int(OutputOnlyString& myString)){
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto ms = duration_cast<std::chrono::milliseconds>(now.time_since_epoch())%1000;
    std::tm local_tm = *std::localtime(&time_t_now);
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%d.%m.%Y %H:%M:%S")
        << '.' << std::setw(3) << std::setfill('0') << ms.count();
    myString = oss.str();
    return 1;
}

SCRIPT_API(ParseMyTs, int(const std::string& myTs, OutputOnlyString& myString)){
    const int64_t convertedMyTs= std::stoi(myTs);
    std::chrono::milliseconds ms_since_epoch(convertedMyTs);
    std::chrono::system_clock::time_point tp(ms_since_epoch);
    auto time_t_sec = std::chrono::system_clock::to_time_t(tp);
    auto ms = duration_cast<std::chrono::milliseconds>(tp.time_since_epoch())%1000;
    std::tm tm = *std::localtime(&time_t_sec);
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << tm.tm_mday << "."
        << std::setw(2) << std::setfill('0') << (tm.tm_mon + 1) << "."
        << (tm.tm_year + 1900) << " "
        << std::setw(2) << std::setfill('0') << tm.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << tm.tm_min << ":"
        << std::setw(2) << std::setfill('0') << tm.tm_sec << "."
        << std::setw(3) << std::setfill('0') << ms.count();
    myString = oss.str();
    return 1;
}