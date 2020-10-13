package javap2;


public class Main {
  final static int MAX = 10;

  final static void print(String text) {
    for (int i=0; i<MAX; i++) { System.out.println(text); }
  }
  

  private class Hilo extends Thread {
    private String text;

    public Hilo(String text) { this.text = text; }

    public void run() { Main.print(text); }
  }

  private class Ejecutable implements Runnable {
    private String text;

    public Ejecutable(String text) { this.text = text; }

    public void run() { Main.print(text); }
  }

  public static void main(String[] args) {
    Thread hilo = new Hilo("Soy el hilo.");
    Thread ejec = new Thread(new Ejecutable("Soy el ejecutable."));

    System.out.println("Hewwo :3c");
  }
}
