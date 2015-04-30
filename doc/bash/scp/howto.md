##Transfer files to remote machine
`scp <file to be transfered> <username>@<hostname or IP address of the remote machine>:<path to destination>`<br>
For example, if you want to transfer foo.txt to the /temp of the remote machine 192.168.0.4, and the username of that machine is geek, then the command should be:<br>
`scp foo.txt geek@192.168.0.4:/temp` 