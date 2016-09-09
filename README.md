# aclogger
File logger for the game arma 3

## Installation

### On Windows
- Install [Microsoft Visual C++ Redistributable Packages 2013](https://www.microsoft.com/en-us/download/details.aspx?id=40784)
- Place the logger in your arma3 folder

### On Linux
- Install g++ 32 bits libraries ``` sudo apt-get install gcc-multilib g++-multilib ```
- Place the logger in your arma3 folder

## Utilisation

The extension is called in game with this command : ```"aclogger" callExtension "your_command" ```
Arguments are separated in the string by the "$" symbol , the symbol "|" in string means a file separator
This extension can only write in his folder (thedll/aclogger/) and subdirectories and can only write in .log files

- It has 5 functions who return "true" in case of success , "false" in case of fail or "nil" if nothing is handled :
  - write [function,file,content] : write text in the file
  - log [function,file,content] : log text in the file with this format : "DATE -> TEXT"
  - append [function,file,content] : append text to an existing file
  - clear [function,file] : clear the content of the file
  - removeFile [function,file] : remove the file

### example :
```sqf
"aclogger" callExtension "version";                             //return the actual version ("1.1")
"aclogger" callExtension "write$file.log$content";              //overrides the file and add the text "content"
"aclogger" callExtension "append$file.log$another content";     //add a new line with "content" text
"aclogger" callExtension "log$file.log$hey , a log content !";  //add a new line with log format
"aclogger" callExtension "clear$file.log";                      //clear the content
"aclogger" callExtension "removeFile$file.log";                 //remove the file

"aclogger" callExtension "write$subdirectory|file.log$hey !"; 
// for compatibility , the | mean a dir separator , in this case the file will be created in aclogger/subdirectory/file.log
```

