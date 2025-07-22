#include "Event.h"
// getters completed
const std::string& Event::getProviderName() const { return providerName; }
const std::string& Event::getEventID() const { return eventID; }
const std::string& Event::getVersion() const { return version; }
const std::string& Event::getOpcode() const { return opcode; }
const std::string& Event::getLevel() const { return level; }
const std::string& Event::getTimeCreated() const { return timeCreated; }
const std::string& Event::getKeywords() const {return keywords;}
const std::string& Event::getEventRecordID() const { return eventRecordID;}
const std::string& Event::getChannel() const { return channel; }
const std::string& Event::getComputer() const { return computer; }


void Event::setProviderName(const std::string& name) { providerName = name; }
void Event::setEventID(const std::string& id) { eventID = id; }
void Event::setVersion(const std::string& ver) { version = ver; }
void Event::setOpcode(const std::string& code) { opcode = code; }
void Event::setLevel(const std::string& lvl) { level = lvl; }
void Event::setTimeCreated(const std::string& time) { timeCreated = time; }
void Event::setKeywords(const std::string& kw) { keywords = kw; }
void Event::setEventRecordID(const std::string& id) { eventRecordID = id; }
void Event::setChannel(const std::string& ch) { channel = ch; }
void Event::setComputer(const std::string& comp) { computer = comp; }


void Event::print() const {
    std::cout << "Provider: " << providerName << "\n";
    std::cout << "Event ID: " << eventID << "\n";
    std::cout << "Version: " << version << "\n";
    std::cout << "Opcode: " << opcode << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Time Created: " << timeCreated << "\n";
    std::cout << "Keywords: " << keywords << "\n";
    std::cout << "EventRecordID: " << level << "\n";
    std::cout << "Channel: " << channel << "\n";
    std::cout << "Computer: " << computer << "\n";

}