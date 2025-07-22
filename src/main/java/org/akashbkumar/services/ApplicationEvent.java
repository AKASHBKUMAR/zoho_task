package org.akashbkumar.services;

import org.akashbkumar.dao.DatabaseOperations;
import org.akashbkumar.model.Event;

import java.sql.SQLException;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;

public class ApplicationEvent
{
    private static final BlockingQueue<Event> applicationQueue = new LinkedBlockingDeque<>();

    public static void addEventToApplicationBlockingQueue(Event event)
    {
        applicationQueue.add(event);
    }
    static
    {
        Thread consumerThread = new Thread(()->
        {
            try
            {
                while (true)
                {
                    Event event = applicationQueue.take();
                    System.out.println(event);
                    DatabaseOperations.insertEventIntoDatabase("application",event);
                }
            } catch (InterruptedException  | SQLException e)
            {
                throw new RuntimeException(e);
            }
        });
        consumerThread.setDaemon(true);
        consumerThread.start();
    }
}
