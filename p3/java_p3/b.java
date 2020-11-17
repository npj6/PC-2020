import java.lang.Math; // para random

public class b extends Thread {
  static int n = 0;
  static volatile int C[] = {0, 0};
  int id1; // identificador del hilo
  int id2; // identificador del otro hilo

  int M = 500;

  public void run() {
    try {
      for(int i=0; i<M; i++){
        while(C[id2] == 1);
        C[id1] = 1;
        //sleep((long) (Math.random()*10));
        n = n + 1;
        // System.out.println("En hilo "+id1+", n = "+n);
        C[id1] = 0;
      }
      System.out.println(n);
    } catch (Exception e) {return;}
  }

  b(int id) {
    this.id1 = id;
    this.id2 = (id == 1)? 0 : 1;
  }

  public static void main(String args[]) {
    Thread thr1 = new b(0);
    Thread thr2 = new b(1);

    thr1.start();
    thr2.start();
  }
}
