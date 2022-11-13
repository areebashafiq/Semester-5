// this is an implementation of socket programming in java

import java.io.*;
import java.net.*;

// this is the server class
class Server
{
    public static void main(String args[]) throws Exception
    {
        ServerSocket ss = new ServerSocket(2222); // opening port

        Socket s = ss.accept(); // accepts socket and return communication socket
        DataInputStream dis = new DataInputStream(s.getInputStream()); // get input stream
        String str = (String)dis.readUTF(); // convering to string
        System.out.println("message= "+str); // printing message to console

        OutputStream os = s.getOutputStream(); // defining output stream object
        DataOutputStream dos = new DataOutputStream(os); // converting to data output stream
        dos.writeUTF("Hello Client"); // sending message to client

        ss.close();
    }
}

// this is the client class
class Client
{
    public static void main(String args[]) throws Exception
    {
        Socket s = new Socket("localhost",2222); // connecting to server

        OutputStream os = s.getOutputStream(); // defining output stream object
        DataOutputStream dos = new DataOutputStream(os); // converting to data output stream
        dos.writeUTF("Hello Server"); // sending message to server

        DataInputStream dis = new DataInputStream(s.getInputStream()); // get input stream
        String str = (String)dis.readUTF(); // convering to string
        System.out.println("message= "+str); // printing message to console

        s.close();
    }
}