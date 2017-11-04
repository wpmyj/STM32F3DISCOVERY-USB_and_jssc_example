package org.chuck79;

import jssc.*;
import java.util.Scanner;

public class Main {
    private static SerialPort serialPort;
    private static Scanner in = new Scanner(System.in);

    public static void main(String[] args) {
        String[] portNames = SerialPortList.getPortNames();
        System.out.println("Availible ports:");
        for(int i = 0; i < portNames.length; i++){
            System.out.println(portNames[i]);
        }

        serialPort = new SerialPort("COM4"); // yot can change it

        System.out.println("Write hex here (like '55' or '4f': ");
        try {
            serialPort.openPort();
            serialPort.setParams(
                    SerialPort.BAUDRATE_9600,
                    SerialPort.DATABITS_8,
                    SerialPort.STOPBITS_1,
                    SerialPort.PARITY_NONE
            );

            serialPort.addEventListener(new EventListener(), SerialPort.MASK_RXCHAR);

            int num = Integer.parseInt(in.next(), 16);
            while (num != 0x00) {
                System.out.println("Writing: " + num);
                serialPort.writeInt(num);

                num = Integer.parseInt(in.next(), 16);
            }
            serialPort.closePort();
        } catch (SerialPortException e) {
            e.printStackTrace();
        }
    }

    private static class EventListener implements SerialPortEventListener {
        public void serialEvent(SerialPortEvent event) {
            if(event.isRXCHAR() && event.getEventValue() > 0){
                try {
                    int[] data = serialPort.readIntArray();

                    for (int i : data) {
                        System.out.println("Answer:" + i);
                    }

                } catch (SerialPortException ex) {
                    System.out.println(ex);
                }
            }
        }
    }
}
