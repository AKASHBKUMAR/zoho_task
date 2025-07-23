#include <windows.h>
#include <winevt.h>
#include <jni.h>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Event.h"
#include "tinyxml2.h"

#pragma comment(lib, "wevtapi.lib")


using namespace tinyxml2;
std::mutex jvmMutex;
JavaVM* genv = nullptr;


std::wstring toWString(const char* str) {
    if (!str) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    std::wstring wstr(size_needed-1, 0);
    MultiByteToWideChar(CP_UTF8, 0, str, -1, &wstr[0], size_needed);
    return wstr;
}

std::string toUtf8(const wchar_t* wideStr)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    std::string result(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, &result[0], size, nullptr, nullptr);
    return result;
}

std::string toString(const std::wstring& wstr) {
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, NULL, NULL);
    std::string str(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, NULL, NULL);
    return str;
}

jobject createJavObject (Event event)
{
    JNIEnv* createEnv;
    jint result = genv->GetEnv((void**)&createEnv, JNI_VERSION_1_6);
    // Handle detached threads
    if (result == JNI_EDETACHED) {
        result = genv->AttachCurrentThread((void**)&createEnv, nullptr);
    }

    // Check for errors
    if (result != JNI_OK || !createEnv) {
        std::wcerr << L"Failed to get JNI environment" << std::endl;
        return nullptr;
    }

    jclass eventJavaClass = createEnv->FindClass("org/akashbkumar/model/Event");
    jmethodID javaconstructor = createEnv->GetMethodID(eventJavaClass,"<init>","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    if(javaconstructor == nullptr)
    {
        std::wcout<<"Cannot Find the Java Constructor"<<std::endl;
    }
    jstring logName = createEnv->NewStringUTF(event.getProviderName().c_str());
    jstring eventID = createEnv -> NewStringUTF(event.getEventID().c_str());
    jstring version = createEnv -> NewStringUTF(event.getVersion().c_str());
    jstring opcode = createEnv -> NewStringUTF(event.getOpcode().c_str());
    jstring level = createEnv -> NewStringUTF(event.getLevel().c_str());
    jstring timeCreated = createEnv -> NewStringUTF(event.getTimeCreated().c_str());
    jstring keywords = createEnv -> NewStringUTF(event.getKeywords().c_str());
    jstring eventRecordId = createEnv -> NewStringUTF(event.getEventRecordID().c_str());
    jstring channel = createEnv -> NewStringUTF(event.getChannel().c_str());
    jstring computer = createEnv -> NewStringUTF(event.getComputer().c_str());

    jobject javaEventObject = createEnv -> NewObject(eventJavaClass, javaconstructor,logName,eventID, version, opcode, level,timeCreated, keywords, eventRecordId, channel, computer);

    if(javaEventObject == nullptr)
    {
        std::wcout<<"Error in the Java Event Object"<<std::endl;
    }
    return javaEventObject;
}

void SendEventToJava(Event event)
{
    jobject javaEventObject = createJavObject(event);
    JNIEnv* createEnv;
    jint result = genv->GetEnv((void**)&createEnv, JNI_VERSION_1_6);
    // Handle detached threads
    if (result == JNI_EDETACHED)
    {
        result = genv->AttachCurrentThread((void**)&createEnv, nullptr);
    }

        // Check for errors
    if (result != JNI_OK || !createEnv)
    {
        std::wcerr << L"Failed to get JNI environment" << std::endl;
        return;
    }

    jclass javaEventDispatcherClass = createEnv-> FindClass("org/akashbkumar/services/EventDispatcher");
    if(javaEventDispatcherClass == nullptr)
    {
        std::wcout<<"Not found the eventDispacther class of java"<<std::endl;
    }
    jmethodID javaEventDispatcherMethodId = createEnv -> GetStaticMethodID(javaEventDispatcherClass, "addItemToEventDispatcherQueue","(Lorg/akashbkumar/model/Event;)V");
    if(javaEventDispatcherMethodId == nullptr)
    {
        std::wcout<<"Cannot the find event dispatcher method"<<std::endl;
    }
    createEnv->CallStaticVoidMethod(javaEventDispatcherClass, javaEventDispatcherMethodId,javaEventObject);

}

// parse XML and convert it to CPP Event Object
int parseXMLandRetrieveData(const char* xml)
{
    Event event;
    if (!xml || !*xml) {
        std::cerr << "Error: Empty or null XML input\n";
        return 1;
    }

    tinyxml2::XMLDocument doc;
    XMLError result = doc.Parse(xml);
    if (result != XML_SUCCESS) {
        std::cerr << "Failed to parse XML: " << doc.ErrorStr() << "\n";
        return 1;
    }

    const XMLElement* root = doc.RootElement();
    if (!root) {
        std::cerr << "Error: No root element found\n";
        return 1;
    }

    // Helper lambda for safe text/attribute access
    auto safeGet = [](const XMLElement* elem, const char* name, const char* defaultValue = "") {
        if (!elem) return defaultValue;
        const XMLAttribute* attr = elem->FindAttribute(name);
        return attr ? attr->Value() : defaultValue;
    };

    auto safeText = [](const XMLElement* elem, const char* defaultValue = "") {
        return elem && elem->GetText() ? elem->GetText() : defaultValue;
    };

    const XMLElement* system = root->FirstChildElement("System");
    if (system)
    {
        const XMLElement* provider = system->FirstChildElement("Provider");
        event.setProviderName(safeGet(provider, "Name", "N/A"));

        const XMLElement* eventID = system->FirstChildElement("EventID");
        event.setEventID(safeText(eventID));

        const XMLElement* version = system->FirstChildElement("Version");
        event.setVersion(safeText(version));

        const XMLElement* opcode = system->FirstChildElement("Opcode");
        event.setOpcode(safeText(opcode));

        const XMLElement* level = system->FirstChildElement("Level");
        event.setLevel(safeText(level));

        const XMLElement* time = system->FirstChildElement("TimeCreated");
        event.setTimeCreated(safeGet(time, "SystemTime", "N/A"));

        const XMLElement* keywords = system->FirstChildElement("Keywords");
        event.setKeywords(safeText(keywords));

        const XMLElement* eventRecordId = system->FirstChildElement("EventRecordID");
        event.setEventRecordID(safeText(eventRecordId));

        const XMLElement* channel = system->FirstChildElement("Channel");
        event.setChannel(safeText(channel));

        const XMLElement* computer = system->FirstChildElement("Computer");
        event.setComputer(safeText(computer));
    }
    //event.print();
    SendEventToJava(event);
    return 0;
}

DWORD WINAPI EventCallback(EVT_SUBSCRIBE_NOTIFY_ACTION action, PVOID context, EVT_HANDLE event)
{

    //std::wcout<<"Executing the call back function"<<std::endl;
    if(action != EvtSubscribeActionDeliver || event == nullptr)
    {
        return 0;
    }
    DWORD bufferUsed = 0;
    DWORD propertyCount = 0;

    EvtRender(NULL, event, EvtRenderEventXml, 0, NULL, &bufferUsed, &propertyCount);
    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    {
        std::wcerr << L"EvtRender size error: " << GetLastError() << std::endl;
        return 0;
    }

    std::vector<wchar_t> buffer(bufferUsed / sizeof(wchar_t));

    if (!EvtRender(NULL, event, EvtRenderEventXml, bufferUsed, buffer.data(), &bufferUsed, &propertyCount))
    {
        std::wcerr << L"EvtRender render error: " << GetLastError() << std::endl;
        return 0;
    }

    std::string xmlUtf8 = toUtf8(buffer.data());
    parseXMLandRetrieveData(xmlUtf8.c_str());

    return 0;
}
//Get ALl data from the Windows Event API
void getHistoricalData(const char* channelName)
{
    std::wstring wChannelName = toWString(channelName);
    EVT_HANDLE eventQuery = EvtQuery(NULL, wChannelName.c_str(), L"*",EvtQueryForwardDirection | EvtQueryChannelPath);
    if(eventQuery == nullptr)
    {
        std::wcout<<"Event Query failed"<<GetLastError()<<std::endl;
        return;
    }
    const int chunkSize = 64;
    EVT_HANDLE events[chunkSize];
    DWORD returned = 0;
    int count = 0;
    while(true)
    {
        if(EvtNext(eventQuery, chunkSize, events, INFINITE, 0, &returned))
        {
            DWORD lastError = GetLastError();
            if(lastError == ERROR_NO_MORE_ITEMS)
            {
                std::wcout<<"Reached End Of Logs";
                break;
            }
        }
        for(DWORD iterator = 0; iterator<returned; iterator++)
        {
            DWORD bufferUsed = 0;
            DWORD propertyCount = 0;
            if(!EvtRender(NULL, events[iterator], EvtRenderEventXml, 0, NULL, &bufferUsed, &propertyCount))
            {
                if(GetLastError() == ERROR_INSUFFICIENT_BUFFER)
                {
                    std::vector<wchar_t> buffer (bufferUsed/sizeof(wchar_t));
                    if(EvtRender(NULL,events[iterator], EvtRenderEventXml, buffer.size() * sizeof(wchar_t), buffer.data(),&bufferUsed,&propertyCount))
                    {
                        std::string xmlUtf8 = toUtf8(buffer.data());
                        parseXMLandRetrieveData(xmlUtf8.c_str());
                    }
                }
            }
        }
    }
    for(DWORD i = 0; i<returned; i++)
    {
        if(events[i] != NULL)
        {
            EvtClose(events[i]);
        }
    }
    EvtClose(eventQuery);
}
void SubscribeToChannel(const char* channelName)
{
    std::wcout<<"subscribing to "<<toWString(channelName).c_str()<<"--------------"<<std::endl;
    EVT_HANDLE sub = EvtSubscribe(NULL, NULL, toWString(channelName).c_str(), NULL, NULL, (PVOID)&channelName, (EVT_SUBSCRIBE_CALLBACK)EventCallback, EvtSubscribeToFutureEvents );
    if (!sub)
    {
        std::wcerr << L"Failed to subscribe to: " << channelName << std::endl;
    }

}

extern "C" JNIEXPORT void JNICALL Java_org_akashbkumar_jni_EventLogReader_getLogs(JNIEnv* env, jobject, jstring channel)
{
    env->GetJavaVM(&genv);
    const char* ch = env->GetStringUTFChars(channel, NULL);
    SubscribeToChannel(ch);
    getHistoricalData(ch);
}
