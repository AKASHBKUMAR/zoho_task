package org.akashbkumar.dao;

import org.akashbkumar.model.Event;

import java.sql.*;
import java.time.Instant;

public class DatabaseOperations
{
    private static final String URL = "jdbc:postgresql://localhost/events";
    private static final String USERNAME = "postgres";
    private static  final String PASSWORD = "root";
    private static Connection connection;
    private static final String INSERT_STATEMENT = "INSERT INTO setup (log_name,event_id,version,opcode,level,time_created,keywords,event_record_id,channel,computer) VALUES(?,?,?,?,?,?,?,?,?,?)";
    static
    {
        try
        {
            Class.forName("org.postgresql.Driver");
            connection = DriverManager.getConnection(URL, USERNAME, PASSWORD);

        }
        catch (ClassNotFoundException | SQLException e)
        {
            throw new RuntimeException(e);
        }
    }
    public static void insertEventIntoDatabase(String tableName,Event event) throws SQLException
    {
        PreparedStatement preparedStatement = connection.prepareStatement(INSERT_STATEMENT);
        preparedStatement.setString(1,event.getLogName());
        preparedStatement.setInt(2, Integer.parseInt(event.getEventID()));
        preparedStatement.setInt(3, Integer.parseInt(event.getVersion()));
        preparedStatement.setInt(4, Integer.parseInt(event.getOpcode()));
        preparedStatement.setInt(5, Integer.parseInt(event.getLevel()));
        preparedStatement.setTimestamp(6, Timestamp.from(Instant.parse(event.getTimeCreated())));
        preparedStatement.setString(7,event.getKeywords());
        preparedStatement.setInt(8,Integer.parseInt(event.getEventRecordId()));
        preparedStatement.setString(9, event.getChannel());
        preparedStatement.setString(10,event.getComputer());
        int numberOfRowsUpdated = preparedStatement.executeUpdate();
        System.out.println(numberOfRowsUpdated + " inserted into the table " + event.getChannel());
    }
}
