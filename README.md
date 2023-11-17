# Origins
**pico-c** is a project created by Zik at [https://code.google.com/p/picoc](https://code.google.com/p/picoc/ "Google code").
The projet is now hosted at [https://gitlab.com/zsaleeba/picoc](https://gitlab.com/zsaleeba/picoc/ "Github.com"). 

**pico-c** intends to be a very light **C** interpreter. **pico-c** is very small, but include many standard libraries.

# The content
Initially those libraries were natively integrated into pico-c:

* ctype.h
* errno.h
* math.h
* stdbool.h
* stdio.h
* stdlib.h
* string.h
* time.h
* unistd.h

Some of them were improved:

* stdio.h
* unistd.h

We have planned to add support for 3 other useful libraries:

* dirent.h
* regex.h
* socket.h
* stat.h

# The pico-c syntax

```
$ pico-c -h
pico-c.exe, A very small C interpreter
Usage: pico-c.exe [-h] [-i] [-m] [-n] [-o] [<filename1>...] [- <arg1>...]
        -h: this help message
        -i: force interactive mode at the end of scripts
        -m: run main() function automaticaly
        -n: don't print prompt
        -o: the original "old" mode
        -v: print version
Exemples:
        pico-c.exe script1.pcc script2.pcc
        pico-c.exe -i script.pcc
        pico-c.exe -m script1.pcc script2.pcc - arg1 agr2
```


**Cyd**
