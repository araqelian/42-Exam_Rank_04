# 📌 subject.en.txt
<p>
Assignment name: &nbsp;&nbsp;&nbsp;microshell<br>
Expected files: &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;microshell.c<br>
Allowed functions: &nbsp;&nbsp;&nbsp;malloc, &nbsp;free, &nbsp;write,&nbsp; close, &nbsp;fork, &nbsp;waitpid, &nbsp;signal, &nbsp;kill, &nbsp;exit, &nbsp;chdir, &nbsp;execve, &nbsp;dup, &nbsp;dup2, &nbsp;pipe,&nbsp; strcmp,&nbsp; strncmp<br>
____________________________________________________________________________________________________________
</p>
<p>
Write a program that will behave like executing a shell command
<ul>
<li>  The command line to execute will be the arguments of this program
<li>  Executable's path will be absolute or relative but your program must not build a path (from the PATH variable for example)
<li>  You must implement "|" and ";" like in bash
<li>  we will never try a "|" immediately followed or preceded by nothing or "|" or ";"
<li>  Your program must implement the built-in command cd only with a path as argument (no '-' or without parameters)
<li>  if cd has the wrong number of argument your program should print in STDERR "error: cd: bad arguments" followed by a '\n'
<li>  if cd failed your program should print in STDERR "error: cd: cannot change directory to path_to_change" followed by a '\n' with path_to_change replaced by the argument to cd
<li>  a cd command will never be immediately followed or preceded by a "|"
<li>  You don't need to manage any type of wildcards (*, ~ etc...)
<li>  You don't need to manage environment variables ($BLA ...)
<li>  If a system call, except execve and chdir, returns an error your program should immediatly print "error: fatal" in STDERR followed by a '\n' and the program should exit
<li>  If execve failed you should print "error: cannot execute executable_that_failed" in STDERR followed by a '\n' with executable_that_failed replaced with the path of the failed executable (It should be the first argument of execve)
<li>  Your program should be able to manage more than hundreds of "|" even if we limit the number of "open files" to less than 30.
</ul><br>
<b>for example this should work:</b>
<p>
$>./microshell&nbsp; /bin/ls&nbsp; "|" &nbsp;/usr/bin/grep &nbsp;microshell &nbsp;";" &nbsp;/bin/echo &nbsp;i love my microshell<br>
microshell<br>
i love my microshell<br>
</p>
<p>
$>./microshell &nbsp;/bin/echo &nbsp;i love 42 &nbsp;"|" &nbsp;"/usr/bin/grep" &nbsp;i &nbsp;";" &nbsp;";" &nbsp;";" &nbsp;"/bin/echo" YEAH<br>
i love 42<br>
YEAH
</p>
Hints:
Don't forget to pass the environment variable to execve

Hints:
Do not leak file descriptors!
