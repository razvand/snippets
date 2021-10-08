#!/bin/bash

MONITORED_INTERFACE_DST=mdst

# For a veth interface as monitor
VETH_MONITOR_DST=true
VETH_MONITOR_NAMESPACE_DST=mdst
VETH_MONITOR_MAC_INNER_DST=22:22:22:00:00:00
VETH_MONITOR_MAC_OUTER_DST=44:44:44:00:00:00
VETH_MONITOR_NET_DST=10.2.0.0
VETH_MONITOR_MASK_DST=16
VETH_MONITOR_MASK_LONG_DST=255.255.0.0
VETH_MONITOR_ADDRESS_OUTER_DST=10.2.0.2
VETH_MONITOR_ADDRESS_INNER_DST=10.2.0.3

remove_namespace() {
    MONITORED_INTERFACE=$1
    VETH_MONITOR=$2
    VETH_MONITOR_MAC_INNER=$3
    VETH_MONITOR_MAC_OUTER=$4
    VETH_MONITOR_NAMESPACE=$5
    VETH_MONITOR_MASK=$6
    VETH_MONITOR_NET=$7
    VETH_MONITOR_ADDRESS_INNER=$8
    VETH_MONITOR_ADDRESS_OUTER=$9

    if [ $VETH_MONITOR == "true" ]; then
        MONITORED_INTERFACE_OUTER=${MONITORED_INTERFACE}_outer
        MONITORED_INTERFACE_INNER=${MONITORED_INTERFACE}_inner
        # Bring interfaces down.
        sudo ip link set dev $MONITORED_INTERFACE_INNER down
        sudo ip netns exec $VETH_MONITOR_NAMESPACE ip link set dev $MONITORED_INTERFACE_OUTER down
        # Flush interfaces.
        sudo ip netns exec $VETH_MONITOR_NAMESPACE ip addr flush dev $MONITORED_INTERFACE_OUTER
        sudo ip addr flush dev $MONITORED_INTERFACE_INNER
        # Remove interface link.
        sudo ip link del $MONITORED_INTERFACE_INNER
        # Remove namespace.
        #sudo ip netns exec $VETH_MONITOR_NAMESPACE ip link set dev $MONITORED_INTERFACE_OUTER netns 1
        sudo ip netns del $VETH_MONITOR_NAMESPACE
        MONITORED_INTERFACE=$MONITORED_INTERFACE_INNER
    fi
}

# Remove namespace for destination node.
remove_namespace $MONITORED_INTERFACE_DST        \
                 $VETH_MONITOR_DST               \
                 $VETH_MONITOR_MAC_INNER_DST     \
                 $VETH_MONITOR_MAC_OUTER_DST     \
                 $VETH_MONITOR_NAMESPACE_DST     \
                 $VETH_MONITOR_MASK_DST          \
                 $VETH_MONITOR_NET_DST           \
                 $VETH_MONITOR_ADDRESS_INNER_DST \
                 $VETH_MONITOR_ADDRESS_OUTER_DST
