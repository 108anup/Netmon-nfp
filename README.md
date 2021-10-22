# Sketching on Netronome Agilio SmartNIC devices

# Implemented sketches:
Count Min Sketch, Count Sketch, and Univmon (optimized version of Univmon, refer to SketchLib [NSDI22] for high level sketch optimizations)

# Development Requirements
1. Setup Netronome kernel modules, drivers, and basic NIC firmware (https://help.netronome.com/support/solutions/articles/36000049975-basic-firmware-user-guide)
2. Setup Netronome compilation toolchain (https://www.netronome.com/products/datapath-programming-tools/). 
I don't think this is publically available. We procured the development SDK from Netronome when we bought the NICs.
3. Setup DPDK (https://www.dpdk.org/) and pktgen (https://pktgen-dpdk.readthedocs.io/en/latest/) for sendign and recieving packets and running benchmarking experiments.
You could also use linux kernel data path (via standard netdev interfaces and iperf/custom application). Steps to run would be different for this. 
The kernel module params change dpending on whether you want to use for dpdk or kernel. Refer to the basic firmware doc above for more information.

# Steps to run
```
./reset.sh  # For if you used the NIC kernel modules previously for some other purposes.
./start.sh  # Prepare NIC to accept a new firmware.
./build.sh <project-path>  # e.g., ./build.sh univmon
./load.sh <project-path>  # e.g., ./build.sh univmon
```
At this point you can send and receive packets.
I used a custom dpdk receiver (https://github.com/108anup/dpdk-receiver) on one server hosting the NIC and pktgen on another server.
Refer to `./run_manifests.sh` for more information on this.

Refer to `./reload_rules.sh` for how to change MA table configuration at runtime.
