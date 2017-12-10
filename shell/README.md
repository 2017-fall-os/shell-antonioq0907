Lab 2 Shell

    Objective: Make a shell that bash and implement several commands

Shell main code in shell.c
    Different comments throughtout the code, with short descriptions of each methods.

Test
    TEST                        OUTPUT
    -----------------------------------
    cd ..                       Passed
    -----------------------------------
    pwd                         Passed
    -----------------------------------
    ps                          Passed
    -----------------------------------
    uname                       Passed
    -----------------------------------
    /bin/uname                  Passed
    -----------------------------------
    /bin/uname                  Passed
    /bin/uname
    -----------------------------------
    /bin/uname                  Passed

    /bin/uname
    -----------------------------------
    cat /etc/passwd             Passed
    -----------------------------------
    cat /etc/passwd | sort      Passed
    -----------------------------------
    cat /etc/passwd | sort | wc Passed
    -----------------------------------
    dfe                         Failed
    -----------------------------------
    cd                          Failed
    -----------------------------------
    wc                          Failed
    -----------------------------------
    ps1                         Failed
    
    
Running
    $ make run
    $ make ./ myShellTest
    
Exit test
    $ exit
    $ EXIT
    sometimes it does not work the first input, multiple attends is recommended.
    
