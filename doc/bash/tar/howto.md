##Create a tar file
To create a tar file, type:<br>
`tar -cvf filename.tar files/directories`<br>
To create a tar.gz file, type:<br>
`tar -zcvf filename.tar.gz files/directories`<br>
Where,<br>
* -z: Compress archive using gzip program
* -c: Create archive
* -v: Verbose i.e display progress while creating archive
* -f: Archive File name

##Extract or Unpack a TarBall File
To unpack or extract a tar file, type:<br>
`tar -xvf file.tar`<br>
To extract / unpack a .tar.gz (gzip) file, enter (note -z option):<br>
`tar -xzvf file.tar.gz`<br>
To extract / unpack a .tar.bz2 (bzip2) file, enter (note -j option):<br>
`tar -xjvf file.tar.bz2`<br>
Where,<br>
* -x : Extract a tar ball.
* -v : Verbose output or show progress while extracting files.
* -f : Specify an archive or a tarball filename.
* -j : Decompress and extract the contents of the compressed archive created by bzip2 program (tar.bz2 extension).
* -z : Decompress and extract the contents of the compressed archive created by gzip program (tar.gz extension).

##References
[https://www.centos.org/docs/2/rhl-gsg-en-7.2/s1-zip-tar.html](https://www.centos.org/docs/2/rhl-gsg-en-7.2/s1-zip-tar.html)<br>
[http://www.cyberciti.biz/faq/tar-extract-linux/](http://www.cyberciti.biz/faq/tar-extract-linux/)