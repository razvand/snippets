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

create_namespace()
{
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
        # Create veth pair.
        MONITORED_INTERFACE_OUTER=${MONITORED_INTERFACE}_outer
        MONITORED_INTERFACE_INNER=${MONITORED_INTERFACE}_inner
        sudo ip link add name $MONITORED_INTERFACE_INNER type veth peer name $MONITORED_INTERFACE_OUTER
        # Allocate predetermined MACs.
        sudo ip link set dev $MONITORED_INTERFACE_INNER address $VETH_MONITOR_MAC_INNER
        sudo ip link set dev $MONITORED_INTERFACE_OUTER address $VETH_MONITOR_MAC_OUTER
        # Create namespace.
        sudo ip netns add $VETH_MONITOR_NAMESPACE
        # Add interface to namespace.
        sudo ip link set dev $MONITORED_INTERFACE_OUTER netns $VETH_MONITOR_NAMESPACE
        # Bring interfaces up.
        sudo ip link set dev $MONITORED_INTERFACE_INNER up
        sudo ip netns exec $VETH_MONITOR_NAMESPACE ip link set dev $MONITORED_INTERFACE_OUTER up
        # Assign IP addresses
        sudo ip netns exec $VETH_MONITOR_NAMESPACE ip addr add $VETH_MONITOR_ADDRESS_OUTER/$VETH_MONITOR_MASK dev $MONITORED_INTERFACE_OUTER
        sudo ip addr add $VETH_MONITOR_ADDRESS_INNER/$VETH_MONITOR_MASK dev $MONITORED_INTERFACE_INNER
        MONITORED_INTERFACE=$MONITORED_INTERFACE_INNER
    fi
}

# Create namespace for destination node.
create_namespace $MONITORED_INTERFACE_DST        \
                 $VETH_MONITOR_DST               \
                 $VETH_MONITOR_MAC_INNER_DST     \
                 $VETH_MONITOR_MAC_OUTER_DST     \
                 $VETH_MONITOR_NAMESPACE_DST     \
                 $VETH_MONITOR_MASK_DST          \
                 $VETH_MONITOR_NET_DST           \
                 $VETH_MONITOR_ADDRESS_INNER_DST \
                 $VETH_MONITOR_ADDRESS_OUTER_DST
