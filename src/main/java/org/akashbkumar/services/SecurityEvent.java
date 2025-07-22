package org.akashbkumar.services;

import org.akashbkumar.dao.DatabaseOperations;
import org.akashbkumar.model.Event;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class SecurityEvent
{
    private static final BlockingQueue<Event> securityEventsQueue = new LinkedBlockingDeque<>();

    public static void addSecurityToSecurityEventsQueue(Event event)
    {
        securityEventsQueue.add(event);
    }
    static
    {
        Thread consumerThread = new Thread(()->{
           try
           {
               while (true)
               {
                   Event event = securityEventsQueue.take();
                   DatabaseOperations.insertEventIntoDatabase("security",event);
               }
           }
           catch (Exception exception)
           {
               exception.printStackTrace();
           }
        });
    }
}
