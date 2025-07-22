package org.akashbkumar.services;

import org.akashbkumar.dao.DatabaseOperations;
import org.akashbkumar.model.Event;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class SystemEvent
{
    private static final BlockingQueue<Event> systemEventsQueue = new LinkedBlockingDeque<>();

    public static void addEventToSystemEventsQueue(Event event)
    {
        systemEventsQueue.add(event);
    }
    static
    {
        Thread consumerThread = new Thread(()->{
            try
            {
                while (true)
                {
                   Event event = systemEventsQueue.take();
                    DatabaseOperations.insertEventIntoDatabase("system",event);
                }
            }
            catch (Exception exception)
            {
                exception.printStackTrace();
            }
        });
    }
}
