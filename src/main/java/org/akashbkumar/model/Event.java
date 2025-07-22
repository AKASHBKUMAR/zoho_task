package org.akashbkumar.model;

@SuppressWarnings("ALL")
public class Event
{
    private String logName;
    private String eventID;
    private String version;
    private String opcode;
    private String level;
    private String timeCreated;
    private String keywords;
    private String eventRecordId;
    private String channel;
    private String computer;

    public String getLogName() {
        return logName;
    }

    public void setLogName(String logName) {
        this.logName = logName;
    }

    public String getEventID() {
        return eventID;
    }

    public void setEventID(String eventID) {
        this.eventID = eventID;
    }

    public String getVersion() {
        return version;
    }

    public void setVersion(String version) {
        this.version = version;
    }

    public String getOpcode() {
        return opcode;
    }

    public void setOpcode(String opcode) {
        this.opcode = opcode;
    }

    public String getLevel() {
        return level;
    }

    public void setLevel(String level) {
        this.level = level;
    }

    public String getTimeCreated() {
        return timeCreated;
    }

    public void setTimeCreated(String timeCreated) {
        this.timeCreated = timeCreated;
    }

    public String getKeywords() {
        return keywords;
    }

    public void setKeywords(String keywords) {
        this.keywords = keywords;
    }

    public String getEventRecordId() {
        return eventRecordId;
    }

    public void setEventRecordId(String eventRecordId) {
        this.eventRecordId = eventRecordId;
    }

    public String getChannel() {
        return channel;
    }

    public void setChannel(String channel) {
        this.channel = channel;
    }

    public String getComputer() {
        return computer;
    }

    public void setComputer(String computer) {
        this.computer = computer;
    }

    public Event() {
    }

    public Event(String logName, String eventID, String version, String opcode, String level, String timeCreated, String keywords, String eventRecordId, String channel, String computer) {
        this.logName = logName;
        this.eventID = eventID;
        this.version = version;
        this.opcode = opcode;
        this.level = level;
        this.timeCreated = timeCreated;
        this.keywords = keywords;
        this.eventRecordId = eventRecordId;
        this.channel = channel;
        this.computer = computer;
    }

    @Override
    public String toString() {
        return "Event{" +
                "logName='" + logName + '\'' +
                ", eventID='" + eventID + '\'' +
                ", version='" + version + '\'' +
                ", opcode='" + opcode + '\'' +
                ", level='" + level + '\'' +
                ", timeCreated='" + timeCreated + '\'' +
                ", keywords='" + keywords + '\'' +
                ", eventRecordId='" + eventRecordId + '\'' +
                ", channel='" + channel + '\'' +
                ", computer='" + computer + '\'' +
                '}';
    }
}
