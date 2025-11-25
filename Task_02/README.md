### Copy Constructor (Sharing the same FD Pointer "No file reopening")
``` bash
ehab@HP:~/Documents/ITI_9Months/CPP/Task_02$ g++ main.cpp 
ehab@HP:~/Documents/ITI_9Months/CPP/Task_02$ ./a.out 
Opened file: file.txt
Enter 5 characters to write: EhabM 
[WRITE] wrote: EhabM
[READ] read 5 characters: "EhabM"
Copy constructor -> Sharing the same file descriptor pointer
Enter 5 characters to write: 12345
[WRITE] wrote: 12345
[READ] read 5 characters: "EhabM"
Enter 5 characters to write: 12345
[WRITE] wrote: 12345
[READ] read 10 characters: "EhabM12345"
[CLOSED] Closed File
Destroyed fd
Destroyed fd
```
