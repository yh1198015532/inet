.. :orphan:

New events - NID
================

.. Another way of dealing with new events is to use the network communication fingerprint calculator.

.. When a change introduces new events to the simulation and breaks fingerprints, an option is to use a different / alternative fingerprint calculator, not the default one. INET features the Network Communication Fingerprint Calculator, which extends the default one (as that normal fingerprints can be used alongside it). This fingerprint calculator uses the communication between modules, such as messages, etc, TODO, as ingredients. TODO

   This only takes into account/uses the communication between nodes.
   Thus protocol implementation details don't matter...only the data content of the packets.
   The fingerprint calculator has three available ingredients:

When a change introduces new events to the simulation and breaks fingerprints, an option is to use an alternative fingerprint calculator instead of the default one.
INET's fingerprint calculator (:cpp:`FingerprintCalculator`) extends the default calculator, and adds new ingredients that can be used alongside the default ones.

.. INET features the Network Communication Fingerprint Calculator, which extends the default calculator, and adds new ingredients that can be used alongside the default ones.

.. This fingerprint calculator uses only the communication between network nodes to calculate fingerprints.

.. This fingerprint calculator uses the communication between network nodes as ingredients.

.. The calculator only takes into account the communication between the network nodes.

.. Thus protocol implementation details don't affect the fingerprints, only the data content of the packets. (doesn't matter what happens/what events there are inside network nodes TODO)

The calculator uses the communication between the network nodes to calculate fingerprints.
Thus protocol implementation details and events inside network nodes don't affect the fingerprints,

**V1** only the data content of the packets sent between network nodes.

**V2** only which data is sent between which network nodes.

The fingerprint calculator has four available ingredients:

.. - ``N``: Network node path in the module hierarchy
   - ``I``: Network interface path in the module hierarchy
   - ``D``: Network data

- ``N``: Network node path in the module hierarchy
- ``I``: Network interface path in the module hierarchy; the superset of ``N``
- ``D``: Packet data
- ``~``: Filter events to network communication

.. A fourth ingredient is ``~``, which toggles filtering of events

.. A fourth ingredient toggles filtering of events which are for the NID TODO

.. The network node path is a subset of the network interface path, as the latter is more specific, and contains the network node path. Note that the ``D`` network data is

.. note:: Both ``d`` and ``D`` are packet data ingredients; ``d`` includes packet data and meta-infos such as annotations, tags, and flags; ``D`` includes just the packet data.

To use the ``~NID`` ingredients, add the following line to the ``General`` configuration:

.. literalinclude:: ../omnetpp.ini
   :start-at: General
   :end-at: class
   :language: ini

.. .. literalinclude:: ../omnetpp.ini
      :start-at: General
      :end-at: class
      :language: ini
      :emphasize-lines: 2

.. TODO the default and the NID can be mixed

Now, the ``~NID`` and the default ingredients can be mixed.

.. **V1** The ``~`` ingredient toggles filtering of events to those that are used in the fingerprint calculation for ``N``, ``I`` and ``D``. This is relevant when the NID fingerprints are mixed with the default ones. (the events are filtered even for the default ingredients if they're used)

The ``~`` ingredient toggles filtering of events to those that are messages between two different network nodes, effectively limiting the set of events taking part in fingerprint calculation to network communication. Note that this ingredient affects the default ingredients as well.

.. **TODO** this affects the included default ingredients as well

.. effectively limiting the set of events to network communication./

.. - when the ingredients contain ``~``, events are filtered even for the default ingredients.
   - so if the ingredients are NID, is that filtered?

.. - if ``t`` is not in the ingredients, only D, then just the order of the packet datas matter

.. .. note:: When using only ``D`` as ingredient,

.. **V0** If ``t`` is not in the ingredients, only D, then only the order of the packets define the fingerprints

.. **V1** if the ingredients contain only D (and not t), the fingerprints are defined only by the order of the packets/sent in the network (and the data they contain), but not the timings/timing of the packets.

.. note:: If the ingredients contain only D (and not t), the fingerprints are defined/affected only by the order of the packets (and the data they contain), the timings are irrelevant.

.. **V3** if the ingredients contain only D and not t, then just the order the packets define the fingerprints,
   the timings don't.

.. **V4** if the ingredients contain only D and not t, then just the order the packets matter (and their data) matter, the timings don't.

.. **TODO** its the same as the previous step

To filter the effects of new events, run fingerprints with ~NID ingredients:

- Before making the change in the model, run the fingerprint with ~NID ingredients only
- Make the changes in the model
- Run the fingerprint tests again

If fingerprint tests pass, there was no change in the communication between network nodes,
and the model can be assumed to be correct.

.. TODO example

As a simplistic example, we will make the same change to the Udp module as in the previous step.
We will use only the NID ingredients to calculate fingerprints, and verify the model.

.. We run the fingerprints with NID~ ingredients by replacing the ingredients in the .csv file:

We replace the default ingredients with ``~NID`` in the .csv file:

.. TODO

.. code-block:: text

  .,        -f omnetpp.ini -c Ethernet -r 0,           5s,         aeb0-6fd3/~NID, PASS,
  .,        -f omnetpp.ini -c EthernetUdp10 -r 0,      5s,         e2b5-3bc8/~NID, PASS,
  .,        -f omnetpp.ini -c Wifi -r 0,               5s,         c1f4-8059/~NID, PASS,
  .,        -f omnetpp.ini -c WifiUdp10 -r 0,          5s,         4ce3-ac67/~NID, PASS,
  .,        -f omnetpp.ini -c Ospf -r 0,            5000s,         da5a-88c1/~NID, PASS,

Then we run the fingerprint tests:

.. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Ethernet -r 0  ... : FAILED: actual  'b47f-d0db/~NID'
  . -f omnetpp.ini -c Ospf -r 0  ... : FAILED
  . -f omnetpp.ini -c Wifi -r 0  ... : FAILED
  . -f omnetpp.ini -c WifiUdp10 -r 0  ... : FAILED
  . -f omnetpp.ini -c EthernetUdp10 -r 0  ... : FAILED

As there was no change in the model, the new fingerprints can be accepted:

.. code-block:: fp

   $ mv fingerprintshowcase.csv.UPDATED fingerprintshowcase.csv

We make the change:

.. literalinclude:: ../Udp_mod.cc
   :diff: ../Udp_orig.cc

**TODO** should we mention the .h?

We run the fingerprint tests again:

.. code-block:: fp

  $ inet_fingerprinttest
  . -f omnetpp.ini -c Ethernet -r 0  ... : PASS
  . -f omnetpp.ini -c Ospf -r 0  ... : PASS
  . -f omnetpp.ini -c Wifi -r 0  ... : PASS
  . -f omnetpp.ini -c WifiUdp10 -r 0  ... : PASS
  . -f omnetpp.ini -c EthernetUdp10 -r 0  ... : PASS

.. TODO

.. Here is the example model change from the previous step:

.. .. literalinclude:: ../Udp_mod.cc
      :diff: ../Udp_orig.cc

.. We run the fingerprint tests with only the NID ingredients, and update the .csv file with the new values:

.. TODO NID fingerprints PASS

After making the change, the fingerprint tests pass, thus the model can be assumed correct.

**TODO** pittfalls
