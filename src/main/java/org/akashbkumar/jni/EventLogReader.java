package org.akashbkumar.jni;

public class EventLogReader
{
    static
    {
        System.loadLibrary("EventReader");
    }

    public native void getLogs(String logName);
}
