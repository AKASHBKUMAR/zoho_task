package org.akashbkumar.services;

import org.akashbkumar.dao.DatabaseOperations;
import org.akashbkumar.model.Event;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class SetupEvents
{
    private static final BlockingQueue<Event> setupQueue = new LinkedBlockingDeque<>();

    public static void addEventToSetupQueue(Event event)
    {
        setupQueue.add(event);
    }
    static
    {
        Thread consumerThread = new Thread(()-> {
            try
            {
                while(true)
                {
                    Event event = setupQueue.take();
                    DatabaseOperations.insertEventIntoDatabase("setup",event);
                }
            }
            catch (Exception exception)
            {
                exception.printStackTrace();
            }
        });
    }
}
