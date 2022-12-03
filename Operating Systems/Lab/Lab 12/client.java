// this file reads a file and sends it to the server

import java.io.*;
import java.net.*;

public class client {
    public static void main(String[] args) throws Exception {
        // create a socket
        Socket s = new Socket("localhost", 6666);
        // create a data output stream
        DataOutputStream dout = new DataOutputStream(s.getOutputStream());
        // create a file input stream
        FileInputStream fin = new FileInputStream(
                "/Users/carbon/Documents/Semester-5/Operating Systems/Lab/Lab 12/numbers.txt");
        // create a buffer
        byte[] buffer = new byte[1024];
        // read the file
        int count;
        while ((count = fin.read(buffer)) > 0) {
            // send the file
            dout.write(buffer, 0, count);
        }
        // close the socket
        s.close();
    }
}