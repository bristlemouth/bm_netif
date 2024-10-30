# Bristlemouth Network Interface

**This repository is being archived.
The code has been incorporated into bm_core in PR 28:
https://github.com/bristlemouth/bm_core/pull/28**

---

This repo defines the Bristlemouth `NetworkInterface` trait.
A network interface must support an `init` method and a `send` method.
Passed into `init` is a `Receiver`, a trait with one required method `receive`,
which is called by the network interface when bytes are received on the wire.

As of 2024 the only device in usage for Bristlemouth Single-Pair Ethernet (SPE)
networks is the two-port ADIN2111 from Analog Devices.
The ADIN1110 is a single-port variant of the same hardware.
This repo implements drivers for both chips.
