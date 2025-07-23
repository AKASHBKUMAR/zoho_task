package org.akashbkumar.services;

import org.akashbkumar.model.*;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;

@SuppressWarnings("ALL")
public class EventDispatcher
{
    private static final BlockingQueue<Event> eventQueue = new LinkedBlockingQueue<>();
    static
    {
        Thread consumerThread = new Thread(() ->
        {
            try
            {
                while (true)
                {
                    Event event = eventQueue.take(); // Waits if empty
                    dispatch(event);
                }
            }
            catch (InterruptedException e)
            {
                Thread.currentThread().interrupt();
                System.err.println("EventDispatcher thread interrupted.");
            }
        });
        consumerThread.setDaemon(true);
        consumerThread.start();
    }
    public static void addItemToEventDispatcherQueue(Event event)
    {
        eventQueue.add(event);
    }
    public static void dispatch(Event event)
    {
        String channel = event.getChannel();
        if("Application".equals(channel))
        {
            ApplicationEvent.addEventToApplicationBlockingQueue(event);
        }
        else if ("System".equalsIgnoreCase(channel))
        {
            SystemEvent.addEventToSystemEventsQueue(event);
        }
        else if ("Setup".equals(channel))
        {
            SetupEvents.addEventToSetupQueue(event);
        }
        else if ("Security".equals(channel))
        {
            SecurityEvent.addSecurityToSecurityEventsQueue(event);
        }
        else if(channel.equals("ForwardedEvents"))
        {
            ForwardedEvents.addEventToForwardedEventsQueue(event);
        }
    }

}
