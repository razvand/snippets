# Packet Capture for Network Namespaces

This is a demo on using network namespacing and `tcpdump` for packet capture.

It uses a namespace (`mdst`) and a veth interface pair.
One end of the pair is in in the namespace (`mdst_inner`);
the other is outside of it (`mdst_outer`).

`ping` is used to send packets from the namespaces to the outer interface.
`tcpdump` is used to capture the packets.
Packets are captured raw (via the `-w` flag of `tcpdump`) in the `ping.pcap` file.
The contents of the `ping.pcap` file can then be rendered using the `-r` flag of `tcpdump`.

There are three scripts:
* `create_namespace.sh`: create the setup: namespace and interface pair
* `remove_namespace.sh`: remove the namespace
* `run_tcpdump.sh`: run `tcpdump` to capture packets to / from the namespace;
  use `ping` to send packets
