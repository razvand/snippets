#!/bin/bash

echo "Start tcpdump."
sudo ip netns exec mdst tcpdump -i mdst_outer -e -U -w ping.pcap > /dev/null 2>&1 &

echo -n "Sleeping for 5 seconds ..."
sleep 5
echo

# Send some pings; we don't care about the ping output.
echo -n "Pinging for 5 seconds ..."
sudo ip netns exec mdst ping -c 5 10.2.0.3 > /dev/null
echo

# Stop tcpdump.
echo "Stop tcpdump process (send SIGINT)."
sudo kill -INT $!

# Print captured packets.
sleep 2
echo
echo
echo "Packets captured:"
sudo tcpdump -r ping.pcap
