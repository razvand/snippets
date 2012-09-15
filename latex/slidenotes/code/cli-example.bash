alexj@hathor ~ $ uname
Linux
alexj@hathor ~ $ uname --help
Usage: uname [OPTION]...
Print certain system information.  With no OPTION, same as -s.

  -a, --all                print all information, in the following order,
                             except omit -p and -i if unknown:
  [snip]

alexj@hathor ~ $ uname -h
uname: invalid option -- 'h'
Try `uname --help' for more information.
alexj@hathor ~ $ uname -a
Linux hathor 3.3.0-rc6+ #7 SMP Mon Mar 5 19:54:28 EET 2012 i686 i686
i386 GNU/Linux
alexj@hathor ~ $ uname --all
Linux hathor 3.3.0-rc6+ #7 SMP Mon Mar 5 19:54:28 EET 2012 i686 i686
i386 GNU/Linux
