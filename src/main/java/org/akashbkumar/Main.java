package org.akashbkumar;

import org.akashbkumar.jni.EventLogReader;

public class Main
{
    public static void main(String[] args) throws InterruptedException
    {
        EventLogReader eventLogReader = new EventLogReader();
        eventLogReader.getLogs("Setup");
        //Thread.sleep(Long.MAX_VALUE);
    }
}