# OWASP Bucharest AppSec Conference 2016 CTF

CTF (Capture the Flag) contest to take place at [OWASP AppSec 2016 Bucharest](OWASP Bucharest AppSec Conference 2016). The CTF will take place on Thursday, October 6, 2016, during the conference.

Challenges are split in categories and each category contains several challenges. Each category is a folder and each challenge is a folder in its category folder. Categories are `crypto`, `exploit`, `misc`, `reverse` and `web`.

## Creating a Challenge

A challenge is created as a subfolder in its category folder. A sample challenge folder is `sample/piece_of_pie/` with the contents below:
```
sample/piece_of_pie/
|-- README.md
|-- public/
|   `-- piece_of_pie*
|-- flag
|-- sol/
|   `-- exploit.py
`-- src/
    |-- Makefile
    `-- piece_of_pie.c
```
As above, the challenge folder must have:
* a `README.md` similar to the one in the `sample/piece_of_pie` folder that provides:
  * the challenge title
  * the challenge description, also showing hints and score
  * a description of the vulnerability
  * a description of the exploit/solution
  * instructions on deploying it and its required environment
* a `flag` file containing the flag to be captured;
* a `src/` subfolder used for building the challenge. It must provide a `Makefile` file with a `clean` and `public` target (possibly a `private` target).
* a `sol/` subfolder containing the solution/exploit script. It is recommended to name it `exploit.py` or similar.
* a `public/` subfolder where build results from the `src/` subfolder and additional required files are to be placed. The contents of this folder are to be packed into the challenge archive that will be be published to the participants.
* an optional `private/` subfolder folder where private build results from the `src/` subfolder are to be placed. The contents of this folder are to be packed into the challenge archive that will be be deployed privately in the CTF infrastructure.

## Packing a Challenge

After creating the challenge, we create a `.tar` file that will be published to the participants. The name of the `.tar` file will consist of the challenge folder name and the MD5 sum of the archive, such that participants can check they have the correct file.

We use the `pack-public` script to create a challenge archive. We either pass it the path to the challenge subfolder (multiple arguments are allowed) or we run it with no arguments, in which case it walks through all challenge subfolders. A sample run is:
```
$ ls
crypto  exploit  misc  reverse  sample  web  README.md  clean-src  config  make-src  pack-private  pack-public  private-src  public-src


$ ./pack-public
Packing public for sample/piece_of_pie ...


$ ls
crypto   misc     sample  README.md  config    pack-private  piece_of_pie_43990b11e9561be8a952cadc23a9caf4.tar  public-src
exploit  reverse  web     clean-src  make-src  pack-public   private-src


$ md5sum piece_of_pie_43990b11e9561be8a952cadc23a9caf4.tar
43990b11e9561be8a952cadc23a9caf4  piece_of_pie_43990b11e9561be8a952cadc23a9caf4.tar
```
After running the `pack-public` script, we get the `piece_of_pie_43990b11e9561be8a952cadc23a9caf4.tar` file: the challenge folder name `piece_of_pie` followed by the MD5 sum of the file.

There are similar scripts to automate other actions. They are invoked similar to the `pack-public` script:
* the `make-src` script builds result files in the `src` subfolder; it invokes `make` in the `src/` subfolder;
* the `clean-src` script cleans output and intermediary files the `src` subfolder; it invokes `make clean` in the `src/` subfolder;
* the `public-src` copies result files from the `src` subfolder to the `public` subfolder; it invokes `make public` in the `src/` subfolder/.

## Deploying a Challenge

Deploying a challenge usually requires a virtual machine where to deploy it. We will use virtual machines in the [NCIT Cluster in UPB](http://curs.pub.ro/index.php/projects/projects-cursuri-upb/17-general/general/13-ncit-cluster-homepage) and the [xinetd-based approach](https://github.com/pwning/docs/blob/master/suggestions-for-running-a-ctf.markdown#remote) for deploying challenge binaries and flags.

For flags we will use the `OWASPCTF` prefix followed by a random string in curly brackets, e.g. `OWASPCTF{jumping_Jehoshaphat}`. We place flag files in `/flag`, i.e. in the root folder.
