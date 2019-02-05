/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package semaforypilab;

import java.util.concurrent.Semaphore;

/**
 *
 * @author Account
 */
public class SemaforyPILab {
    
    // CBBA
    private static final int COUNT = 30;
    //private static final int DELAY = 5;
    
    private static int COUNTER = 0;
    private static final int STEP = 5;
    
    private static final Semaphore a = new Semaphore(1, true);
    private static final Semaphore b = new Semaphore(0, true);
    private static final Semaphore c = new Semaphore(0, true); 
    
    public static void main(String[] args) {
        new A().start();
        new B().start();
        new C().start();
    }

    private static final class A extends Thread {
        
        @Override
        @SuppressWarnings("SleepWhileInLoop")
        public void run() {
            try {
                for (int i = 0; i < COUNT; i++) {
                    a.acquire();
                    c.release();
                    a.acquire();
                    prettyPrint("A ");
                    b.release(2);
                    a.acquire(2);
                    c.release();
  
                }
            } catch (InterruptedException ex) {}
        }
        
    }
    
    private static final class B extends Thread {
        
        @Override
        @SuppressWarnings("SleepWhileInLoop") 
        public void run() {
            try {
                for (int i = 0; i < COUNT*2; i++) {
                    b.acquire();
                    prettyPrint("B ");
                    a.release();
                }
            } catch (InterruptedException ex) {}
        }
        
    }
    
    private static final class C extends Thread {
        @Override
        @SuppressWarnings("SleepWhileInLoop")
        public void run() {
            try {
                for (int i = 0; i < COUNT*2; i++) {
                    c.acquire();
                    prettyPrint("C ");
                    a.release();
    
                }
            } catch (InterruptedException ex) {}
        }
    }

    
    private static synchronized void prettyPrint(String s) {
        COUNTER++;
        System.out.print(s);
        if (COUNTER == STEP) {
            COUNTER = 0;
            System.out.println();
        }
    }
        
} 
