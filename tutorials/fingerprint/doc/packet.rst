.. :orphan:

Changing Packet Length
======================

.. TODO

tplx -> tpx
ha csak mondjuk az app csomaghossza valtozott 1-rol 2-byte-ra, ethernet padding miatt min csomag length 64
vagy
tplx -> px
ha nagyobb a valtozas

workflow -> ha megváltoztatjuk a csomag hosszát de belefér a min ehternet frame-be akkor az az expectation hogy nem változik meg a fingerprint (a csomag hossza a network-ön nem változik) és így az időzítések se
de ha nagy a változás akkor igen

TODO minden stepnél -> expectation -> a mögöttes gondolkodás

l -> minden eseménynél figyelembe veszi a csomag hosszát

mit gondolsz az adott change-nél

so

- what happens when you change the packet length? the tplx fingerprints change
- the packet length is part of the ingredients
- it affects fingerprints in all stages of the packet -> as it travels down the protocol stack
- so the packet length should be dropped
- what is the point in this ? you change the header length and you think it doesnt alter the model
and want to make sure it doesn't ? or just show what fingerprints break or not break when
the packet length is changed
- the thinking is that when the packet is small it doesn't break the fingerprints

- change something in the model that causes the packet length to change, e.g. a change in a protocol header

Some changes in the model, e.g. adding fields to a protocol header, can cause the packet lengths to change.
This in turn leads to changes in the ``tplx`` fingerprints. The ``l`` stands for packet length, and the length of packets anywhere in the network is taken into account at every event.

TODO is there a missing logical step here? that we drop the packet length from the fingerprints to see if the model behaves the same way as before?

Even if we drop the packet length from the fingerprint ingredients, the fingerprints might still change due to the different timings of the longer/shorter packets/frames.

If we drop the packet length from the fingerprint ingredients, the fingerprints might still change due to the different timings of the packets/frames.

Our expectation is that we change the packet length, but if the packets are small and still fit in a minimum Ethernet frame size of 64 bytes, the frame is padded, and the packet length change doesn't matter in terms of fingerprints/doesn't affect fingerprints. If the packet is smaller than the minimum ethernet size, the frame is padded.

A similar padding effect happens in 802.11 frames. The data contained in the frame is a multiple of the bits per symbol value for the given modulation. For QAM-64, this is around 30 bytes.

TODO so we expect that for small packets the fingerprints don't change; for larger ones they do

In the following example, we'll increase the Udp header size from 8 bytes to 10 bytes.

TODO do we need additional configs for that? a short packet version of each of the configs?

TODO do we want to use the ethernet and the wifi padding as well ?

Before making the change, we drop the packet length from the fingerprints and run the tests:

.. TODO .csv with tpx

.. code-block:: text
   :caption: fingerprintshowcase.csv

   .,        -f omnetpp.ini -c Wireless -r 0,        5s,         8365-8b99/tpx, PASS,
   .,        -f omnetpp.ini -c Mixed -r 0,           5s,         e7ed-cd64/tpx, PASS,
   .,        -f omnetpp.ini -c Wired -r 0,           5s,         fc75-b591/tpx, PASS,
   .,        -f omnetpp.ini -c WirelessNID -r 0,     5s,         d410-0d99/NID,  PASS,
   .,        -f omnetpp.ini -c WiredNID -r 0,        5s,         1145-0392/NID,  PASS,
   .,        -f omnetpp.ini -c MixedNID -r 0,        5s,         d2fb-2f48/NID,  PASS,
   .,        -f omnetpp.ini -c WirelessNIDDim -r 0,  5s,         d410-0d99/NID,  PASS,
   .,        -f omnetpp.ini -c WirelessDim -r 0,     5s,         8365-8b99/tpx, PASS,
   .,        -f omnetpp.ini -c Ospf -r 0,            5000s,      0cf5-6ae4/tpx, PASS,
   .,        -f omnetpp.ini -c WirelessUdp10 -r 0,   5s,         384f-3adf/tpx, PASS,
   .,        -f omnetpp.ini -c WiredUdp10 -r 0,      5s,         fc75-b591/tpx, PASS,
   .,        -f omnetpp.ini -c MixedUdp10 -r 0,      5s,         fc75-b591/tpx, PASS,

.. TODO fingerprints fail

.. code-block:: fp

  $ inet_fingerprinttest xxx.csv
  . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Wireless -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WiredNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessDim -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessUdp10 -r 0  ... : PASS
  . -f omnetpp.ini -c MixedUdp10 -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WiredUdp10 -r 0  ... : PASS

We update the .csv with the new fingerprints:

.. code-block:: fp

   $ mv fingerprintshowcase.csv.UPDATED fingerprintshowcase.csv

Then we increase the Udp header size:

.. literalinclude:: ../UdpHeader.msg.mod
   :diff: ../UdpHeader.msg.orig

We run the fingerprint tests again:

.. code-block:: fp

  $ inet_fingerprinttest xxx.csv
  . -f omnetpp.ini -c Wired -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Mixed -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Wireless -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WiredNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c MixedNID -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessNIDDim -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessDim -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WirelessUdp10 -r 0  ... : PASS
  . -f omnetpp.ini -c MixedUdp10 -r 0  ... : FAILED (should be PASS)
  . -f omnetpp.ini -c WiredUdp10 -r 0  ... : PASS

TODO why the two fingerprints didn't change
