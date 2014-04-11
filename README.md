ESHcript
========

ESHcript is an interpreted Lisp programming language developed by Eli S. Hickox, hence the name "ESHcript".

Makes use of the [mpc Parser Combinator library](https://github.com/orangeduck/mpc) for C.

This is not intended to be a full-scale, production level, programming language. A language is only as good as the library that surounds it. This is just a personal pet project that I have been tinkering with for a while.

To install:

  1) Clone the git repository
  
  2) cc -std=c99 -Wall prompt.c mpc.c -ledit -lm -o prompt 
  
Currently only supported on OS X. 

WARNING: This is experimental, pre-alpha software. I am not responsible for what this does to your computer.
