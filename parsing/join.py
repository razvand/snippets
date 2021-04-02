#!/usr/bin/env python3

import sys


def usage(argv0):
    print("Usage: {} <first_file> <second_file>".format(argv0), file=sys.stderr)


def main():
    if len(sys.argv) != 3:
        usage(sys.argv[0])
        sys.exit(1)

    first = open(sys.argv[1])
    second = open(sys.argv[2])

    first_items = {}
    for l in first.readlines():
        g = l.rstrip().split("\t")
        first_items[g[0]] = g[1:]

    second_items = {}
    for l in second.readlines():
        g = l.rstrip().split("\t")
        second_items[g[0]] = g[2:]

    for i in first_items.keys():
        if i in second_items.keys():
            print(i + "\t" + "\t".join(item for item in first_items[i]) + "\t" + "\t".join(item for item in second_items[i]))
        else:
            print(i + "\t" + "\t".join(item for item in first_items[i]))


if __name__ == "__main__":
    sys.exit(main())
