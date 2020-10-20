package javap2;


public class Main {
  final static int MAX = 10;

  final static void print(String text) {
    for (int i=0; i<MAX; i++) { System.out.println(text); }
  }
  

  private static class Hilo extends Thread {
    private String text;

    public Hilo(String text) { this.text = text; }

    public void run() { Main.print(text); }
  }

  private static class Ejecutable implements Runnable {
    private String text;

    public Ejecutable(String text) { this.text = text; }

    public void run() { Main.print(text); }
  }

  public static void main(String[] args) {
    Thread thread1, thread2;

    if(args.length < 1 || args[0].equals("-h")) {
      thread1 = new Hilo("hilo1");
      thread2 = new Hilo("hilo2");
    } else {
      thread1 = new Thread(new Ejecutable("ejec1"));
      thread2 = new Thread(new Ejecutable("ejec2"));
    }
    thread1.setPriority(1);
    thread1.start();
    thread2.start();
  }
}
