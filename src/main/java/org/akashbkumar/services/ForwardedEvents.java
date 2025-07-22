package org.akashbkumar.services;

import org.akashbkumar.dao.DatabaseOperations;
import org.akashbkumar.model.Event;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class ForwardedEvents
{
    private static final BlockingQueue<Event> forwardedEventsQueue = new LinkedBlockingDeque<>();

    public static void addEventToForwardedEventsQueue(Event event)
    {
        forwardedEventsQueue.add(event);
    }
    static
    {
        Thread consumerThread = new Thread(()->{
            try
            {
                while (true)
                {
                    Event event = forwardedEventsQueue.take();
                    DatabaseOperations.insertEventIntoDatabase("forwarded_events",event);
                }
            }
            catch (Exception exception)
            {
                exception.printStackTrace();
            }
        });
    }
}
