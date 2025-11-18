```bash
gcc main.cpp -lstdc++
```

```bash
ehab@HP:~/Documents/ITI_9Months/CPP$ ls -la /usr/lib/gcc/x86_64-linux-gnu/11/ | grep libstdc++
-rw-r--r-- 1 root root  6018836 Apr 22  2025 libstdc++.a
-rw-r--r-- 1 root root   683830 Apr 22  2025 libstdc++fs.a
lrwxrwxrwx 1 root root       40 Apr 22  2025 libstdc++.so -> ../../../x86_64-linux-gnu/libstdc++.so.6
```



### **Why `-lstdc++` is used**

Because you’re using `gcc`, which **does not auto-link** the C++ standard library.
 So you must manually link it:

- `-lstdc++` = link against the C++ standard library (`libstdc++.so`)



### **What `-static-libstdc++` Means**

This flag tells the linker:

> "Do not use the shared (dynamic) libstdc++.so.
>  Instead, embed the entire C++ standard library inside the executable."



### Why use static linking?

✔ No need to install libstdc++ on the target system
✔ Executable is fully self-contained
✔ Good for embedded systems, servers, containers

### Why NOT use static linking?

✘ Executable becomes much larger
✘ Some Linux distros discourage it
✘ Harder to update for security vulnerabilities

##### Example:

```bash
g++ main.cpp -static-libstdc++ -static-libgcc
```



### To write c++ code in c fike

 from what I can tell, gcc does consider a `.C` (capital) extension a c++ extension. The following works just fine: `gcc test.C -lstdc++ -o test` or `g++ test.C -o test`.