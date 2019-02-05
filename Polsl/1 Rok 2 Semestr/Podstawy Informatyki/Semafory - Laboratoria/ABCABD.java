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
    private static final int STEP = 6;
    
    private static final Semaphore a = new Semaphore(0, true);
    private static final Semaphore b = new Semaphore(0, true);
    private static final Semaphore c = new Semaphore(0, true);
    private static final Semaphore d = new Semaphore(1, true);
    
    public static void main(String[] args) {
        new A().start();
        new B().start();
        new C().start();
        new D().start();
    }

    private static final class A extends Thread {
        
        @Override
        @SuppressWarnings("SleepWhileInLoop")
        public void run() {
            try {
                for (int i = 0; i < COUNT * 2; i++) {
                    a.acquire();
                    prettyPrint("A ");
                    d.release();
  
                }
            } catch (InterruptedException ex) {}
        }
        
    }
    
    private static final class B extends Thread {
        
        @Override
        @SuppressWarnings("SleepWhileInLoop") 
        public void run() {
            try {
                for (int i = 0; i < COUNT * 2; i++) {
                    b.acquire();
                    prettyPrint("B ");
                    d.release();
                }
            } catch (InterruptedException ex) {}
        }
        
    }
    
    private static final class C extends Thread {
        @Override
        @SuppressWarnings("SleepWhileInLoop")
        public void run() {
            try {
                for (int i = 0; i < COUNT; i++) {
                    c.acquire();
                    prettyPrint("C ");
                    d.release();
                }
            } catch (InterruptedException ex) {}
        }
    }
    
     private static final class D extends Thread {
        @Override
        @SuppressWarnings("SleepWhileInLoop")
        public void run() {
            try {
                for (int i = 0; i < COUNT; i++) {
                    d.acquire();
                    
                    a.release();
                    d.acquire();
                    
                    b.release();
                    d.acquire();
                    
                    c.release();
                    d.acquire();
                    
                    a.release();
                    d.acquire();
                    
                    b.release();
                    
                    
                    prettyPrint("D ");
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
