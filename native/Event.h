#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <vector>

class Event
{
    private:
        std::string providerName;
        std::string eventID;
        std::string version;
        std::string opcode;
        std::string level;
        std::string timeCreated;
        std::string keywords;
        std::string eventRecordID;
        std::string channel;
        std::string computer;

    public:
        const std::string& getProviderName() const;
        const std::string& getEventID() const;
        const std::string& getVersion() const;
        const std::string& getOpcode() const;
        const std::string& getLevel() const;
        const std::string& getTimeCreated() const;
        const std::string& getKeywords() const;
        const std::string& getEventRecordID() const;
        const std::string& getChannel() const;
        const std::string& getComputer() const;

        void setProviderName(const std::string& name);
        void setEventID(const std::string& id);
        void setVersion(const std::string& ver);
        void setOpcode(const std::string& code);
        void setLevel(const std::string& lvl);
        void setTimeCreated(const std::string& time);
        void setKeywords(const std::string& kw);
        void setEventRecordID(const std::string& id);
        void setChannel(const std::string& ch);
        void setComputer(const std::string& comp);

    void print() const;
};

#endif