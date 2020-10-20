#! /usr/bin/env python

import threading

CONTADOR = 0
THREADNUM = 5
ADDNUM = 50000

def thread():
  global CONTADOR
  for i in range(0,ADDNUM):
    CONTADOR = CONTADOR + 1

def main():
  threads = []
  for i in range(0,THREADNUM):
    threads.append(threading.Thread(target=thread))
    threads[-1].start()

  for t in threads:
    t.join()

  print(CONTADOR)

if __name__ == "__main__":
  main()
